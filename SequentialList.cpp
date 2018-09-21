// .cpp files contain code definitions for methods that have been declared
// in the according .hpp file. The skeleton has been set up here for you.
// That is, the methods have been initiated, and your mission, should you 
// choose to accept it (which you should for marks), is to fill in each method
// with the appropriate code.
//
// A note about the "::" syntax: generally, this means "the thing on the right
// belongs to the thing on the left." So, SequentialList::empty() means the method
// empty() belongs to the class SequentialList. This allows empty() to access (and
// potentially change) the member variables in class SequentialList.

#include "SequentialList.hpp"
#include <iostream>
#include <cstdlib>

using namespace std;

// This is the constructor.
SequentialList::SequentialList(unsigned int cap)
{
	data_ = new DataType[cap];
	capacity_ = cap;
	size_ = 0;
}

SequentialList::~SequentialList()
{
	data_ = NULL;
	delete data_;
}

bool SequentialList::empty() const
{
	return (size_ == 0);
}

unsigned int SequentialList::size() const
{
	return size_;
}

unsigned int SequentialList::capacity() const
{
	return capacity_;
}

bool SequentialList::full() const
{
	return (size_ == capacity_);
}

void SequentialList::print() const
{
	for (int counter = 0; counter < capacity_; counter++)
		cout << data_[counter];
	if (empty())
		cout << "List is empty" << endl;
}

// NOTE on inserts: do NOT grow the array if we reach capacity. Simply return false.
bool SequentialList::insert_front(DataType val)
{
	if (capacity_ > 0 && size_ < capacity_)
	{
		if (empty())
		{
			data_[0] = val;
			size_++;
			return true;
		}
		else if (size_ > 0)
		{
			for (int i = size_-1; i >= 0; i--)
			{
				data_[i+1] = data_[i];
			}

			data_[0] = val;
			size_++;

			return true;
		}

		return true;
	}
	return false;
}

bool SequentialList::remove_front()
{
	if (size_ > 0)
	{
		for (int i = 1; i < size_; i++)
			data_[i-1] = data_[i];

		data_[size_-1] = NULL;
		size_--;
		return true;
	}
	return false;
}

bool SequentialList::insert_back(DataType val)
{
	if (capacity_ > 0 && size_ < capacity_)
	{
		data_[size_] = val;
		size_++;

		return true;
	}
	return false;
}

bool SequentialList::remove_back()
{
	if (size_ > 0)
	{
		data_[size_-1] = NULL;
		size_--;
		return true;
	}

	return false;
}

bool SequentialList::insert(DataType val, unsigned int index)
{
	if (capacity_ > 0 && size_ < capacity_)
	{
		if (index == size_)
			return (insert_back(val));
			
		else if (size_ > 0 && index < size_)
		{
			for (int i = size_; i > index; i--)
				data_[i] = data_[i-1];

			data_[index] = val;
			size_++;

			return true;
		}
		
		else if (empty())
		{
			data_[index] = val;
			size_++;
			return true;
		}
	}
	
	return false;
}

bool SequentialList::remove(unsigned int index)
{
	if (size_ > 0 && index < size_)
	{
		for (int i = index; i < size_; i++)
			data_[i] = data_[i+1];

		data_[size_-1] = NULL;
		size_--;
		return true;
	}
	return false;
}

unsigned int SequentialList::search(DataType val) const
{
	if(size_ > 0)
	{
		for (int i = 0; i < size_; i++)
		{
				if(data_[i] == val)
					return i;
		}
	}
	return size_;
}

SequentialList::DataType SequentialList::select(unsigned int index) const
{
	if (index >= size_)
		return data_[size_-1];

	return (data_[index]);
}

bool SequentialList::replace(unsigned int index, DataType val)
{
	if (index < capacity_)
	{
		if(size_ > index)
		{
			data_[index] = val;
			return true;
		}

		return false;
	}
	return false;
}
