#include <iostream>
#include <math.h>

using namespace std;

int Fibonacci(int num)
{
    if (num == 0 || num == 1) return num;
     
    return Fibonacci(num - 1) + Fibonacci(num - 2);
}

bool IsPowOfTwo(int num) 
{
    if (num == 0) 
    {
        return false;
    }

    if (num == 1) 
    {
        return true;
    }

    if (num % 2 == 0) 
    {
        return IsPowOfTwo(num / 2);
    }
    return false;
}

int main() 
{
    //cout << Fibonacci(6) << endl;

    int result = IsPowOfTwo(1024);
    cout << result << endl;
}