#include <iostream>
#include <set>
#include <vector>

using namespace std;

template <typename It>
void PrintRange(It range_begin, It range_end)
{
    if(range_begin == range_end) return;

    for (auto it = range_begin; it != range_end; ++it) 
    {
        cout << *it << " "s;
    }

    cout << endl;
}

int main() 
{
    cout << "Test1"s << endl;
    set<int> test1 = {1, 1, 1, 2, 3, 4, 5, 5};
    PrintRange(test1.begin(), test1.end());
    cout << "Test2"s << endl;
    vector<int> test2 = {}; // пустой контейнер
    PrintRange(test2.begin(), test2.end());
    cout << "End of tests"s << endl;
}