#include <iostream>
#include <vector>
#include <set>
#include <map>

using namespace std;

// переопределение оператора << для функции Print
template <typename First, typename Second>
ostream& operator<<(ostream& out, const pair<First, Second>& pair)
{
    return out << '(' << pair.first << ", " << pair.second << ')';
}

// вывод элементов контейнера
template <typename Container>
void Print(ostream& out, const Container& container)
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
}

// для векторов
template <typename Term>
ostream& operator<<(ostream& out, const vector<Term>& container)
{
    out << '[';
    Print(out, container);
    out << ']';
    return out;
}

// для множеств
template <typename Term>
ostream& operator<<(ostream& out, const set<Term>& container)
{
    out << '{';
    Print(out, container); 
    out << '}';
    return out;
}

// для словарей
template <typename Element1, typename Element2>
ostream& operator<<(ostream& out, const map<Element1, Element2>& container)
{
    out << '<';
    Print(out, container); 
    out << '>';
    return out;
}

int main() 
{
    const set<string> cats = {"Мурка"s, "Белка"s, "Георгий"s, "Рюрик"s};
    cout << cats << endl;
    const vector<int> ages = {10, 5, 2, 12};
    cout << ages << endl;
    const map<string, int> cat_ages = {
        {"Мурка"s, 10}, 
        {"Белка"s, 5},
        {"Георгий"s, 2}, 
        {"Рюрик"s, 12}
    };
    cout << cat_ages << endl;

    return 0;
}