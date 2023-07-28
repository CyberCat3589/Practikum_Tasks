#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

template <typename It>
void PrintRange(It range_begin, It range_end)
{
    if(range_begin == range_end)
    {
        cout << endl;
        return;
    }

    for (auto it = range_begin; it != range_end; ++it) 
    {
        cout << *it << " "s;
    }

    cout << endl;
}

template <typename Container, typename Element>
void FindAndPrint(Container container, Element element)
{
    auto it = find(container.begin(), container.end(), element);

    PrintRange(container.begin(), it);
    PrintRange(it, container.end());
}

template <typename It>
auto MakeVector(It range_begin, It range_end)
{
    return vector(range_begin, range_end);
}

int main() 
{
    /*
    set<int> test = {1, 1, 1, 2, 3, 4, 5, 5};
    cout << "Test1"s << endl;
    FindAndPrint(test, 3);

    cout << "Test2"s << endl;
    FindAndPrint(test, 0); // элемента 0 нет в контейнере

    cout << "Test3"s << endl;
    vector<int> test_vec = {1, 2, 3, 4, 5};
    FindAndPrint(test_vec, 4);

    cout << "Test4"s << endl;
    string test_str = "Focus-pokus";
    FindAndPrint(test_str, '-');

    cout<< "End of tests"s << endl;
    */
    set<string> unique_langs = {"Python"s, "Java"s, "C#"s, "Ruby"s, "C++"s};
    vector<string> langs = MakeVector(unique_langs.begin(), unique_langs.end());
    PrintRange(langs.begin(), langs.end());
}