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
pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin, RandomIt range_end, char prefix) 
{
    string prefix_str = " ";
    prefix_str[0] = prefix;

    RandomIt lower = lower_bound(range_begin, range_end, prefix_str);

    ++prefix_str[0];

    RandomIt upper = upper_bound(range_begin, range_end, prefix_str);
    
    return {lower, upper};
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

    const vector<string> sorted_strings = {"moscow", "murmansk", "vologda"};
    const auto m_result = FindStartsWith(begin(sorted_strings), end(sorted_strings), 'm');
    for (auto it = m_result.first; it != m_result.second; ++it) {
        cout << *it << " ";
    }
    cout << endl;
    const auto p_result = FindStartsWith(begin(sorted_strings), end(sorted_strings), 'p');
    cout << (p_result.first - begin(sorted_strings)) << " " << (p_result.second - begin(sorted_strings)) << endl;
    const auto z_result = FindStartsWith(begin(sorted_strings), end(sorted_strings), 'z');
    cout << (z_result.first - begin(sorted_strings)) << " " << (z_result.second - begin(sorted_strings)) << endl;

    return 0;
}