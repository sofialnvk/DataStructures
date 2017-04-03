#include "set.h"

/*****************************************************
* Implementation of the member functions             *
******************************************************/

//Default constructor
Set::Set ()
	: counter(0)
{
	//Default: value = 0, nex = prev = nullptr
	head = new Node();
	// (value, next, prev)
	tail = new Node(0, nullptr, head);
	head->next = tail;
	//IMPLEMENT before HA session on week 14
}


//Conversion constructor
Set::Set (int n)
	: counter(1) // counter(0) implemented by Aida
{
	// make_empty();
    //Default: value = 0, nex = prev = nullptr
    head = new Node();
    // (value, next, prev)
    tail = new Node(0, nullptr, head);
    head->next = tail;
	
	Node* newNode = new Node(n, tail, tail->prev);
	// tail->prev = newNode
	// tail->prev->next = newNode;
	tail->prev = tail->prev->next = newNode;
	//IMPLEMENT before HA session on week 14
}


//Constructor to create a Set from a sorted array
Set::Set (int a[], int n) // a is sorted
	: counter(n)
{
    //Default: value = 0, nex = prev = nullptr
    head = new Node();
    // (value, next, prev)
    tail = new Node(0, nullptr, head);
    head->next = tail;
	for (int i = 0; i < n; i++)
	{
		Node* newNode = new Node(a[i], tail, tail->prev);
		// tail->prev = newNode
		// tail->prev->next = newNode;
		tail->prev = tail->prev->next = newNode;
	}
	//IMPLEMENT before HA session on week 14
}

Set::~Set()
{
	make_empty();

	delete head;
	delete tail;

	//IMPLEMENT before HA session on week 14

}


//Copy constructor
Set::Set (const Set& source)
	: counter(source.counter)
{
	//Default: value = 0, nex = prev = nullptr
	head = new Node();
	// (value, next, prev)
	tail = new Node(0, nullptr, head);
	head->next = tail;

	for (Node* ptr = source.head->next; ptr->next != nullptr; ptr = ptr->next)
	{
		Node* newNode = new Node(ptr->value, tail, tail->prev);
		// tail->prev = newNode
		// tail->prev->next = newNode;
		tail->prev = tail->prev->next = newNode;
	}
	
	//IMPLEMENT before HA session on week 14
}


//Copy-and-swap assignment operator
Set& Set::operator=(Set source)
{
	
	
	//IMPLEMENT before HA session on week 14

	return *this;
}


//Test whether a set is empty
bool Set::_empty () const
{
	return (!counter);
}


//Test set membership
bool Set::is_member (int val) const
{
	//IMPLEMENT before HA session on week 14

	return false; //remove this line
}



//Return number of elements in the set
unsigned Set::cardinality() const
{
	return counter;
}


//Make the set empty
void Set::make_empty()
{
	//IMPLEMENT before HA session on week 14
}

//Modify *this such that it becomes the union of *this with Set S
//Add to *this all elements in Set S (repeated elements are not allowed)
Set& Set::operator+=(const Set& S)
{
	//IMPLEMENT before HA session on week 14

	return *this;
}

//Return true, if the set is a subset of b, otherwise false
//a <= b iff every member of a is a member of b
bool Set::operator<=(const Set& b) const
{
	//IMPLEMENT

	return false; //remove this line
}


//Return true, if the set is equal to set b
//a == b, iff a <= b and b <= a
bool Set::operator==(const Set& b) const
{
	//IMPLEMENT

	return false; //remove this line
}

//Return true, if the set is different from set b
//a == b, iff a <= b and b <= a
bool Set::operator!=(const Set& b) const
{
	//IMPLEMENT

	return false; //remove this line
}


//Return true, if the set is a strict subset of S, otherwise false
//a == b, iff a <= b but not b <= a
bool Set::operator<(const Set& b) const
{
	//IMPLEMENT

	return false; //remove this line
}


//Modify *this such that it becomes the intersection of *this with Set S
Set& Set::operator*=(const Set& S)
{
	//IMPLEMENT

	return *this;
}


//Modify *this such that it becomes the Set difference between Set *this and Set S
Set& Set::operator-=(const Set& S)
{
	//IMPLEMENT

	return *this;
}


// Overloaded operator<<
ostream& operator<<(ostream& os, const Set& b)
{
	if (b._empty())
		os << "Set is empty!" << endl;
	else
	{
		auto temp = b.head->next;

		os << "{ ";
		while (temp != b.tail)
		{
			os << temp->value << " ";
			temp = temp->next;
		}

		os << "}" << endl;
	}

	return os;
}


