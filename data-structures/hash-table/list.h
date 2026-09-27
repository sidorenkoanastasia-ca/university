#ifndef LIST_H
#define LIST_H
#include <iostream>

template <class T>
class DoubleOrderedDuplicateList
{
public:
	//O(1)
	DoubleOrderedDuplicateList() : head_(nullptr),
		tail_(nullptr),
		size_(0)
	{
	}
	//O(1)
	DoubleOrderedDuplicateList(const T& value) : head_(new Node(value)), size_(1)
	{
		tail_ = head_;
	}
	//O(1)
	DoubleOrderedDuplicateList(T&& value) : head_(new Node(std::move(value))),
		size_(1)
	{
		tail_ = head_;
	}
	//O(n), n - other.size_
	DoubleOrderedDuplicateList(const DoubleOrderedDuplicateList& other) : head_(nullptr),
		tail_(nullptr),
		size_(0)
	{
		if (other.head_ == nullptr)
		{
			return;
		}
		Node* currentOther = other.head_;
		Node* prev = nullptr;
		try
		{
			while (currentOther != nullptr)
			{
				Node* newNode = new Node(currentOther->data_);
				newNode->prev_ = prev;
				if (prev == nullptr)
				{
					head_ = newNode;
				}
				else
				{
					prev->next_ = newNode;
				}
				prev = newNode;
				size_++;
				currentOther = currentOther->next_;
			}
		}
		catch (...)
		{
			clear();
			throw;
		}
		tail_ = prev;
	}
	//O(1)
	DoubleOrderedDuplicateList(DoubleOrderedDuplicateList&& other) : head_(other.head_),
		tail_(other.tail_),
		size_(other.size_)
	{
		other.head_ = nullptr;
		other.tail_ = nullptr;
		other.size_ = 0;
	}
	~DoubleOrderedDuplicateList()
	{
		while (head_ != nullptr)
		{
			Node* next = head_->next_;
			delete head_;
			head_ = next;
		}
	}
	//O(n), n - other.size_
	DoubleOrderedDuplicateList& operator=(const DoubleOrderedDuplicateList& other)
	{
		if (this != &other)
		{
			DoubleOrderedDuplicateList temp(other);
			swap(temp);
		}
		return *this;
	}
	//O(1)
	DoubleOrderedDuplicateList& operator=(DoubleOrderedDuplicateList&& other)
	{
		if (this != &other)
		{
			DoubleOrderedDuplicateList temp(std::move(other));
			swap(temp);
		}
		return *this;

	}
	//O(1)
	T head() const
	{
		if (!head_)
		{
			throw std::runtime_error("ERROR: List is empty\n");
		}
		return head_->data_;
	}
	//O(1)
	T tail() const
	{
		if (!tail_)
		{
			throw std::runtime_error("ERROR: List is empty\n");
		}
		return tail_->data_;
	}
	//O(n)
	bool search(const T& key) const
	{
		Node* val = head_;
		while (val != nullptr)
		{
			if (val->data_ == key)
			{
				return true;
			}
			if (val->data_ > key)
			{
				return false;
			}
			val = val->next_;
		}
		return false;
	}
	bool find(const T& key, T& outValue) const
	{
		Node* current = head_;
		while (current != nullptr)
		{
			if (current->data_ == key)
			{
				outValue = current->data_;
				return true;
			}
			if (current->data_ > key)
			{
				return false;
			}
			current = current->next_;
		}
		return false;
	}
	//O(1)
	size_t size() const noexcept
	{
		return size_;
	}
	//O(1)
	bool isEmpty() const noexcept
	{
		return size_ == 0;
	}
	//O(n)
	void printForward(std::ostream& out) const
	{
		Node* start = head_;
		while (start != nullptr)
		{
			out << start->data_ << ' ';
			start = start->next_;
		}
	}
	//O(n)
	void printBackward(std::ostream& out) const
	{
		Node* start = tail_;
		while (start != nullptr)
		{
			out << start->data_ << ' ';
			start = start->prev_;
		}
	}
	//O(n)
	bool insert(const T& value)
	{
		Node* newNode = new Node(value);
		if (head_ == nullptr)
		{
			head_ = newNode;
			tail_ = newNode;
			size_++;
			return true;
		}
		Node* current = head_;
		while (current != nullptr)
		{
			if (current->data_ == value)
			{
				delete newNode;
				return false;
			}
			if (current->data_ > value)
			{
				break;
			}
			current = current->next_;
		}
		if (current == head_)
		{
			Node* oldHead = head_;
			head_ = newNode;
			head_->next_ = oldHead;
			oldHead->prev_ = head_;
		}
		else if (current == nullptr)
		{
			Node* oldTail = tail_;
			tail_ = newNode;
			tail_->prev_ = oldTail;
			oldTail->next_ = tail_;
		}
		else
		{
			Node* oldPrev = current->prev_;
			oldPrev->next_ = newNode;
			newNode->prev_ = oldPrev;
			newNode->next_ = current;
			current->prev_ = newNode;
		}
		size_++;
		return true;
	}
	//O(n)
	bool insert(T&& value)
	{
		Node* newNode = new Node(std::move(value));
		if (head_ == nullptr)
		{
			head_ = newNode;
			tail_ = newNode;
			size_++;
			return true;
		}
		Node* current = head_;
		while (current != nullptr)
		{
			if (current->data_ == newNode->data_)
			{
				delete newNode;
				return false;
			}
			if (current->data_ > newNode->data_)
			{
				break;
			}
			current = current->next_;
		}
		if (current == head_)
		{
			Node* oldHead = head_;
			head_ = newNode;
			head_->next_ = oldHead;
			oldHead->prev_ = head_;
		}
		else if (current == nullptr)
		{
			Node* oldTail = tail_;
			tail_ = newNode;
			tail_->prev_ = oldTail;
			oldTail->next_ = tail_;
		}
		else
		{
			Node* oldPrev = current->prev_;
			oldPrev->next_ = newNode;
			newNode->prev_ = oldPrev;
			newNode->next_ = current;
			current->prev_ = newNode;
		}
		size_++;
		return true;
	}
	//O(1)
	void removeHead()
	{
		if (head_ == nullptr)
		{
			throw std::out_of_range("ERROR: List is empty\n");
		}
		Node* oldHead = head_;
		if (size_ == 1)
		{
			head_ = nullptr;
			tail_ = nullptr;
		}
		else
		{
			head_ = head_->next_;
			head_->prev_ = nullptr;
		}
		delete oldHead;
		size_--;
	}
	//O(1)
	void clear() noexcept
	{
		DoubleOrderedDuplicateList empty;
		swap(empty);
	}
	//O(n)
	bool removeKey(const T& keyBegin, const T& keyEnd)
	{
		if (head_ == nullptr)
		{
			return false;
		}
		bool removed = false;
		Node* current = head_;
		while (current != nullptr)
		{
			Node* next = current->next_;
			if (current->data_ > keyEnd)
			{
				break;
			}
			if (current->data_ >= keyBegin && current->data_ <= keyEnd)
			{
				if (current == head_)
				{
					head_ = current->next_;
					if (head_ != nullptr)
					{
						head_->prev_ = nullptr;
					}
					else
					{
						tail_ = nullptr;
					}
				}
				else if (next == nullptr)
				{
					tail_ = current->prev_;
					if (tail_ != nullptr)
					{
						tail_->next_ = nullptr;
					}
				}
				else
				{
					Node* prev = current->prev_;
					prev->next_ = next;
					next->prev_ = prev;
				}
				delete current;
				size_--;
				removed = true;
			}
			current = next;
		}
		return removed;
	}
	//O(n)
	bool operator==(const DoubleOrderedDuplicateList& other) const
	{
		if (size_ != other.size_)
		{
			return false;
		}
		Node* current = head_;
		Node* currentOther = other.head_;
		while (current != nullptr && currentOther != nullptr)
		{
			if (current->data_ != currentOther->data_)
			{
				return false;
			}
			current = current->next_;
			currentOther = currentOther->next_;
		}
		return true;
	}
	friend DoubleOrderedDuplicateList getIntersection(const DoubleOrderedDuplicateList& first, const DoubleOrderedDuplicateList& second)
	{
		if (first.head_ == nullptr || second.head_ == nullptr)
		{
			return DoubleOrderedDuplicateList();
		}
		DoubleOrderedDuplicateList result;
		Node* currentFirst = first.head_;
		Node* currentSecond = second.head_;
		while (currentFirst != nullptr && currentSecond != nullptr)
		{
			if (currentFirst->data_ < currentSecond->data_)
			{
				currentFirst = currentFirst->next_;
			}
			else if (currentFirst->data_ > currentSecond->data_)
			{
				currentSecond = currentSecond->next_;
			}
			else
			{
				result.insertInTheEnd(currentFirst->data_);
				currentFirst = currentFirst->next_;
				currentSecond = currentSecond->next_;
			}
		}
		return result;
	}
	//O(n+m), m - other.size_
	void remove(const DoubleOrderedDuplicateList& other)
	{
		if (head_ == nullptr || other.head_ == nullptr)
		{
			return;
		}
		Node* currentThis = head_;
		Node* currentOther = other.head_;
		while (currentThis != nullptr && currentOther != nullptr)
		{
			if (currentThis->data_ < currentOther->data_)
			{
				currentThis = currentThis->next_;
			}
			else if (currentThis->data_ > currentOther->data_)
			{
				currentOther = currentOther->next_;
			}
			else
			{
				Node* next = currentThis->next_;
				Node* del = currentThis;
				if (currentThis->prev_)
				{
					currentThis->prev_->next_ = next;
				}
				else
				{
					head_ = next;
				}
				if (currentThis->next_)
				{
					next->prev_ = currentThis->prev_;
				}
				else
				{
					tail_ = currentThis->prev_;
				}
				delete del;
				size_--;
				currentThis = next;
				currentOther = currentOther->next_;
			}
		}
	}
	//O(1)
	void swap(DoubleOrderedDuplicateList& other) noexcept
	{
		std::swap(size_, other.size_);
		std::swap(head_, other.head_);
		std::swap(tail_, other.tail_);
	}
private:
	struct Node
	{
		T data_;
		Node* next_;
		Node* prev_;
		Node(const T& value) : data_(value), next_(nullptr),
			prev_(nullptr)
		{
		}
		Node(T&& value) : data_(std::move(value)), next_(nullptr),
			prev_(nullptr)
		{
		}
		Node(const T& value, Node* prev, Node* next) : data_(value), next_(next),
			prev_(prev)

		{
		}
		Node(const Node&) = delete;
		Node& operator=(const Node&) = delete;
	};
	Node* head_;
	Node* tail_;
	size_t size_;
	void insertInTheEnd(const T& value)
	{
		Node* newNode = new Node(value);
		if (head_ == nullptr)
		{
			head_ = newNode;
			tail_ = newNode;
			size_++;
			return;
		}
		Node* temp = tail_;
		tail_ = newNode;
		tail_->prev_ = temp;
		temp->next_ = tail_;
		size_++;
	}
};

#endif