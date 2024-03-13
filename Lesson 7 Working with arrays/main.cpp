#include <cassert>
#include <vector>

template <typename T> void ReverseArray(T* start, size_t size)
{
    // Напишите тело функции самостоятельно
}

int main()
{
    using namespace std;

    vector<int> v = {1, 2};
    ReverseArray(v.data(), v.size());
    assert(v == (vector<int>{2, 1}));
}