#include <algorithm>
#include <iostream>
#include <vector>
#include <random>

#include "../Lesson 3 Measuring time/log_duration.h"

using namespace std;

// bool TestPermut(const vector<int>& v1, const vector<int>& v2)
// {
//     LOG_DURATION("Original");
//     // если они разной длины, элементы заведомо разные
//     if (v1.size() != v2.size())
//     {
//         return false;
//     }

//     for (int i : v1)
//     {
//         // проверяем, что каждый элемент первого вектора
//         // содержится одинаковое количество раз в обоих векторах
//         if (count(v1.begin(), v1.end(), i) != count(v2.begin(), v2.end(), i))
//         {
//             return false;
//         }
//     }

//     return true;
// }

bool TestPermut(const vector<int>& v1, const vector<int>& v2)
{
    LOG_DURATION("Modified");
    vector<int> v1_copy = v1;
    vector<int> v2_copy = v2;

    // если они разной длины, элементы заведомо разные
    if (v1.size() != v2.size())
    {
        return false;
    }

    sort(v1_copy.begin(), v1_copy.end());
    sort(v2_copy.begin(), v2_copy.end());

    return v1_copy == v2_copy;
}

int main()
{
    std::mt19937 g;

    int n;
    cin >> n;
    vector<int> v1, v2;
    v1.reserve(n);
    v2.reserve(n);

    for (int i = 0; i < n; ++i)
    {
        v1.push_back(rand());
        v2.push_back(rand());
    }

    // оба вектора случайны, вряд ли они совпадут
    cout << "Random vectors match? "s << flush;
    cout << (TestPermut(v1, v2) ? "Yes"s : "No"s) << endl;

    // делаем один перестановкой другого явным образом
    v2 = v1;
    shuffle(v2.begin(), v2.end(), g);
    cout << "Permuted vectors match? "s << flush;
    cout << (TestPermut(v1, v2) ? "Yes"s : "No"s) << endl;
}