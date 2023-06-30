#include <iostream>
#include <vector>
#include <set>

using namespace std;

// для векторов
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

// для множеств
template <typename Term>
ostream& operator<<(ostream& out, const set<Term>& container)
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
    // const vector<int> ages = {10, 5, 2, 12};
    // cout << ages << endl;

    const set<string> cats = {"Мурка"s, "Белка"s, "Георгий"s, "Рюрик"s};
    cout << cats << endl;

    return 0;
}