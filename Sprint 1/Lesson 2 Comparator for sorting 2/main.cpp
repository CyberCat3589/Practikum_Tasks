#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> Input()
{
    int n = 0;
    string str;
    vector<string> input;
    
    cin >> n;
    
    for(int i = 0; i < n; ++i)
    {
        cin >> str;
        input.push_back(str);
    }
    
    return input;
}

int main() 
{

    vector<string> amount = Input();
    sort(amount.begin(), amount.end(), [](string str1, string str2)
         {
             return lexicographical_compare(str1.begin(), str1.end(), str2.begin(), str2.end(), [](char a, char b){ 
                 return tolower(a) < tolower(b); });
         });
    
    for(string str : amount)
    {
        cout << str << " ";
    }
    cout << endl;
    
}