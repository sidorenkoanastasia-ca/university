#ifndef VECTOR_H
#define VECTOR_H


template <class T>
class Vector
{
public:
    //конструкторы и деструктор
    Vector() : data_(nullptr),
        size_(0), 
        capacity_(0)
    { }
    Vector(size_t n) : data_(nullptr), 
        size_(0), 
        capacity_(0)
    {
        if (n == 0)
        {
            return;
        }
        T* new_data = allocator_.allocate(n);
        try 
        {
            allocator_.construct_range(new_data, n);
        }
        catch (...) 
        {
            allocator_.deallocate(new_data);
            throw;
        }

        data_ = new_data;
        size_ = n;
        capacity_ = n;
    }
    Vector(size_t n, const T& value) : data_(nullptr),
        size_(0), 
        capacity_(0)
    {
        if (n == 0)
        {
            return;
        }
        T* new_data = allocator_.allocate(n);

        try
        {
            allocator_.construct_range(new_data, n, value);
        }
        catch (...)
        {
            allocator_.deallocate(new_data);
            throw;
        }

        data_ = new_data;
        size_ = n;
        capacity_ = n;
    }

    Vector(const Vector& other) : data_(nullptr), 
        size_(0), 
        capacity_(0)
    {
        if (other.size_ == 0)
        {
            return;
        }

        T* new_data = allocator_.allocate(other.size_);
        try
        {
            allocator_.construct_range(new_data, other.size_, other.data_);
        }
        catch (...)
        {
            allocator_.deallocate(new_data);
            throw;
        }

        data_ = new_data;
        size_ = other.size_;
        capacity_ = other.size_;
    }
    Vector(Vector&& other) noexcept :
        data_(other.data_),
        size_(other.size_),
        capacity_(other.capacity_)
    {
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }
    ~Vector()
    {
        allocator_.destroy_range(data_, size_);
        allocator_.deallocate(data_);
    }

    //перегруженные операторы присваивания
    Vector& operator=(const Vector& other)
    { 
        if (this != &other)
        {
            Vector temp(other);
            swap(temp);
        }
        return *this;
    }
    Vector& operator=(Vector&& other) noexcept
    {
        if (this != &other)
        {
            Vector temp(std::move(other));
            swap(temp);
        }
        return *this;
    }

    //операторы доступа
    T& operator[](size_t index)
    {
        return data_[index];
    }
    const T& operator[](size_t index) const
    {
        return data_[index];
    }

    T& at(size_t index)
    {
        if (index >= size_)
        {
            throw std::out_of_range("Error: index is out of range\n");
        }
        return data_[index];
    }
    const T& at(size_t index) const 
    {
        if (index >= size_)
        {
            throw std::out_of_range("Error: index is out of range\n");
        }
        return data_[index];
    }

    const T& front() const
    {
        if (empty())
        {
            throw std::out_of_range("Error: index is out of range\n");
        }
        return data_[0];
    }
    T& front()
    {
        if (empty())
        {
            throw std::out_of_range("Error: index is out of range\n");
        }
        return data_[0];
    }
    const T& back() const
    {
        if (empty())
        {
            throw std::out_of_range("Error: index is out of range\n");
        }
        return data_[size_ - 1];
    }
    T& back()
    {
        if (empty())
        {
            throw std::out_of_range("Error: index is out of range\n");
        }
        return data_[size_ - 1];
    }


    //информация о состоянии
    size_t size() const noexcept
    {
        return size_;
    }
    size_t capacity() const noexcept
    {
        return capacity_;
    }
    bool empty() const noexcept
    {
        return size_ == 0;
    }

    //вставка элементов 
    void push_back(const T& value)
    {
        if (size_ == capacity_)
        {
            reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        }
        allocator_.construct(data_ + size_, value);
        ++size_;
    }

    void push_back(T&& value)
    {
        if (size_ == capacity_)
        {
            reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        }
        allocator_.construct(data_ + size_, std::move(value));
        ++size_;
    }

    void insert(size_t index, const T& value)
    {
        if (index > size_)
        {
            throw std::out_of_range("Error: index out of range");
        }
        if (index == size_)
        {
            push_back(value);
            return;
        }
        size_t new_capacity = capacity_ == 0 ? 1 : capacity_ * 2;
        Vector temp;
        temp.reserve(new_capacity);

        for (size_t i = 0; i < index; ++i)
        {
            temp.push_back(data_[i]);
        }
        temp.push_back(value);
        for (size_t i = index; i < size_; ++i)
        {
            temp.push_back(std::move_if_noexcept(data_[i]));
        }
        swap(temp);
    }

    void insert(size_t index, T&& value)
    {
        if (index > size_)
        {
            throw std::out_of_range("Error: index out of range");
        }
        if (index == size_)
        {
            push_back(std::move(value));
            return;
        }
        size_t new_capacity = capacity_ == 0 ? 1 : capacity_ * 2;
        Vector temp;
        temp.reserve(new_capacity);

        for (size_t i = 0; i < index; ++i)
        {
            temp.push_back(data_[i]);
        }
        temp.push_back(std::move(value));
        for (size_t i = index; i < size_; ++i)
        {
            temp.push_back(std::move_if_noexcept(data_[i]));
        }
        swap(temp);
    }

    //удаление элементов
    void pop_back()
    {
        if (size_ > 0)
        {
            allocator_.destroy(data_ + size_ - 1);
            --size_;
        }
    }
    void clear()
    {
        allocator_.destroy_range(data_, size_);
        size_ = 0;
    }
    void erase(size_t index)
    {
        if (index >= size_)
        {
            throw std::out_of_range("Error: index out of range");
        }

        Vector temp;
        temp.reserve(capacity_);

        for (size_t i = 0; i < index; ++i)
        {
            temp.push_back(std::move_if_noexcept(data_[i]));
        }
        for (size_t i = index+1; i < size_; ++i)
        {
            temp.push_back(std::move_if_noexcept(data_[i]));
        }
        swap(temp);
    }
    void erase(size_t first, size_t last)
    {
        if (first > last || last >= size_)
        {
            throw std::out_of_range("Error: Invalid range\n");
        }
        Vector temp;
        temp.reserve(capacity_);

        for (size_t i = 0; i < first; ++i)
        {
            temp.push_back(std::move_if_noexcept(data_[i]));
        }
        for (size_t i = last + 1; i < size_; ++i)
        {
            temp.push_back(std::move_if_noexcept(data_[i]));
        }
        swap(temp);
    }


    //изменение размера
    void reserve(size_t new_capacity)
    {
        if (new_capacity <= capacity_)
        {
            return;
        }
        T* new_data = allocator_.allocate(new_capacity);
        try
        {
            allocator_.construct_range(new_data, size_, data_);
        }
        catch (...)
        {
            allocator_.deallocate(new_data);
            throw;
        }
        allocator_.destroy_range(data_, size_);
        allocator_.deallocate(data_);
        data_ = new_data;
        capacity_ = new_capacity;
    }

    void resize(size_t new_size)
    {
        if (new_size < size_)
        {
            allocator_.destroy_range(data_ + new_size, size_ - new_size);
        }
        else if (new_size > size_)
        {
            if (new_size > capacity_)
            {
                size_t new_cap = std::max(capacity_ * 2, new_size);
                reserve(new_cap);
            }
            try
            {
                allocator_.construct_range(data_ + size_, new_size - size_);
            }
            catch (...)
            {
                throw;
            }
        }
        size_ = new_size; 
    }
    void resize(size_t new_size, const T& value)
    {
        if (new_size < size_)
        {
            allocator_.destroy_range(data_ + new_size, size_ - new_size);
        }
        else if (new_size > size_)
        {
            if (new_size > capacity_)
            {
                size_t new_cap = std::max(capacity_ * 2, new_size);
                reserve(new_cap);
            }
            try
            {
                allocator_.construct_range(data_ + size_, new_size - size_, value);
            }
            catch (...)
            {
                throw;
            }
        }
        size_ = new_size;
    }
    void shrink_to_fit()
    {
        if (size_ == capacity_)
        {
            return;
        }
        if (size_ == 0)
        {
            allocator_.deallocate(data_);
            data_ = nullptr;
            capacity_ = 0;
            return;
        }
        T* new_data = allocator_.allocate(size_);

        try 
        {
            allocator_.construct_range(new_data, size_, data_);  
        }
        catch (...) 
        {
            allocator_.deallocate(new_data);
            throw;
        }

        allocator_.destroy_range(data_, size_);
        allocator_.deallocate(data_);

        data_ = new_data;
        capacity_ = size_;
    }

    //дополнительно - операции сравнения, swap
    bool operator==(const Vector& other) const
    {
        if (size_ != other.size_)
        {
            return false;
        }
        for (size_t i = 0; i < size_; ++i)
        {
            if (data_[i] != other.data_[i])
            {
                return false;
            }
        }
        return true;
    }
    bool operator!=(const Vector& other) const
    {
        return !(*this == other);
    }
    bool operator<(const Vector& other) const
    {
        for (size_t i = 0; i < size_ && i < other.size_; ++i)
        {
            if (data_[i] != other.data_[i])
            {
                return data_[i] < other.data_[i];
            }
        }
        return size_ < other.size_;
    }
    bool operator<=(const Vector& other) const
    {
        return (*this < other || *this == other);
    }
    bool operator>(const Vector& other) const
    {
        return !(*this < other);
    }
    bool operator>=(const Vector& other) const
    {
        return (*this > other || *this == other);
    }
    void swap(Vector& other) noexcept
    {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
    }

private:
    struct Allocator
    {
        T* allocate(size_t n)
        {
            if (n == 0)
            {
                return nullptr;
            }
            return static_cast<T*>(::operator new(n * sizeof(T)));
        }

        void deallocate(T* ptr)
        {
            if (ptr)
            {
                ::operator delete(static_cast<void*>(ptr));
            }
        }
        void construct(T* ptr)
        {
            new (ptr) T;
        }

        void construct(T* ptr, const T& value)
        {
            new (ptr) T(value);
        }

        void construct(T* ptr, T&& value)
        {
            new (ptr) T(std::move(value));
        }

        void destroy(T* ptr)
        {
            if (ptr)
            {
                ptr->~T();
            }
        }
        void destroy_range(T* begin, size_t count) noexcept
        {
            for (size_t i = 0; i < count; ++i)
            {
                destroy(begin + i);
            }
        }
        void construct_range(T* begin, size_t count) 
        {
            size_t constructed = 0;
            try
            {
                for (constructed = 0; constructed < count; ++constructed)
                {
                    construct(begin + constructed);
                }
            }
            catch (...) 
            {
                destroy_range(begin, constructed);
                throw;
            }
        }
        void construct_range(T* begin, size_t count, const T& value) 
        {
            size_t constructed = 0;
            try 
            {
                for (constructed = 0; constructed < count; ++constructed)
                {
                    construct(begin + constructed, value);
                }
            }
            catch (...) 
            {
                destroy_range(begin, constructed);
                throw;
            }
        }
        void construct_range(T* begin, size_t count, const T* src)
        {
            size_t constructed = 0;
            try
            {
                for (constructed = 0; constructed < count; ++constructed)
                {
                    construct(begin + constructed, src[constructed]);
                }
            }
            catch (...)
            {
                destroy_range(begin, constructed);
                throw;
            }
        }
        void construct_range(T* begin, size_t count, T* src)
        {
            size_t constructed = 0;
            try 
            {
                for (constructed = 0; constructed < count; ++constructed)
                {
                    construct(begin + constructed, std::move(src[constructed]));
                }
            }
            catch (...) 
            {
                destroy_range(begin, constructed);
                throw;
            }
        }
    }; 
    Allocator allocator_;
	T* data_;
	size_t size_;
	size_t capacity_;
};


template <class T>
void insertion_sort(Vector<T>& vector)
{
    size_t n = vector.size();
    for (size_t i = 1; i < n; ++i)
    {
        T key = vector[i];
        size_t j = i;
        while (j > 0 && key < vector[j - 1])
        {
            vector[j] = vector[j - 1];
            --j;
        }
        vector[j] = key;
    }
}


#endif
