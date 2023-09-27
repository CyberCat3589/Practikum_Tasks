#include <algorithm>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

int EffectiveCount(const vector<int>& v, int n, int i) 
{
    // место для вашего решения
    bool good_case = false; // false - заглушка, расчитать
    int result_num = 0;
    if(good_case)
    {
        cout << "Using find_if" << endl;
        auto it = find_if(v.begin(), v.end(), [i](int num){ return num <= i; });
        result_num = it - v.begin();
    }
    else
    {
        cout << "Using upper_bound" << endl;
        auto it = upper_bound(v.begin(), v.end(), i);
        result_num = it - v.begin();
    }

    return result_num;
}

int main() 
{
    static const int NUMBERS = 1'000'000;
    static const int MAX = 1'000'000'000;

    mt19937 r;
    uniform_int_distribution<int> uniform_dist(0, MAX);

    vector<int> nums;
    for (int i = 0; i < NUMBERS; ++i) 
    {
        int random_number = uniform_dist(r);
        nums.push_back(random_number);
    }
    sort(nums.begin(), nums.end());

    int i;
    cin >> i;
    int result = EffectiveCount(nums, MAX, i);
    cout << "Total numbers before "s << i << ": "s << result << endl;
}