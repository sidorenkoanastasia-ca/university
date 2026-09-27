#ifndef QUEUERING_H
#define QUEUERING_H
#include <iostream>
#include <exception>
#include <string>

class WrongQueueSize : public std::exception
{
public:
    WrongQueueSize() : reason_("Wrong Queue Size")
    {
    }
    const char* what() const override
    {
        return reason_.c_str();
    }
private:
    const std::string reason_;
};

class QueueOverflow : public std::exception
{
public:
    QueueOverflow() : reason_("Queue overflow")
    {
    }
    const char* what() const override
    {
        return reason_.c_str();
    }
private:
    const std::string reason_;
};

class QueueUnderflow : public std::exception
{
public:
    QueueUnderflow() : reason_("Queue underflow")
    {
    }
    const char* what() const override
    {
        return reason_.c_str();
    }
private:
    const std::string reason_;
};

template <class T>
class Queue
{
public:
    virtual ~Queue() = default;
    virtual void enQueue(const T& e) = 0;
    virtual T deQueue() = 0;
    virtual bool isEmpty() const = 0;
};

template <class T>
class QueueRing : public Queue<T>
{
public:
    QueueRing(int size) : head_(0),
        tail_(0),
        size_(size)
    { 
        if (size <= 0)
        {
            throw WrongQueueSize();
        }
        queue_ = new T[size];
    }
    QueueRing(const QueueRing& other) : head_(other.head_),
        tail_(other.tail_),
        size_(other.size_)
    {
        queue_ = new T[size_];
        try
        {
            for (int i = 0; i < size_; ++i)
            {
                queue_[i] = other.queue_[i];
            }
        }
        catch (...)
        {
            delete[] queue_;
            throw;
        }
    }
    QueueRing(QueueRing&& other) : queue_(other.queue_),
        head_(other.head_),
        tail_(other.tail_),
        size_(other.size_)
    {
        other.queue_ = nullptr;
        other.head_ = 0;
        other.tail_ = 0;
        other.size_ = 0;
    }
    QueueRing& operator=(const QueueRing& other)
    {
        if (this != &other)
        {
            QueueRing temp(other);
            swap(temp);
        }
        return *this;
    }
    QueueRing& operator=(QueueRing&& other) noexcept
    {
        if (this != &other)
        {
            QueueRing temp(std::move(other));
            swap(temp);
        }
        return *this;
    }
    ~QueueRing()
    {
        delete[] queue_;
    }
    void enQueue(const T& e) override
    {
        if (head_ == (tail_ + 1) % size_)
        {
            throw QueueOverflow();
        }
        queue_[tail_] = e;
        tail_ = (tail_ + 1) % size_;
    }
    T deQueue() override
    {
        if (tail_ == head_)
        {
            throw QueueUnderflow();
        }
        T result = queue_[head_];
        head_ = (head_ + 1) % size_;
        return result;
    }
    bool isEmpty() const override
    {
        return head_ == tail_;
    }
    void swap(QueueRing& other) noexcept
    {
        std::swap(queue_, other.queue_);
        std::swap(head_, other.head_);
        std::swap(tail_, other.tail_);
        std::swap(size_, other.size_);
    }
private:
    T* queue_;
    int head_;
    int tail_;
    int size_;
};



#endif