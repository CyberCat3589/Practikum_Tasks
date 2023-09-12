#include <iostream>

using namespace std;

template <typename F>
int FindFloor(int n, F drop) 
{
    // Переделайте этот алгоритм, имеющий линейную сложность.
    // В итоге должен получится логарифмический алгоритм.
    for (int i = 1; i < n; ++i) 
    {
        if (drop(i)) 
        {
            return i;
        }
    }

    return n;
}

int main() 
{
    int n,t;
    cout << "Enter n and target floor number: "s << endl;
    cin >> n >> t;

    int count = 0;
    int found = FindFloor(n, [t, &count](int f) 
    {
        ++count;
        return f >= t;
    });

    cout << "Found floor "s << found << " after "s << count << " drops"s;

    return 0;
}