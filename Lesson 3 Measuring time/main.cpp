#include <cstdlib>
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <log_duration.h>

using namespace std;

vector<int> ReverseVector(const vector<int>& source_vector) 
{
    vector<int> res;
    for (int i : source_vector) 
    {
        res.insert(res.begin(), i);
    }

    return res;
}

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
    for (int i = 0; i < n; ++i) 
    {
        // получаем случайное число с помощью функции rand.
        // с помощью (rand() % 2) получим целое число в диапазоне 0..1.
        // в C++ имеются более современные генераторы случайных чисел,
        // но в данном уроке не будем их касаться
        v.push_back(rand() % 2);
    }
}

void Operate() 
{
    vector<int> random_bits;

    // операция << для целых чисел это сдвиг всех бит в двоичной
    // записи числа. Запишем с её помощью число 2 в степени 17 (131072)
    static const int N = 1 << 17;

    const auto start_append_time = chrono::steady_clock::now();

    // заполним вектор случайными числами 0 и 1
    AppendRandom(random_bits, N);

    const auto end_append_time = chrono::steady_clock::now();
    const auto append_dur = end_append_time - start_append_time;

    cerr << "Append random: "s << chrono::duration_cast<chrono::milliseconds>(append_dur).count() << " ms"s << endl;

    const auto start_reverse_time = chrono::steady_clock::now();

    // перевернём вектор задом наперёд
    vector<int> reversed_bits = ReverseVector(random_bits);

    const auto end_reverse_time = chrono::steady_clock::now();
    const auto reversre_dur = end_reverse_time - start_reverse_time;

    cerr << "Reverse: "s << chrono::duration_cast<chrono::milliseconds>(reversre_dur).count() << " ms"s << endl;

    const auto start_counting_time = chrono::steady_clock::now();

    // посчитаем процент единиц на начальных отрезках вектора
    for (int i = 1, step = 1; i <= N; i += step, step *= 2) 
    {
        // чтобы вычислить проценты, мы умножаем на литерал 100. типа double;
        // целочисленное значение функции CountPops при этом автоматически
        // преобразуется к double, как и i
        double rate = CountPops(reversed_bits, 0, i) * 100. / i;
        cout << "After "s << i << " bits we found "s << rate << "% pops"s
             << endl;
    }

    const auto end_counting_time = chrono::steady_clock::now();
    const auto counting_dur = end_counting_time - start_counting_time;
    cerr << "Counting: "s << chrono::duration_cast<chrono::milliseconds>(counting_dur).count() << " ms"s << endl;
}

int main() 
{
    Operate();
    return 0;
}