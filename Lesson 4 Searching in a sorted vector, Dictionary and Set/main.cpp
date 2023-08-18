#include <iostream>
#include <set>

using namespace std;

set<int>::const_iterator FindNearestElement(const set<int>& numbers, int border) 
{
    // set<int>::const_iterator — тип итераторов для константного множества целых чисел
    auto it_big = numbers.lower_bound(border);
    if(it_big != numbers.begin())
    {
        auto it_small = prev(it_big, 1);
        if(abs(border - *it_big) >= abs(border - *it_small))
        {
            return it_small;
        }else
        {
            return it_big;
        }
    }
    return it_big;
}

int main() 
{
    set<int> numbers = {1, 4, 6};
    cout << *FindNearestElement(numbers, 0) << " " << *FindNearestElement(numbers, 3) << " "
         << *FindNearestElement(numbers, 5) << " " << *FindNearestElement(numbers, 6) << " "
         << *FindNearestElement(numbers, 100) << endl;
    set<int> empty_set;
    cout << (FindNearestElement(empty_set, 8) == end(empty_set)) << endl;
    return 0;
}