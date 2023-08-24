#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <numeric>

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
        PrintRange(elements_.begin(), elements_.end());
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
class Queue 
{
public:

    void Push(const Type& element) 
    {
        stack1_.Push(element);
    }

    void Pop() 
    {
        MoveFromFirstStack();

        stack1_.Pop();

        MoveFromSecondStack();
    }

    Type Front() 
    {
        MoveFromFirstStack();

        Type front = stack1_.Peek();

        MoveFromSecondStack();

        return front;
    }

    uint64_t Size() const 
    {
        return stack1_.Size();
    }

    bool IsEmpty() const 
    {
        return stack1_.IsEmpty();
    }

private:
    Stack<Type> stack1_;
    Stack<Type> stack2_;

    void MoveFromFirstStack()
    {
        while(stack1_.Size() > 1)
        {
            Type elem_move = stack1_.Peek();
            stack2_.Push(elem_move);
            stack1_.Pop();
        }
    }

    void MoveFromSecondStack()
    {
        while (!stack2_.IsEmpty())
        {
            Type elem_move = stack2_.Peek();
            stack1_.Push(elem_move);
            stack2_.Pop();
        }
    }
};

int main() 
{
    Queue<int> queue;
    vector<int> values(5);

    // заполняем вектор для тестирования очереди
    iota(values.begin(), values.end(), 1);

    // перемешиваем значения
    random_shuffle(values.begin(), values.end());
    PrintRange(values.begin(), values.end());
    cout << "Заполняем очередь"s << endl;

    // заполняем очередь и выводим элемент в начале очереди
    for (int i = 0; i < 5; ++i) 
    {
        queue.Push(values[i]);
        cout << "Вставленный элемент "s << values[i] << endl;
        cout << "Первый элемент очереди "s << queue.Front() << endl;
    }
    cout << "Вынимаем элементы из очереди"s << endl;

    // выводим элемент в начале очереди и вытаскиваем элементы по одному
    while (!queue.IsEmpty()) 
    {
        // сначала будем проверять начальный элемент, а потом вытаскивать,
        // так как операция Front на пустой очереди не определена
        cout << "Будем вынимать элемент "s << queue.Front() << endl;
        queue.Pop();
    }
    return 0;
}