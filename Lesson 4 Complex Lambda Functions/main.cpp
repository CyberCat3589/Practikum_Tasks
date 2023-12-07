#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

vector<int> ReadNumbers() 
{
    int count;
    cin >> count;

    vector<int> numbers;
    for (int i = 0; i < count; ++i) 
    {
        int number;
        cin >> number;
        numbers.push_back(number);
    }

    return numbers;
}

void PrintNumbers(const vector<int>& numbers) 
{
    for (auto number : numbers) 
    {
        cout << number << " "s;
    }
}

int main() 
{
    vector<int> numbers = ReadNumbers();

    sort(numbers.begin(), numbers.end(), [](int n1, int n2) 
    {
        if((n1 % 2 == 0) && (n2 % 2 == 0)) return n1 < n2;
        
        if((n1 % 2 == 0) && (n2 % 2 != 0)) return true;

        if((n1 % 2 != 0) && (n2 % 2 == 0)) return false;

        if((n1 % 2 != 0) && (n2 % 2 != 0)) return n1 > n2;
        return true;
    });

    PrintNumbers(numbers);
}