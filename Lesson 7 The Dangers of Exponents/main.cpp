#include <cstdint>
#include <iostream>
#include "../Lesson 3 Measuring time/log_duration.h"

using namespace std;

// упростите эту экспоненциальную функцию,
// реализовав линейный алгоритм
int64_t T(int i) 
{
    if (i <= 1) return 0;
    if (i == 2) return 1;
    
    int prev0 = 0, prev1 = 0, prev2 = 1;
    int next;

    for(int t = 1; t < i - 1; ++t)
    {
        next = prev0 + prev1 + prev2;
        prev0 = prev1;
        prev1 = prev2;
        prev2 = next;
    }

    return prev2;
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

        {
            LOG_DURATION("Time");
            cout << "Ti = "s << T(i) << endl;
        }
    }
}