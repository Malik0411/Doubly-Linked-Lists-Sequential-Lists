#include "DoublyLinkedList.hpp"
#include <iostream>
#include <cstdlib>

using namespace std;

DoublyLinkedList::Node::Node(DataType data)
{
	value = data;
	next = NULL;
	prev = NULL;
}

DoublyLinkedList::DoublyLinkedList()
{
	head_ = NULL;
	tail_ = NULL;
	size_ = 0;
}

DoublyLinkedList::~DoublyLinkedList()
{
	if (head_ == NULL)
		return;

	while (head_ != NULL)
	{
		Node* temp = head_;
		head_ = temp->next;
		delete temp;
	}
}

bool DoublyLinkedList::empty() const
{
	return (size_ == 0);
}

unsigned int DoublyLinkedList::size() const
{
	return size_;
}

void DoublyLinkedList::print() const
{
	Node* last = head_;

	cout << "(";
	while (last != NULL)
	{
		cout << "[" << last->value << "]";
		last = last->next;

		if (last != NULL)
			cout << "->";
	}

	cout << ")\n";
}

bool DoublyLinkedList::insert_front(DataType value)
{
	if (size_ == 0)
	{
		Node* newNode = new Node(value);
		head_ = newNode;
		tail_ = newNode;

		size_++;

		return true;
	}
	
	else if (size_ == 1)
	{
		Node* temp = head_;
		Node* newNode = new Node(value);
		head_ = newNode;
		newNode->next = temp;
		temp->prev = newNode;
		tail_ = temp;

		size_++;

		return true;
	}
	
	else if (size_ > 0 && size_ < CAPACITY)
	{
		Node* temp = head_;
		Node* newNode = new Node(value);
		head_ = newNode;
		newNode->next = temp;
		temp->prev = newNode;

		size_++;

		return true;
	}

	return false;
}

bool DoublyLinkedList::remove_front()
{
	if (size_ == 0)
		return false;

	else if (size_ == 1)
	{
		head_ = NULL;
		tail_ = NULL;
		delete head_;
		delete tail_;

		size_--;

		return true;
	}
	else
	{
		Node* temp = head_->next;
		head_ = NULL;
		delete head_;
		head_ = temp;
		temp->prev = NULL;
		delete temp->prev;

		size_--;

		return true;
	}

	return false;
}

bool DoublyLinkedList::insert_back(DataType value)
{
	if (size_ == 0)
	{
		Node* newNode = new Node(value);
		head_ = newNode;
		tail_ = newNode;

		size_++;

		return true;
	}
	else if (size_ > 0 && size_ < CAPACITY)
	{
		Node* temp = tail_;
		Node* newNode = new Node(value);
		tail_ = newNode;
		newNode->prev = temp;
		temp->next = newNode;

		size_++;

		return true;
	}

	return false;
}

bool DoublyLinkedList::remove_back()
{
	if (size_ == 0)
		return false;

	else if (size_ == 1)
	{
		head_ = NULL;
		tail_ = NULL;
		delete head_;
		delete tail_;

		size_--;

		return true;
	}

	else
	{
		Node* temp = tail_->prev;
		tail_ = NULL;
		delete tail_;
		tail_ = temp;
		temp->next = NULL;
		delete temp->next;

		size_--;

		return true;
	}

	return false;
}

bool DoublyLinkedList::insert(DataType value, unsigned int index)
{
	if (index < 0 || index > CAPACITY || index > size_ || size_ == CAPACITY)
		return false;

	else if (size_ == 0)
	{
		Node* newNode = new Node(value);
		head_ = newNode;
		tail_ = newNode;

		size_++;

		return true;
	}
		
	else if (index == 0)
	{
		Node* temp = head_;
		Node* newNode = new Node(value);
		head_ = newNode;
		newNode->next = temp;
		temp->prev = newNode;

		size_++;

		return true;
	}

	else if (index == size_)
	{
		Node* temp = tail_;
		Node* newNode = new Node(value);
		tail_ = newNode;
		newNode->prev = temp;
		temp->next = newNode;

		size_++;

		return true;
	}

	else
	{
		Node* temp = getNode(index);
		Node* newNode = new Node(value);
		
		newNode->next = temp;
		newNode->prev = temp->prev;
		
		temp->prev->next = newNode;
		temp->prev = newNode;

		size_++;

		return true;
	}

	return false;
}

bool DoublyLinkedList::remove(unsigned int index)
{
	if (size_ == 0 || index < 0 || index > CAPACITY || (index+1) > size_)
		return false;

	else if (size_ == 1)
	{
		head_ = NULL;
		tail_ = NULL;
		delete head_;
		delete tail_;

		size_--;

		return true;
	}
	
	else if (index == 0)
	{
		Node* temp = head_->next;	
		
		head_ = NULL;
		delete head_;
		
		head_ = temp;
		
		temp->prev = NULL;
		delete temp->prev;

		size_--;

		return true;
	}
	
	else if ((index+1) == size_)
	{
		Node* temp = tail_->prev;
		
		tail_ = NULL;
		delete tail_;
		
		tail_ = temp;
		
		temp->next = NULL;
		delete temp->next;

		size_--;

		return true;
	}

	else
	{
		Node* temp = getNode(index);

		temp->prev->next = temp->next;
		temp->next->prev = temp->prev;

		temp = NULL;
		delete temp;

		size_--;

		return true;
	}

	return false;
}

unsigned int DoublyLinkedList::search(DataType value) const
{
	if (size_ == 0)
		return size_;

	else
	{
		Node* temp = head_;

		for (int i = 0; i < size_; i++)
		{
			if (temp->value == value)
				return i;

			temp = temp->next;
		}

		return size_;
	}
}

DoublyLinkedList::DataType DoublyLinkedList::select(unsigned int index) const
{
	if (size_ == 0 || index < 0 || index > CAPACITY || (index+1) > size_)
		return tail_->value;

	else
	{
		Node* temp = head_;

		for (int i = 0; i < index; i++)
			temp = temp->next;

		return temp->value;
	}
}

bool DoublyLinkedList::replace(unsigned int index, DataType value)
{
	if ((index+1) > size_ || index < 0 || (index+1) > CAPACITY)
		return false;

	else
	{
		Node* temp = head_;

		for (int i = 0; i < index; i++)
			temp = temp->next;

		temp->value = value;

		return true;
	}

	return false;
}

DoublyLinkedList::Node* DoublyLinkedList::getNode(unsigned int index) const
{
	int count = 0;
	Node* temp = head_;
	
	while(count < index)
	{
		temp = temp->next;
		count++;
	}
	
	return temp;
}

bool DoublyLinkedList::full() const
{
	return (size_ == CAPACITY);
}
