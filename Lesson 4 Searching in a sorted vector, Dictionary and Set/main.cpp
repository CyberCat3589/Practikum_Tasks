#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

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

template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin, RandomIt range_end, string prefix) 
{
    RandomIt it1 = lower_bound(range_begin, range_end, prefix);

    prefix[prefix.size() - 1] = prefix[prefix.size() - 1] + 1;

    RandomIt it2 = lower_bound(range_begin, range_end, prefix);
    
    return {it1, it2};
}

int main() 
{
    /*
    set<int> numbers = {1, 4, 6};
    cout << *FindNearestElement(numbers, 0) << " " << *FindNearestElement(numbers, 3) << " "
         << *FindNearestElement(numbers, 5) << " " << *FindNearestElement(numbers, 6) << " "
         << *FindNearestElement(numbers, 100) << endl;
    set<int> empty_set;
    cout << (FindNearestElement(empty_set, 8) == end(empty_set)) << endl;
    */

    const vector<string> sorted_strings = {"moscow", "motovilikha", "murmansk"};
    const auto mo_result = FindStartsWith(begin(sorted_strings), end(sorted_strings), "mo");
    for (auto it = mo_result.first; it != mo_result.second; ++it) {
        cout << *it << " ";
    }
    cout << endl;
    const auto mt_result = FindStartsWith(begin(sorted_strings), end(sorted_strings), "mt");
    cout << (mt_result.first - begin(sorted_strings)) << " " << (mt_result.second - begin(sorted_strings)) << endl;
    const auto na_result = FindStartsWith(begin(sorted_strings), end(sorted_strings), "na");
    cout << (na_result.first - begin(sorted_strings)) << " " << (na_result.second - begin(sorted_strings)) << endl;

    return 0;
}