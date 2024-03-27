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
        if(elements_.IsEmpty() || (element < min_elements_.Peek()))
        {
            elements_.Push(element);
            min_elements_.Push(element);
        }
        else
        {
            elements_.Push(element);
            Type current_min = min_elements_.Peek();
            min_elements_.Push(current_min);
        }
    }

    void Pop() 
    {
        elements_.Pop();
        min_elements_.Pop();
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
        return min_elements_.Peek();
    }

    Type& PeekMin() 
    {
        return min_elements_.Peek();
    }

private:

    Stack<Type> elements_;
    // возможно, здесь вам понадобится что-то изменить
    Stack<Type> min_elements_;
};

template <typename Type>
class SortedSack 
{
public:

    void Push(const Type& element) 
    {
        if(elements_.IsEmpty())
        {
            elements_.Push(element);
        }
        else
        {
            while(!elements_.IsEmpty() && element > elements_.Peek())
            {
                Type elem_move = elements_.Peek();
                temp_.Push(elem_move);
                elements_.Pop();
            }

            elements_.Push(element);

            while(!temp_.IsEmpty())
            {
                Type elem_move = temp_.Peek();
                elements_.Push(elem_move);
                temp_.Pop();
            }
        }
    }

    void Pop() 
    {
        elements_.Pop();
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
        elements_.Print();
    }

    uint64_t Size() const 
    {
        return elements_.Size();
    }

    bool IsEmpty() const 
    {
        return elements_.IsEmpty();
    }

private:

    Stack<Type> elements_;
    Stack<Type> temp_;
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

    /*
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
    */

    SortedSack<int> sack;
    vector<int> values(5);

    // заполняем вектор для тестирования нашего класса
    iota(values.begin(), values.end(), 1);
    // перемешиваем значения
    random_shuffle(values.begin(), values.end());

    // заполняем класс и проверяем, что сортировка сохраняется после каждой вставки
    for (int i = 0; i < 5; ++i) 
    {
        cout << "Вставляемый элемент = "s << values[i] << endl;
        sack.Push(values[i]);
        sack.Print();
    }
}