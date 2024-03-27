#include <cstdlib>
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

#include "log_duration.h"

using namespace std;

int CountPops(const vector<int>& source_vector, int begin, int end) 
{
    int res = 0;

    for (int i = begin; i < end; ++i) 
    {
        if (source_vector[i]) 
        {
            ++res;
        }
    }

    return res;
}

void AppendRandom(vector<int>& v, int n) 
{
    v.reserve(n);
    for (int i = 0; i < n; i += 15) {
        int number = rand();

        // мы можем заполнить 15 элементов вектора,
        // но не более, чем нам осталось до конца:
        int count = min(15, n - i);

        for (int j = 0; j < count; ++j)
            // таким образом, получим j-й бит числа.
            // операцию побитового сдвига вы уже видели в этой программе
            // на этот раз двигаем вправо, чтобы нужный бит оказался самым последним
            v.push_back((number >> j) % 2);
    }
}

vector<int> ReverseVector(const vector<int>& source_vector) 
{
    return {source_vector.rbegin(), source_vector.rend()};
}

void Operate() 
{
    LOG_DURATION("Total"s);
    vector<int> random_bits;
    vector<int> reversed_bits;

    // операция << для целых чисел это сдвиг всех бит в двоичной
    // записи числа. Запишем с её помощью число 2 в степени 17 (131072)
    static const int N = 1 << 17;

    {
        LOG_DURATION("Append random"s);
        //LogDuration time_log("Append random"s);
        // заполним вектор случайными числами 0 и 1
        AppendRandom(random_bits, N);
    }

    {
        LOG_DURATION("Reverse"s);
        // перевернём вектор задом наперёд
        reversed_bits = ReverseVector(random_bits);
    }

    {
        LOG_DURATION("Counting"s);
        // посчитаем процент единиц на начальных отрезках вектора
        for (int i = 1, step = 1; i <= N; i += step, step *= 2) 
        {
            // чтобы вычислить проценты, мы умножаем на литерал 100. типа double;
            // целочисленное значение функции CountPops при этом автоматически
            // преобразуется к double, как и i
            double rate = CountPops(reversed_bits, 0, i) * 100. / i;
            cout << "After "s << i << " bits we found "s << rate << "% pops"s << endl;
        }
    }
}

int main() 
{
    Operate();
    return 0;
}