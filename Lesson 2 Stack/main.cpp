#include <iostream>
#include <vector>
#include <cstdint>

using namespace std;

template <typename It>
void PrintRange(It range_begin, It range_end) 
{
    for (auto it = range_begin; it != range_end; ++it) 
    {
        cout << *it << " "s;
    }
    cout << endl;
}

template <typename Type>
class Stack 
{
public:

    void Push(const Type& element) 
    {
        elements_.push_back(element);
    }

    void Pop() 
    {
        elements_.pop_back();
    }

    const Type& Peek() const 
    {
        return elements_.back();
    }

    Type& Peek() 
    {
        return elements_.back();
    }

    void Print() const 
    {
        for(auto it = elements_.begin(); it != elements_.end(); ++it)
        {
            cout << *it << " ";
        }
        cout << endl;
    }

    uint64_t Size() const 
    {
        return distance(elements_.begin(), elements_.end());
    }

    bool IsEmpty() const 
    {
        return elements_.empty();
    }

private:
    vector<Type> elements_;
};

int main() 
{
    Stack<int> stack;
    
    for (uint32_t i = 0; i < 10; ++i) 
    {
        stack.Push(i);
        stack.Print();
    }
    while (!stack.IsEmpty()) 
    {
        stack.Pop();
        stack.Print();
    }
}