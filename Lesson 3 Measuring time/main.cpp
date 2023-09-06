#include <cstdlib>
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

#include "log_duration.h"

using namespace std;

vector<int> ReverseVector(const vector<int>& source_vector) 
{
    vector<int> res;

    for (int i : source_vector) 
    {
        res.insert(res.begin(), i);
    }

    return res;
}

vector<int> ReverseVector2(const vector<int>& source_vector) 
{
    vector<int> res;

    // будем проходить source_vector задом наперёд
    // с помощью обратного итератора
    for (auto iterator = source_vector.rbegin(); iterator != source_vector.rend(); ++iterator) 
    {
        res.push_back(*iterator);
    }

    return res;
}

vector<int> ReverseVector3(const vector<int>& source_vector) 
{
    return {source_vector.rbegin(), source_vector.rend()};
}

vector<int> ReverseVector4(const vector<int>& source_vector) 
{
    vector<int> res(source_vector.size());

    // реализация вашего собственного реверсирования

    return res;
}

void Operate() 
{
    vector<int> rand_vector;
    int n;

    cin >> n;
    rand_vector.reserve(n);

    for (int i = 0; i < n; ++i) {
        rand_vector.push_back(rand());
    }

    // код измерения тут
}

int main() {
    Operate();
    return 0;
}