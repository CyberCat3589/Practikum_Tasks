#pragma once

#include <array>
#include <stdexcept>

template <typename T, size_t N> class StackVector
{
  public:
    explicit StackVector(size_t a_size = 0)
    {
        if (a_size > Capacity())
        {
            throw std::invalid_argument("invalid_argument");
        }
        size_ = a_size;
    }

    T& operator[](size_t index)
    {
        return array_[index];
    }

    const T& operator[](size_t index) const
    {
        return array_[index];
    }

    typename std::array<T, N>::iterator begin() noexcept
    {
        return array_.begin();
    }

    typename std::array<T, N>::iterator end() noexcept
    {
        auto it_first = array_.begin();
        auto it_last = size_;
        auto nx = std::next(it_first, it_last);
        return nx;
    }

    typename std::array<T, N>::const_iterator begin() const noexcept
    {
        return array_.begin();
    }

    typename std::array<T, N>::const_iterator end() const noexcept
    {
        auto it_first = array_.begin();
        auto it_last = size_;
        auto nx = std::next(it_first, it_last);
        return nx;
    }

    size_t Size() const
    {
        return size_;
    }
    size_t Capacity() const
    {
        return array_.size();
    }

    void PushBack(const T& value)
    {
        if (size_ == Capacity())
        {
            throw std::overflow_error("no space");
        }
        else
        {
            array_[size_] = value;
            ++size_;
        }
    }

    T PopBack()
    {
        if (size_ == 0)
        {
            throw std::underflow_error("no elements");
        }
        else
        {
            --size_;
            return array_[size_];
        }
    }

  private:
    std::array<T, N> array_;
    size_t size_{};
};