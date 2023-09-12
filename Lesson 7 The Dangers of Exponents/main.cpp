#include <cstdint>
#include <iostream>

using namespace std;

// упростите эту экспоненциальную функцию,
// реализовав линейный алгоритм
int64_t T(int i) 
{
    if (i <= 1) 
    {
        return 0;
    }
    if (i == 2) 
    {
        return 1;
    }

    return T(i - 1) + T(i - 2) + T(i - 3);
}

int main() 
{
    int i;

    while (true) {
        cout << "Enter index: "s;
        if (!(cin >> i)) 
        {
            break;
        }

        cout << "Ti = "s << T(i) << endl;
    }
}