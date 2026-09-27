#ifndef STACKLIST_H
#define STACKLIST_H
#include <exception>
#include <string>
#include <iostream>

class StackUnderflow : public std::exception
{
public:
    StackUnderflow() : reason_("Stack underflow")
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
class Stack
{
public:
    virtual ~Stack() = default;
    virtual void push(const T& val) = 0;
    virtual T pop() = 0;
    virtual bool isEmpty() const = 0;

};

template <class T>
class StackList : public Stack<T>
{
public:
    StackList() : head_(nullptr)
    { }
    ~StackList()
    {
        while (head_ != nullptr)
        {
            Node* temp = head_;
            head_ = head_->next_;
            delete temp;
        }
    }
    StackList(const StackList& other) : head_(nullptr)
    {
        if (other.head_ == nullptr)
        {
            return;
        }

        Node* currentOther = other.head_;
        Node* last = nullptr;
        try
        {
            while (currentOther != nullptr)
            {
                Node* newNode = new Node(currentOther->data_);
                newNode->next_ = nullptr;

                if (last == nullptr)
                {
                    head_ = newNode;
                }
                else
                {
                    last->next_ = newNode;
                }
                last = newNode;
                currentOther = currentOther->next_;
            }
        }
        catch (...)
        {
            while (head_ != nullptr)
            {
                Node* temp = head_;
                head_ = head_->next_;
                delete temp;
            }
            throw;
        }
    }
    StackList(StackList&& obj) : head_(obj.head_)
    {
        obj.head_ = nullptr;
    }
    StackList& operator=(const StackList& obj)
    {
        if (this != &obj)
        {
            StackList temp(obj);
            swap(temp);
        }
        return *this;
    }
    StackList& operator=(StackList&& obj) noexcept
    {
        if (this != &obj)
        {
            StackList temp(std::move(obj));
            swap(temp);
        }
        return *this;
    }
    void push(const T& val) override
    {
        try
        {
            Node* temp = new Node(val);
            temp->next_ = head_;
            head_ = temp;
        }
        catch (const std::bad_alloc& err)
        {
            std::cerr << err.what();
            throw;
        }
    }
    T pop() override
    {
        if (isEmpty())
        {
            throw StackUnderflow();
        }
        T result = head_->data_;
        Node* del = head_;
        head_ = head_->next_;
        delete del;
        return result;
    }
    bool isEmpty() const override
    {
        return head_ == nullptr;
    }
    void swap(StackList& other) noexcept
    {
        std::swap(head_, other.head_);
    }
private:
    struct Node
    {
        T data_;
        Node* next_;
        Node(const T& val) : data_(val),
            next_(nullptr)
        { }
    };
    Node* head_;
};



#endif