#include <cstdint>
#include <iostream>
#include <limits>
#include <optional>

using namespace std;

template <typename T> optional<T> SafeAdd(T a, T b)
{
    if (a > 0 && b > 0)
    {
        if (a > numeric_limits<T>::max() - b)
        {
            return nullopt;
        }
    }
    else if (a < 0 && b < 0)
    {
        if (a < numeric_limits<T>::min() - b)
        {
            return nullopt;
        }
    }
    return a + b;
}

int main()
{
    int64_t a;
    int64_t b;
    cin >> a >> b;
    auto sum = SafeAdd(a, b);
    if (sum.has_value())
    {
        cout << sum.value();
    }
    else
        cout << "Overflow!" << endl;
}