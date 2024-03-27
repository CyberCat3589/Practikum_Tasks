#include <cassert>
#include <vector>
#include <cstddef>
#include <iostream>

template <typename T> 
void ReverseArray(T* start, size_t size)
{
    int j = size - 1;
    int i = 0;
    while(i < j)
    {
        T temp = *(start + i);
        *(start + i) = *(start + j);
        *(start + j) = temp;
        ++i;
        --j;
    }
}

void Print(std::vector<int> nums)
{
    for(int num : nums)
    {
        std::cout << num << std::endl;
    }
}

int main()
{
    using namespace std;

    vector<int> v = {1, 2, 3, 4, 5};
    ReverseArray(v.data(), v.size());
    //assert(v == (vector<int>{5, 4, 3, 2, 1}));
    Print(v);
}