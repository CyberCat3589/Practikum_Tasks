#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

void PrintSpacesPositions(string& str) 
{
    auto iter_pos = find(str.begin(), str.end(), ' ');
    while(iter_pos != str.end())
    {
        cout << distance(str.begin(), iter_pos) << endl;
        iter_pos = find(next(iter_pos, 1), str.end(), ' ');
    }

    /*
    for (auto it = find(str.begin(), str.end(), ' '); it != str.end(); it = find(next(it), str.end(), ' ')) 
    {
        cout << distance(str.begin(), it) << endl;
    }*/
}

int main() 
{
    string str = "He said: one and one and one is three"s;
    PrintSpacesPositions(str);
    return 0;
} 