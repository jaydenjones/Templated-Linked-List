#pragma once
#include <iostream>
#include <vector>
using namespace std;

template <typename T>
class LinkedList 
{


public:

	struct Node 
	{

		T data;
		Node* next = nullptr;
		Node* prev = nullptr;

	};

	//methods

	void PrintForward() const;
	void PrintReverse() const;  //look at pdf for name
	void PrintForwardRecursive(const Node *node);
	void PrintReverseRecursive(const Node* node);

	//Accessors
	unsigned int NodeCount() const;
	void FindAll(vector<Node *> &outData, const T &value) const;
	Node *Find(const T &data);
	Node *GetNode(unsigned int index);
	Node *Head();
	Node *Tail();

	//Insertion
	void AddHead(const T &data);
	void AddTail(const T &data);
	void AddNodesHead(const T *data, unsigned int count);
	void AddNodesTail(const T *data, unsigned int count);
	void InsertAfter(Node *node, const T &data);
	void InsertBefore(Node *node, const T &data);
	void InsertAt(const T &data, unsigned int index);

	//Removal 
	bool RemoveHead();
	bool RemoveTail();
	unsigned int Remove(const T &data);
	bool RemoveAt(unsigned int index);
	void Clear();

	//Operators
	T &operator[](unsigned int index);
	bool operator==(const LinkedList<T> &rhs) const;
	LinkedList<T> &operator=(const LinkedList<T> &rhs);

	//Construction / Destruction
	LinkedList();
	LinkedList(const LinkedList<T> &list);
	virtual ~LinkedList();


private:

	Node* head;   //has no prev
	Node* tail;	  //has no next
	unsigned int nodeCount;


};

template <typename T>
LinkedList<T>::LinkedList()
{


	head = nullptr;
	tail = nullptr;
	nodeCount = 0;


}




template <typename T>
LinkedList<T>::~LinkedList()
{

	Clear();

}


template <typename T>
void LinkedList<T>::PrintForward() const 
{


	Node* temp = head;



	while (temp != nullptr)
	{


		cout << temp->data << endl;
		temp = temp->next;
	}

	return;
}


template <typename T>
void LinkedList<T>::PrintReverse() const 
{

	Node* temp = tail;


	while (temp != nullptr) 
	{


		cout << temp->data << endl;
		temp = temp->prev;

	}

	return;


}

template <typename T>
void LinkedList<T>::PrintForwardRecursive(const Node* node) 
{

	if (node != nullptr)
	{

		cout << node->data << endl;
		PrintForwardRecursive(node->next);
	}

	return;

}

template <typename T>
void LinkedList<T>::PrintReverseRecursive(const Node* node) 
{

	if (node != nullptr)
	{

		cout << node->data << endl;
		PrintReverseRecursive(node->prev);
	}

	return;


}

template <typename T>
unsigned int LinkedList<T>::NodeCount() const 
{

	return nodeCount;

}

template <typename T>
void LinkedList<T>::FindAll(vector<Node *> &outData, const T &value) const 
{



	Node* temp = head;

	while (temp != nullptr) 
	{


		if (temp->data == value) 
		{

			outData.push_back(temp);
		}

		temp = temp->next;

	}


}

template <typename T>
typename LinkedList<T>::Node *LinkedList<T>::Find(const T &data) 
{

	Node* temp = head;

	while (temp != nullptr) 
	{

		if (temp->data == data)
		{

			return temp;
		}

		temp = temp->next;

	}

	return temp;


}


template <typename T>
typename LinkedList<T>::Node *LinkedList<T>::GetNode(unsigned int index) 
{ 


	Node* temp = head;

	if (index < 0 || index  > nodeCount)
	{

		throw -1;
	}



	for (unsigned int i = 0; i < index; i++)
	{

		temp = temp->next;

	}

	return temp;
}

template <typename T>
typename LinkedList<T>::Node *LinkedList<T>::Head() 
{

	return head;
}

template <typename T>
typename LinkedList<T>::Node *LinkedList<T>::Tail() 
{
	return tail;
}



template <typename T>
void LinkedList<T>::AddHead(const T &data) 
{

	Node* temp = new Node();
	temp->data = data;


	if (head == nullptr) 
	{

		tail = temp;
		head = temp;
		nodeCount++;

		return;

	}

	temp->next = head;

	head->prev = temp;

	head = temp;


	nodeCount++;

}

template <typename T>
void LinkedList<T>::AddTail(const T &data)
{


	Node* temp = new Node();
	temp->data = data;

	if (head == nullptr) 
	{

		tail = temp;
		head = tail;
		nodeCount++;
		return;

	}

	temp->prev = tail;


	tail->next = temp;

	tail = temp;

	nodeCount++;



}

template <typename T>
void LinkedList<T>::AddNodesHead(const T *data, unsigned int count)
{

	for (unsigned int i = count - 1; i < count; i--) 
	{

		AddHead(data[i]);
	}

}

template <typename T>
void LinkedList<T>::AddNodesTail(const T *data, unsigned int count)
{


	for (unsigned int i = 0; i < count; i++)
	{

		AddTail(data[i]);

	}


}

template <typename T>
void LinkedList<T>::InsertAfter(Node *node, const T &data)
{

	Node* nodeToAdd = new Node();
	nodeToAdd->data = data;

	Node* temp = node->next;

	nodeToAdd->next = temp;
	nodeToAdd->prev = temp->prev;

	nodeToAdd->prev->next = nodeToAdd;
	temp->prev = nodeToAdd;

	nodeCount++;


}


template <typename T>
void LinkedList<T>::InsertBefore(Node *node, const T &data) 
{

	Node* nodeToAdd = new Node();
	nodeToAdd->data = data;

	Node* temp = node; //node->prev?

	nodeToAdd->next = temp;
	nodeToAdd->prev = temp->prev;

	nodeToAdd->prev->next = nodeToAdd;
	temp->prev = nodeToAdd;

	nodeCount++;

}


template <typename T>
void LinkedList<T>::InsertAt(const T &data, unsigned int index) 
{


	Node* temp = GetNode(index);

	if (temp == nullptr)
	{

		AddTail(data);
		return;

	}


	if (index == 0) 
	{

		AddHead(data);
		return;
	}

	Node* nodeToAdd = new Node();
	nodeToAdd->data = data;

	

	nodeToAdd->next = temp;
	nodeToAdd->prev = temp->prev;

	nodeToAdd->prev->next = nodeToAdd;
	temp->prev = nodeToAdd;

	nodeCount++;

	//if index = 0 or equal to head, setting this would throw NullPointerException

	//throw exception if go too far in index




}

template <typename T>
bool LinkedList<T>::RemoveHead() 
{

	Node* temp = head;

	if (temp == nullptr) 
	{

		return false;
	}



	head = temp->next;

	if (this->head == nullptr) 
	{

		delete temp;
		nodeCount--;
		return true;

	}

	head->prev = nullptr;

	delete temp;

	nodeCount--;

	return true;


}

template <typename T>
bool LinkedList<T>::RemoveTail() 
{

	Node* temp = tail;

	if (temp == nullptr)
	{

		return false;
	}

	if (tail == nullptr) 
	{

		return false;
	}


	tail = temp->prev;

	if (this->tail == nullptr)
	{

		delete temp;
		nodeCount--;
		return true;
	}

	tail->next = nullptr;

	delete temp;

	nodeCount--;

	return true;

}


template <typename T>
unsigned int LinkedList<T>::Remove(const T &data)
{

	Node* temp = head;


	int nodesRemoved = 0;

	for (unsigned int i = 0; i < nodeCount; i++)
	{

		temp = head;

		while (temp->data != data) 
		{

			temp = temp->next;

			if (temp == nullptr) 
			{

				return nodesRemoved;
			}

		}


		while (temp->data == data) 
		{


			if (temp == nullptr) 
			{

				return nodesRemoved;
			}

			if (temp->data != data) 
			{

				temp = temp->next;
			}

			if (temp->data == data) 
			{

				if (temp == nullptr)
				{

					return nodesRemoved;
				}


				temp->prev->next = temp->next;

				temp->next->prev = temp->prev;

				nodesRemoved++;

				delete temp;


			}


		}
	}
	return nodesRemoved;

}



template <typename T>
bool LinkedList<T>::RemoveAt(unsigned int index)
{

	//if index is valid, return false (

	//if index is 0, or is count, removeHead or tail and return 


	//GetNode(index)

//	Node* temp = GetNode(index);

	//set node before to node after node(index) and node after to node before node(index)

	//node->p->n = node->n
	//3->n

	if (index < 0 || index > nodeCount) 
	{ 

		return false;

	}

	Node* temp = GetNode(index);

	temp->prev->next = temp->next;

	temp->next->prev = temp->prev;

	nodeCount--;

	delete temp;

	return true;

}


template <typename T>
void LinkedList<T>::Clear() 
{


	//can be done with removeTail
	//use a for loop	

	unsigned int temp = nodeCount;

	for (unsigned int i = 0; i < temp; i++) 
	{

		RemoveTail();
	}

	head = 0;
	tail = 0;
	nodeCount = 0;

	//set head, tail, count all to 0

}

template <typename T>
T &LinkedList<T>::operator[](unsigned int index) 
{

	Node* temp = GetNode(index);

	return temp->data;
}


//in destructor, call Clear() function (i think in destructor)

//equiv.op

template <typename T>
bool LinkedList<T>::operator==(const LinkedList<T> &rhs) const //should work
{ 


	//	Check size (if size is diff, return false)

	if (nodeCount != rhs.nodeCount)
	{

		return false;

	}

	Node* List1Iterator = head;

	Node* List2Iterator = rhs.head;

	while (List1Iterator != nullptr)
	{	

		if (List2Iterator == nullptr)
		{

			return false;

		}




		if (List1Iterator->data != List2Iterator->data)
		{

			return false;
		}

		List1Iterator = List1Iterator->next;
		List2Iterator = List2Iterator->next;
		//move second also




	}

	//this point

	if (List1Iterator == nullptr && List2Iterator != nullptr)
	{

		return false;

	}


	return true;



}



template <typename T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &rhs) //should be last thing you write
{ 

	Clear();

	Node* temp = rhs.head;


	for (unsigned int i = 0; i < rhs.nodeCount; i++)
	{

		AddTail(temp->data);
		temp = temp->next;

	}

	return *this;

}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T> &list) 
{

	Clear();

	Node* temp = list.head;


	for (unsigned int i = 0; i < list.nodeCount; i++)
	{

		AddTail(temp->data);
		temp = temp->next;

	}

}