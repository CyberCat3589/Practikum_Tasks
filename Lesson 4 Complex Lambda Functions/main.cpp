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
        /*
           Напишите тело лямбда-функции самостоятельно.
           Сначала должны располагаться чётные числа в порядке возрастания,
           а следом за ними — нечётные числа в порядке убывания
        */
    });

    PrintNumbers(numbers);
}