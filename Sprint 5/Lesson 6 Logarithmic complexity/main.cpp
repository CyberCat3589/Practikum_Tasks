#include <iostream>

using namespace std;

template <typename F>
int FindFloor(int n, F drop) 
{
    int a = 1;
    int b = n;
    int mid = 0;

    while (a != b)
    {
        mid = (a + b) / 2;
        if(drop(mid))
        {
            b = mid;
        }
        else
        {
            a = mid + 1;
        }
    }
    
    return a;
}

int main() 
{
    int n,t; // кол-во этажей и этаж, при котором drop == true
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