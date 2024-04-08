#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

template <typename Hash> 
int FindCollisions(const Hash& hasher, istream& text)
{
    int collision_count = 0;
    unordered_map<size_t, unordered_set<string>> words;
    string word;
    while (text >> word)
    {
        size_t hash = hasher(word);
        if (const auto it = words.find(hash); it != words.end())
            collision_count += it->second.insert(word).second;
        else words[hash].insert(word);
    }

    return collision_count;
}

struct DummyHash
{
    size_t operator()(const string&) const
    {
        return 42;
    }
};

int main()
{
    DummyHash dummy_hash;
    hash<string> good_hash;

    {
        istringstream stream("I love C++"s);
        cout << FindCollisions(dummy_hash, stream) << endl;
    }
    {
        istringstream stream("I love C++"s);
        cout << FindCollisions(good_hash, stream) << endl;
    }
}