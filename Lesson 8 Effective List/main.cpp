#include <string>
#include <cstddef>
#include <list>
#include <iostream>

class Editor
{
  public:
    Editor() = default;

    // сдвинуть курсор влево
    void Left()
    {
        if (it_ == text_.begin())
        {
            return;
        }
        --it_;
    }

    // сдвинуть курсор вправо
    void Right()
    {
        if (it_ == text_.end())
        {
            return;
        }
        ++it_;
    }

    // вставить символ token
    void Insert(char token)
    {
        text_.insert(it_, token);
    }

    // вырезать не более tokens символов, начиная с текущей позиции курсора
    void Cut(size_t tokens = 1)
    {
        if (tokens > static_cast<size_t>(std::distance(it_, text_.end())))
        {
            tokens = static_cast<size_t>(std::distance(it_, text_.end()));
        }
        auto nx = std::next(it_, tokens);
        buffer_.assign(it_, nx);
        // text_.erase(it_, nx);
        it_ = text_.erase(it_, nx);
    }

    // cкопировать не более tokens символов, начиная с текущей позиции курсора
    void Copy(size_t tokens = 1)
    {
        if (tokens > static_cast<size_t>(std::distance(it_, text_.end())))
        {
            tokens = static_cast<size_t>(std::distance(it_, text_.end()));
        }
        auto nx = std::next(it_, tokens);
        buffer_.assign(it_, nx);
    }

    // вставить содержимое буфера в текущую позицию курсора
    void Paste()
    {
        text_.insert(it_, buffer_.begin(), buffer_.end());
    }

    // получить текущее содержимое текстового редактора
    std::string GetText() const
    {
        return {text_.begin(), text_.end()};
    }

  private:
    std::list<char> text_{};
    std::list<char> buffer_{};
    std::list<char>::iterator it_ = text_.begin();
};

int main()
{
    Editor editor;
    const std::string text = "hello, world"s;
    for (char c : text)
    {
        editor.Insert(c);
    }
    // Текущее состояние редактора: `hello, world|`
    for (size_t i = 0; i < text.size(); ++i)
    {
        editor.Left();
    }
    // Текущее состояние редактора: `|hello, world`
    editor.Cut(7);
    // Текущее состояние редактора: `|world`
    // в буфере обмена находится текст `hello, `
    for (size_t i = 0; i < 5; ++i)
    {
        editor.Right();
    }
    // Текущее состояние редактора: `world|`
    editor.Insert(',');
    editor.Insert(' ');
    // Текущее состояние редактора: `world, |`
    editor.Paste();
    // Текущее состояние редактора: `world, hello, |`
    editor.Left();
    editor.Left();
    // Текущее состояние редактора: `world, hello|, `
    editor.Cut(3);  // Будут вырезаны 2 символа
    // Текущее состояние редактора: `world, hello|`
    std::cout << editor.GetText();
    return 0;
}