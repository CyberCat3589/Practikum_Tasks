#include <iostream>
#include <vector>
#include <cstdint>
#include <numeric>
#include <algorithm>

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

template <typename Type>
class StackMin 
{
public:

    void Push(const Type& element) 
    {
        // напишите реализацию метода
    }

    void Pop() 
    {
        // напишите реализацию метода
    }

    const Type& Peek() const 
    {
        return elements_.Peek();
    }

    Type& Peek() 
    {
        return elements_.Peek();
    }

    void Print() const 
    {
        // работу этого метода мы проверять не будем,
        // но если он вам нужен, то можете его реализовать
        elements_.Print();
    }

    uint64_t Size() const 
    {
        return elements_.size();
    }

    bool IsEmpty() const 
    {
        return elements_.IsEmpty();
    }

    const Type& PeekMin() const 
    {
        // напишите реализацию метода
    }

    Type& PeekMin() 
    {
        // напишите реализацию метода
    }

private:

    Stack<Type> elements_;
    // возможно, здесь вам понадобится что-то изменить
};

int main() 
{
    /*
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
    */

    StackMin<int> stack;
    vector<int> values(5);
    // заполняем вектор для тестирования нашего стека
    iota(values.begin(), values.end(), 1);
    // перемешиваем значения
    random_shuffle(values.begin(), values.end());
    // заполняем стек
    for (int i = 0; i < 5; ++i) 
    {
        stack.Push(values[i]);
    }
    
    // печатаем стек и его минимум, постепенно убирая из стека элементы
    while (!stack.IsEmpty()) 
    {
        stack.Print();
        cout << "Минимум = "s << stack.PeekMin() << endl;
        stack.Pop();
    }
}