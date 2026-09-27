#include <iostream>
#include "String.h"
#include <stdexcept>

void String::swap(String& other) noexcept
{
	std::swap(data_, other.data_);
	std::swap(length_, other.length_);
	std::swap(capacity_, other.capacity_);

}

size_t String::length() const
{
	return length_;
}

bool String::empty() const 
{
	return length_ == 0;
}

void String::clear()
{
	String temp;
	swap(temp);
}

bool String::hasConsecutiveDuplicates() const
{
	if (length_ <= 1) 
	{
		return false;
	}
	for (size_t i = 0; i < length_ - 1; ++i)
	{
		if (data_[i] == data_[i + 1])
		{
			return true;
		}
	}
	return false;
}

String& String::operator=(const String& right) 
{
	if (this != &right)
	{
		String temp(right);
		swap(temp);
	}
	return *this;
}

String& String::operator=(String&& right) noexcept 
{
	if (this != &right)
	{
		String temp(std::move(right));
		swap(temp);
	}
	return *this;
}

String& String::operator=(const char* right) 
{
	String ob(right);
	swap(ob);
	return *this;
}

char& String::operator[](size_t index)
{
	if (index >= length_)
	{
		throw std::out_of_range("Error: index is out of range\n");
	}
	return data_[index];
}

const char& String::operator[](size_t index) const
{
	if (index >= length_)
	{
		throw std::out_of_range("Error: index is out of range\n");
	}
	return data_[index];
}

String String::operator+(const String& other) const
{
	String temp;
	int len = length_ + other.length_;
	if (len == 0)
	{
		return temp;
	}
	char* newData = new char[len+1];
	delete[] temp.data_;
	temp.data_ = newData;
	temp.length_ = len;
	temp.capacity_ = len + 1;
	if (length_ > 0)
	{
		for (size_t i = 0; i < length_; ++i)
		{
			temp.data_[i] = data_[i];
		}
	}
	if (other.length_ > 0)
	{
		for (size_t i = 0; i < other.length_; ++i)
		{
			temp.data_[length_ + i] = other.data_[i];
		}
	}
	temp.data_[temp.capacity_ - 1] = '\0';
	return temp;
}

String String::operator+(const char* str) const
{
	String ob(str);
	return *this + ob;
}

String& String::operator+=(const String& other)
{
	*this = *this + other;  
	return *this;
}

String& String::operator+=(const char* str)
{
	String ob(str);
	return *this += ob;
}

bool String::operator==(const String& other) const
{
	if (length_ != other.length_)
	{
		return false;
	}
	if (length_ == 0)
	{
		return true;
	}
	for (size_t i = 0; i < length_; ++i)
	{
		if (data_[i] != other.data_[i])
		{
			return false;
		}
	}
	return true;
}

bool String::operator!=(const String& other) const
{
	return !(*this == other);
}

bool String::operator<(const String& other) const
{
	size_t minLength = length_ < other.length_ ? length_ : other.length_;
	for (size_t i = 0; i < minLength; ++i)
	{
		if (data_[i] != other.data_[i])
		{
			return data_[i] < other.data_[i];
		}
	}
	return length_ < other.length_;
}

bool String::operator>(const String& other) const
{
	return !(*this < other) && (*this != other);
}

bool String::operator>=(const String& other) const
{
	return (*this == other) || (*this > other);
}

bool String::operator<=(const String& other) const
{
	return (*this == other) || (*this < other);
}

std::ostream& operator <<(std::ostream& on, const String& str)
{
	return on << str.data_;
}
