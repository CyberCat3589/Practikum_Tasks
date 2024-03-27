#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() 
{
    vector<string> words; // массив строк
    
    int elementsNum; // кол-во элементов
    cin >> elementsNum;

    // ввод строк
    while (elementsNum > 0)
    {
        string word;
        cin >> word;
        words.push_back(word);
        --elementsNum;
    }

    sort(words.begin(), words.end(),
    [](string& left, string& right)
    {
        return lexicographical_compare(
            left.begin(), left.end(), 
            right.begin(), right.end(),
            [](char& left, char& right){ return tolower(static_cast<unsigned char>(left)) < tolower(static_cast<unsigned char>(right)); });

    });

    // вывод отсортированного массива
    for(string word : words)
    {
        cout << word << " ";
    }
    
}