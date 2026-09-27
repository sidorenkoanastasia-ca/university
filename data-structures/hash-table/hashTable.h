#ifndef HASHTABLE_H
#define HASHTABLE_H
#include "list.h"
#include <cstring>
#include <string>

class HashTable
{
public:
    HashTable() : size_(101), number_(0)
    {
        table_ = new DoubleOrderedDuplicateList<Record>*[size_];
        for (size_t i = 0; i < size_; ++i)
        {
            table_[i] = nullptr;
        }
    }

    HashTable(const HashTable& other) = delete;
    HashTable& operator=(const HashTable& other) = delete;

    HashTable(HashTable&& other) noexcept : size_(other.size_),
        table_(other.table_),
        number_(other.number_)
    {
        other.size_ = 0;
        other.table_ = nullptr;
        other.number_ = 0;
    }

    HashTable& operator=(HashTable&& other) noexcept
    {
        if (this != &other)
        {
            HashTable temp(std::move(other));
            swap(temp);
        }
        return *this;
    }

    ~HashTable()
    {
        for (size_t i = 0; i < size_; ++i)
        {
            delete table_[i];
        }
        delete[] table_;
    }

    size_t hashFunction(double key) const
    {
        unsigned long long bits;
        memcpy(&bits, &key, sizeof(key));
        bits ^= (bits >> 32);
        return bits % size_;
    }

    bool insert(double key, const std::string& value)
    {
        size_t index = hashFunction(key);

        Record record(key, value);

        if (table_[index] == nullptr)
        {
            table_[index] = new DoubleOrderedDuplicateList<Record>();
        }

        if (table_[index]->insert(record))
        {
            number_++;
            return true;
        }
        return false;
    }

    bool search(double key, std::string& value) const
    {
        size_t index = hashFunction(key);

        if (table_[index] == nullptr)
        {
            return false;
        }

        Record temp(key, "");
        Record result;

        if (!table_[index]->find(temp, result))
        {
            return false;
        }

        value = result.value_;
        return true;
    }

    bool remove(double key)
    {
        size_t index = hashFunction(key);

        if (table_[index] == nullptr)
        {
            return false;
        }

        Record temp(key, "");

        if (table_[index]->removeKey(temp, temp))
        {
            --number_;
            return true;
        }
        return false;
    }

    void print(std::ostream& out) const
    {
        for (size_t i = 0; i < size_; ++i)
        {
            if (table_[i] != nullptr && !table_[i]->isEmpty())
            {
                out << "Bucket " << i << ": ";
                table_[i]->printForward(out);
                out << '\n';
            }
        }
    }

    size_t getLongestChain() const
    {
        size_t maxChain = 0;
        for (size_t i = 0; i < size_; ++i)
        {
            if (table_[i] != nullptr)
            {
                size_t chainSize = table_[i]->size();
                if (chainSize > maxChain)
                {
                    maxChain = chainSize;
                }
            }
        }
        return maxChain;
    }

    size_t getNumber() const
    {
        return number_;
    }

    void swap(HashTable& other) noexcept
    {
        std::swap(size_, other.size_);
        std::swap(table_, other.table_);
        std::swap(number_, other.number_);
    }

private:
    struct Record
    {
        double key_;
        std::string value_;

        Record() : key_(0), value_("") {}
        Record(double k, const std::string& v) : key_(k), value_(v) {}

        bool operator==(const Record& other) const
        {
            return key_ == other.key_;
        }

        bool operator>(const Record& other) const
        {
            return key_ > other.key_;
        }

        bool operator<(const Record& other) const
        {
            return key_ < other.key_;
        }

        bool operator>=(const Record& other) const
        {
            return key_ >= other.key_;
        }

        bool operator<=(const Record& other) const
        {
            return key_ <= other.key_;
        }

        bool operator==(double k) const
        {
            return key_ == k;
        }

        bool operator>(double k) const
        {
            return key_ > k;
        }

        bool operator<(double k) const
        {
            return key_ < k;
        }

        bool operator>=(double k) const
        {
            return key_ >= k;
        }

        bool operator<=(double k) const
        {
            return key_ <= k;
        }

        friend std::ostream& operator<<(std::ostream& out, const Record& rec)
        {
            out << "(" << rec.key_ << ", " << rec.value_ << ")";
            return out;
        }
    };

    size_t size_;
    DoubleOrderedDuplicateList<Record>** table_;
    size_t number_;
};

#endif
