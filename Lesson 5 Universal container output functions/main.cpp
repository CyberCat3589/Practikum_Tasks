#include <iostream>
#include <vector>

using namespace std;

template <typename Term>
ostream& operator<<(ostream& out, const vector<Term>& container)
{
    bool first_iter = true;

    for(auto element : container)
    {
        if(first_iter)
        {
            out << element;
            first_iter = false;
        }
        else
        {
            out << ", "s << element;
        }
    }

    return out;
}

int main() 
{
    const vector<int> ages = {10, 5, 2, 12};
    cout << ages << endl;
    return 0;
}