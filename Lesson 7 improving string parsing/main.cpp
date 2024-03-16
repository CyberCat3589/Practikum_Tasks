#include <cassert>
#include <iostream>
#include <string_view>
#include <vector>
#include <cstdint>

using namespace std;

vector<string_view> SplitIntoWordsView(string_view str)
{
    vector<string_view> result;

    str.remove_prefix(min(str.find_first_not_of(" "), str.size()));

    while (!str.empty())
    {
        int64_t space = str.find(' ');
        result.push_back(str.substr(0, space));
        str.remove_prefix(min(str.find(" "), str.size()));
        str.remove_prefix(min(str.find_first_not_of(" "), str.size()));
    }

    return result;
}

int main()
{
    assert((SplitIntoWordsView("") == vector<string_view>{}));
    assert((SplitIntoWordsView("     ") == vector<string_view>{}));
    assert((SplitIntoWordsView("aaaaaaa") == vector{"aaaaaaa"sv}));
    assert((SplitIntoWordsView("a") == vector{"a"sv}));
    assert((SplitIntoWordsView("a b c") == vector{"a"sv, "b"sv, "c"sv}));
    assert((SplitIntoWordsView("a    bbb   cc") == vector{"a"sv, "bbb"sv, "cc"sv}));
    assert((SplitIntoWordsView("  a    bbb   cc") == vector{"a"sv, "bbb"sv, "cc"sv}));
    assert((SplitIntoWordsView("a    bbb   cc   ") == vector{"a"sv, "bbb"sv, "cc"sv}));
    assert((SplitIntoWordsView("  a    bbb   cc   ") == vector{"a"sv, "bbb"sv, "cc"sv}));
    cout << "All OK" << endl;
}