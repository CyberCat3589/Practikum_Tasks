#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>
#include <vector>

// не меняйте файлы xml.h и xml.cpp
#include "xml.h"

using namespace std;

struct Spending
{
    string category;
    int amount;
};

int CalculateTotalSpendings(const vector<Spending>& spendings)
{
    return accumulate(spendings.begin(), spendings.end(), 0,
                      [](int current, const Spending& spending) { return current + spending.amount; });
}

string FindMostExpensiveCategory(const vector<Spending>& spendings)
{
    assert(!spendings.empty());
    auto compare_by_amount = [](const Spending& lhs, const Spending& rhs) { return lhs.amount < rhs.amount; };
    return max_element(begin(spendings), end(spendings), compare_by_amount)->category;
}

vector<Spending> LoadFromXml(istream& input)
{
    vector<Spending> result;
    Document doc = Load(input);
    for(auto node : doc.GetRoot().Children())
    {
        Spending temp;
        temp.category = node.AttributeValue<string>("category"); 
        temp.amount = node.AttributeValue<int>("amount");
        result.push_back(move(temp));
    }
    return result;
}

int main()
{
    const vector<Spending> spendings = LoadFromXml(cin);
    cout << "Total "sv << CalculateTotalSpendings(spendings) << '\n';
    cout << "Most expensive is "sv << FindMostExpensiveCategory(spendings) << '\n';
}