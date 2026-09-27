#ifndef LINENUMBERS_H
#define LINENUMBERS_H

#include <iostream>

class LineNumbers
{
public:
    LineNumbers() : numbers_(nullptr), size_(0), capacity_(0)
    {
    }
    LineNumbers(int firstLine) : numbers_(nullptr), size_(0), capacity_(0)
    {
        add(firstLine);
    }
    LineNumbers(const LineNumbers& other) : numbers_(nullptr),
        size_(0), capacity_(0)
    {
        LineNumbers temp;
        if (other.size_ > 0)
        {
            temp.numbers_ = new int[other.size_];
            temp.capacity_ = other.size_;
            for (int i = 0; i < other.size_; ++i)
            {
                temp.numbers_[i] = other.numbers_[i];
            }
            temp.size_ = other.size_;
        }
        swap(temp);
    }

    LineNumbers& operator=(const LineNumbers& other)
    {
        if (this != &other)
        {
            LineNumbers temp(other);
            swap(temp);
        }
        return *this;
    }
    LineNumbers(LineNumbers&& other) noexcept : numbers_(other.numbers_), size_(other.size_),
        capacity_(other.capacity_)
    {
        other.numbers_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }
    LineNumbers& operator=(LineNumbers&& other) noexcept
    {
        if (this != &other)
        {
            LineNumbers temp(std::move(other));
            swap(temp);
        }
        return *this;
    }
    ~LineNumbers()
    {
        delete[] numbers_;
    }

    void swap(LineNumbers& other) noexcept
    {
        std::swap(numbers_, other.numbers_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
    }

    void add(int lineNum)
    {
        if (size_ > 0 && numbers_[size_ - 1] == lineNum)
        {
            return;
        }
        if (size_ >= capacity_)
        {
            int newCapacity = (capacity_ == 0) ? 4 : capacity_ * 2;
            int* newNumbers = new int[newCapacity];
            for (int i = 0; i < size_; ++i)
            {
                newNumbers[i] = std::move(numbers_[i]);
            }
            delete[] numbers_;
            numbers_ = newNumbers;
            capacity_ = newCapacity;
        }
        numbers_[size_] = lineNum;
        size_++;
    }

    void print(std::ostream& out) const
    {
        for (int i = 0; i < size_; ++i)
        {
            if (i > 0)
            {
                out << ", ";
            }
            out << numbers_[i];
        }
    }
    friend std::ostream& operator<<(std::ostream& out, const LineNumbers& ob)
    {
        for (int i = 0; i < ob.size_; ++i)
        {
            if (i > 0)
            {
                out << ", ";
            }
            out << ob.numbers_[i];
        }
        return out;
    }
    int getLine(int index) const
    {
        return (index >= 0 && index < size_) ? numbers_[index] : -1;
    }
    int size() const
    {
        return size_;
    }

private:
    int* numbers_;
    int size_;
    int capacity_;
};

#endif
