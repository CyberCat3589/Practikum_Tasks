#include <chrono>
#include <thread>
#include <iostream>

using namespace std;
using namespace chrono;
using namespace literals;

int main()
{
    cout << "Ожидание 5s..."s << endl;
    const auto start_time = steady_clock::now();

    this_thread::sleep_for(seconds(5));
    const auto end_time = steady_clock::now();

    const auto dur = end_time - start_time;
    cerr << "Продолжительность сна: "s << duration_cast<milliseconds>(dur).count() << " ms"s << endl;

    cout << "В 10 часах " << duration_cast<nanoseconds>(10h).count() << " наносекунд" << endl;

    cout << "Ожидание завершено"s << endl;
}