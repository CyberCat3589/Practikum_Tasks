#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

void PrintSpacesPositions(string& str) 
{
    auto iter_pos = find(str.begin(), str.end(), ' ');
    while(iter_pos != str.end())
    {
        
    }
}

int main() 
{
    string str = "He said: one and one and one is three"s;
    PrintSpacesPositions(str);
    return 0;
} 