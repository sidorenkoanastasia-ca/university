#ifndef STRING_H
#define STRING_H
#include "StringUtils.h"
#include <iosfwd>

class String
{
public:
	String() : 
		data_(new char[1]{'\0'}),
		length_(0),
		capacity_(1)
	{
	}
	String(const char* str) :
		data_(new char[1] {'\0'}),
		length_(0),
		capacity_(1)
	{
		if (str != nullptr)
		{
			size_t len = strLength(str);
			char* newData = new char[len+1];
			delete[] data_;
			data_ = newData;
			length_ = len;
			capacity_ = len + 1;
			strCopy(data_, str);
		}
	}
	String(const String& other) : 
		length_(other.length_),
		capacity_(other.length_ + 1),
		data_(new char[other.length_ + 1])
	{
		strCopy(data_, other.data_);
	}
		
	String(String&& other) noexcept:
		length_(other.length_),
		capacity_(other.capacity_),
		data_(other.data_)
	{
		other.data_ = nullptr;
		other.length_ = 0;
		other.capacity_ = 0;
	}
	~String()
	{
		delete[] data_;
	}

	void swap(String& other) noexcept;
	size_t length() const;
	bool empty() const; 
	void clear(); 
	bool hasConsecutiveDuplicates() const;

	String& operator=(const String& right); 
	String& operator=(String&& right) noexcept;
	String& operator=(const char* right);
	char& operator[](size_t index);
	const char& operator[](size_t index) const;

	String operator+(const String& other) const;
	String operator+(const char* str) const;
	String& operator+=(const String& other);
	String& operator+=(const char* str);
	
	bool operator==(const String& other) const; 
	bool operator!=(const String& other) const;
	bool operator<(const String& other) const;
	bool operator>(const String& other) const;
	bool operator>=(const String& other) const;
	bool operator<=(const String& other) const;
	friend std::ostream& operator<<(std::ostream& on, const String& str);
	
private:
	char* data_;
	size_t length_; 
	size_t capacity_; 
};


#endif

