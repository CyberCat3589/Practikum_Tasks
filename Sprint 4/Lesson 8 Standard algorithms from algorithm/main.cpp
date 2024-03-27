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
void PrintRange(It range_begin, It range_end) 
{
    for (auto it = range_begin; it != range_end; ++it) {
        cout << *it << " "s;
    }
    cout << endl;
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
    vector<typename RandomIt::value_type> temp(range_begin, range_end);

    int range_length = range_end - range_begin;
    auto mid = temp.begin() + range_length / 2;

    if(distance(temp.begin(), mid) != 1) MergeSort(temp.begin(), mid);
    if(distance(mid, temp.end()) != 1) MergeSort(mid, temp.end());

    merge(temp.begin(), mid, mid, temp.end(), range_begin);
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

   vector<int> test_vector(10);
    // iota             -> http://ru.cppreference.com/w/cpp/algorithm/iota
    // Заполняет диапазон последовательно возрастающими значениями
    iota(test_vector.begin(), test_vector.end(), 1);
    // random_shuffle   -> https://ru.cppreference.com/w/cpp/algorithm/random_shuffle
    // Перемешивает элементы в случайном порядке
    random_shuffle(test_vector.begin(), test_vector.end());
    // Выводим вектор до сортировки
    PrintRange(test_vector.begin(), test_vector.end());
    // Сортируем вектор с помощью сортировки слиянием
    MergeSort(test_vector.begin(), test_vector.end());
    // Выводим результат
    PrintRange(test_vector.begin(), test_vector.end());
   
    return 0;
}