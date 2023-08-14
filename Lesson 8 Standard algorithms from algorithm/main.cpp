#include <algorithm>
#include <iostream>
#include <numeric>
#include <sstream>
#include <vector>

using namespace std;

// функция, записывающая элементы диапазона в строку
template <typename It>
string PrintRangeToString(It range_begin, It range_end) 
{
    // удобный тип ostringstream -> https://ru.cppreference.com/w/cpp/io/basic_ostringstream
    ostringstream out;
    for (auto it = range_begin; it != range_end; ++it) {
        out << *it << " "s;
    }
    out << endl;
    // получаем доступ к строке с помощью метода str для ostringstream
    return out.str();
}

template <typename It>
vector<string> GetPermutations(It range_begin, It range_end)
{
    vector<string> result;

    sort(range_begin, range_end, [](auto& a, auto& b) { return a < b; });

    result.push_back(PrintRangeToString(range_begin, range_end));

    while(next_permutation(range_begin, range_end))
    {
        result.push_back(PrintRangeToString(range_begin, range_end));
    }

    sort(result.begin(), result.end(), [](auto& a, auto& b) { return a > b; });

    return result;
}

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end)
{
    
}

int main() 
{
    /*vector<int> permutation(3);
    // iota             -> http://ru.cppreference.com/w/cpp/algorithm/iota
    // Заполняет диапазон последовательно возрастающими значениями
    iota(permutation.begin(), permutation.end(), 1);
    
   vector<int> permutation = {2,1,3};
    auto result = GetPermutations(permutation.begin(), permutation.end());
    for (const auto& s : result) {
        cout << s;
    }
    */
   
    return 0;
}