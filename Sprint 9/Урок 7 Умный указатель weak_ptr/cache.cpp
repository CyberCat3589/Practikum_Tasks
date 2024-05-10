#include <cassert>
#include <iostream>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>

template <typename Key, typename Value, typename ValueFactoryFn>
class Cache
{
  public:
    Cache() = default;

    explicit Cache(ValueFactoryFn value_factory) : value_factory_(value_factory)
    {
    }

    std::shared_ptr<Value> GetValue(const Key& key)
    {

        std::shared_ptr<Value> temp;

        if (value_map_.count(key))
        {
            if (value_map_[key].expired())
            {
                temp = value_factory_(key);
                value_map_[key] = temp;
            }

            return (value_map_[key]).lock();
        }

        temp = value_factory_(key);
        value_map_[key] = temp;
        return (value_map_[key]).lock();
    }

  private:
    ValueFactoryFn value_factory_;
    std::unordered_map<Key, std::weak_ptr<Value>> value_map_;
};

class Object
{
  public:
    explicit Object(std::string id) : id_(std::move(id))
    {
        using namespace std;
        cout << "Object '"sv << id_ << "' has been created"sv << endl;
    }

    const std::string& GetId() const
    {
        return id_;
    }

    ~Object()
    {
        using namespace std;
        cout << "Object '"sv << id_ << "' has been destroyed"sv << endl;
    }

  private:
    std::string id_;
};

using ObjectPtr = std::shared_ptr<Object>;

struct ObjectFactory
{
    ObjectPtr operator()(std::string id) const
    {
        return std::make_shared<Object>(std::move(id));
    }
};

void Test1()
{
    using namespace std;
    ObjectPtr alice1;
    Cache<string, Object, ObjectFactory> cache;

    alice1 = cache.GetValue("Alice"s);
    auto bob = cache.GetValue("Bob"s);

    assert(alice1 != bob);
    assert(alice1->GetId() == "Alice"s);
    assert(bob->GetId() == "Bob"s);

    auto alice2 = cache.GetValue("Alice"s);
    assert(alice1 == alice2);

    weak_ptr alice_wp{alice1};
    alice1.reset();
    assert(!alice_wp.expired());
    cout << "---"sv << endl;
    alice2.reset();

    assert(alice_wp.expired());
    cout << "---"sv << endl;

    alice1 = cache.GetValue("Alice"s);
    cout << "---"sv << endl;
}

struct Book
{
    Book(std::string title, std::string content) : title(std::move(title)), content(std::move(content))
    {
    }

    std::string title;
    std::string content;
};

class BookLoader
{
  public:
    using BookStore = std::unordered_map<std::string, std::string>;

    explicit BookLoader(const BookStore& store, size_t& load_count) : store_(store), load_count_(load_count)
    {
    }

    std::shared_ptr<Book> operator()(const std::string& title) const
    {

        if (store_.count(title))
        {
            ++load_count_;
            return std::make_shared<Book>(title, store_.at(title));
        }
        else
        {
            throw std::out_of_range("Not implemented");
        }
    }

  private:
    const BookStore& store_;
    size_t& load_count_;
};

void Test2()
{
    using namespace std;

    BookLoader::BookStore books{
        {"Sherlock Holmes"s, "To Sherlock Holmes she is always the woman. I have seldom heard him mention her under any other name."s},
        {"Harry Potter"s, "Chapter 1. The boy who lived. ...."s},
    };
    using BookCache = Cache<string, Book, BookLoader>;

    size_t load_count = 0;

    BookCache book_cache{BookLoader{books, load_count}};

    auto book1 = book_cache.GetValue("Sherlock Holmes"s);
    assert(book1);
    assert(book1->title == "Sherlock Holmes"s);
    assert(book1->content == books.at(book1->title));
    assert(load_count == 1);

    auto book2 = book_cache.GetValue("Sherlock Holmes"s);
    assert(book2);
    assert(book1 == book2);
    assert(load_count == 1);

    weak_ptr<Book> weak_book{book1};
    assert(!weak_book.expired());
    book1.reset();
    book2.reset();

    assert(weak_book.expired());

    book1 = book_cache.GetValue("Sherlock Holmes"s);
    assert(load_count == 2);
    assert(book1);

    try
    {
        book_cache.GetValue("Fifty Shades of Grey"s);
        assert(false);
    }
    catch (const std::out_of_range&)
    {
    }
    catch (...)
    {
        cout << "Unexpected exception"sv << endl;
    }

    assert(load_count == 2);

    books["Fifty Shades of Grey"s] = "I scowl with frustration at myself in the mirror..."s;

    try
    {
        auto book = book_cache.GetValue("Fifty Shades of Grey"s);

        assert(book->content == books.at("Fifty Shades of Grey"s));
    }
    catch (...)
    {
        assert(false);
    }

    assert(load_count == 3);
}

int main()
{
    Test1();
    Test2();
}