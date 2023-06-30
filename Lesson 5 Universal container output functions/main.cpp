#include <iostream>
#include <vector>

using namespace std;

template <typename Term>
ostream& operator<<(ostream& out, const vector<Term>& container)
{
    for(auto element : container)
    {
        out << element << " "s;
    }

    return out;
}

int main() 
{
    const vector<int> ages = {10, 5, 2, 12};
    cout << ages << endl;
    return 0;
}