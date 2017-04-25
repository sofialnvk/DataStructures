#include "set.h"

/*****************************************************
* Implementation of the member functions             *
******************************************************/

//Default constructor
Set::Set()
	: counter(0)
{
	//Create head and tail and link them to eachother
	//Default: value = 0, nex = prev = nullptr
	head = new Node();
	// (value, next, prev)
	tail = new Node(0, nullptr, head);
	head->next = tail;
	//IMPLEMENT before HA session on week 14
}


//Conversion constructor
Set::Set(int n)
	: Set() //Call constructor instead of rewriting the code from the constructor
{
	//Insert given value to set
	insert(tail, n);
}


//Constructor to create a Set from a sorted array
Set::Set(int a[], int n) // a is sorted
	: Set() //Call constructor instead of rewriting the code from the constructor
{
	//Loop through the array and insert the values to the Set
	for (int i = 0; i < n; i++)
	{
		insert(tail, a[i]);
	}
}

Set::~Set()
{
	//Empty the set
	make_empty();
	
	delete head;
	delete tail;
	//Point to nullptr to avoid memory leaks
	head = tail = nullptr;
}


//Copy constructor
Set::Set(const Set& source)
	: Set() //Call constructor instead of rewriting the code from the constructor
{
	//Loop through given set and insert values into this
	for (Node* ptr = source.head->next; ptr->next != nullptr; ptr = ptr->next)
	{
		insert(tail, ptr->value);
	}
}

//Move copy constructor
Set::Set(Set&& rhs)
    : head(nullptr), tail(nullptr), counter(0)
{
	//Copy values from rhs to this
	head = rhs.head;
	tail = rhs.tail;
	counter = rhs.counter;

	//Reset rhs
	//Link head and tail of rhs to eachother
	rhs.head = new Node();
	rhs.tail = new Node(0, nullptr, rhs.head);
    rhs.head->next = rhs.tail;
	rhs.counter = 0;
}



//Copy-and-swap assignment operator
// Assigns new contents to the Set, replacing its current content
// \param source Set to be copied into Set *this
Set& Set::operator=(const Set& source)
{
    if(this != &source)
    {
		//Make a copy of source
		//Swap the content of this and the copy
        Set copy(source);
        swap(head, copy.head); //swap the pointers
        swap(head->value, copy.head->value);
        swap(tail, copy.tail); //swap the pointers
        swap(tail->value, copy.tail->value);
        swap(counter, copy.counter);
    }
	return *this;
}

//Move assignment operator
Set& Set::operator=(Set&& source)
{

	if(this != &source)
    {
        //release the current object’s resources
        make_empty();
        delete head;
        delete tail;
        counter = 0;
        
		//steal the contents from source into *this
        head = source.head;
        tail = source.tail;
        counter = source.counter;
        
        //reset source
		//Make head and tail of source point to eachother
		//make sure source is an empty list
        source.head = new Node();
        source.tail = new Node(0, nullptr, source.head);
        source.head->next = source.tail;
        source.counter = 0;
    }
    return *this;
}

//Test whether a set is empty
bool Set::_empty() const
{
	if ((head->next == tail) && (tail->prev == head))
	{
		return true;
	}

	else return false;
}


//Test set membership
// This function does not modify the Set in any way
// Return true if val belongs to the set, otherwise false
bool Set::is_member(int val) const
{
	for (Node* ptr = head->next; ptr->next != nullptr; ptr = ptr->next)
	{
		if (ptr->value == val)
			return true;
	}
	return false; 
}



//Return number of elements in the set
unsigned Set::cardinality() const
{
	return counter;
}


//Make the set empty
void Set::make_empty()
{
	Node *ptr = head;
	//Loop through the set and delete each value
	while (ptr->next != tail)
	{
		Node *node = ptr->next;
		ptr->next = node->next;
		node->next->prev = head;

        delete node;
	}
	counter = 0;
}

//Modify *this such that it becomes the union of *this with Set S
//Add to *this all elements in Set S (repeated elements are not allowed)
// Set *this is modified and then returned
Set& Set::operator+=(const Set& S)
{
	Node* left = head->next;
	Node* right = S.head->next;

	while (left->next != nullptr && right->next != nullptr)
	{
		//If left value < right --> insert and point to the next value
		//Value already in this --> no insertion
		if (left->value  < right->value )
		{
			left = left->next;
		}

		//If left value > right  --> insert and point to the next value
		else if (left->value > right->value)
		{
			insert(left, right->value);
			right = right->next;
		}

		//If values are the same the value already exists in this --> no insertion
		else
		{
			right = right->next;
		}
	}

	//If right set is longer than left set --> insert the rest of the values
	while (right->next != nullptr)
	{
		insert(tail, right->value);
		right = right->next;
	}
	return *this;
}

//Return true, if the set is a subset of b, otherwise false
//a <= b iff every member of a is a member of b
bool Set::operator<=(const Set& b) const
{
	Node* left = head->next;
	Node* right = b.head->next;

	if (cardinality() < b.cardinality())
	{
		while (left->next != nullptr && right->next != nullptr)
		{
			//If left value < right --> not a subset, return false
			if (left->value < right->value)
				return false;

			//If left value > right  --> might be a subset, point to the next value in right
			else if (left->value > right->value)
			{
				right = right->next;
			}

			//If values are the same, could be subset
			else
			{
				left = left->next;
				right = right->next;
			}
		}
		//It is a subset
		return true;
	}
	return false;
}


//Return true, if the set is equal to set b
//a == b, iff a <= b and b <= a
bool Set::operator==(const Set& b) const
{
	Node* left = head->next;
	Node* right = b.head->next;

	//If the lengths of the sets are the same the could be equal
	if (cardinality() == b.cardinality())
	{
		while (left->next != nullptr && right->next != nullptr)
		{
			//If the they have the same value, point to the next value
			if (left->value == right->value)
			{
				left = left->next;
				right = right->next;
			}
			//If one of the values do not match, they are not equal
			else
			{
				return false;
			}
		}
		//If the sets are equal
		return true;
	}
	//They do not have the same length
	return false; //remove this line
}

//Return true, if the set is different from set b
//a == b, iff a <= b and b <= a
bool Set::operator!=(const Set& b) const
{
	//If the sets are equal
	if (*this == b)
	{
		return false;
	}

	//If the sets are different
	else return true;
}


//Return true, if the set is a strict subset of S, otherwise false
//a == b, iff a <= b but not b <= a
bool Set::operator<(const Set& b) const
{
	if (*this <= b)
	{
		//It is a proper subset
		if (*this != b)
			return true;
	}

	return false; 
}


//Modify *this such that it becomes the intersection of *this with Set S
Set& Set::operator*=(const Set& S)
{
	Node* left = head->next;
	Node* right = S.head->next;

	while (left != tail && right != S.tail)
	{
		//Value does not exist in both sets, remove from this
		if (left->value < right->value)
		{
			//delete
            left = left->next;
            del(left->prev);
		}

		//Value only exists in right, do nothing to this and point to the
		//next value in right
		else if (left->value > right->value)
		{
			if (right->next == S.tail)
            {
                left = left->next;
                del(left->prev);
            }
            right=right->next;
		}

		//If values are the same, keep value in this, point to the next value
		//in left and right
		else
		{
			left = left->next;
			right = right->next;
		}
	}

    //If left set is longer than right set --> delete the rest of the values
    while (left->next != nullptr)
    {
        left = left->next;
        del(left->prev);

    }

	return *this;
}


//Modify *this such that it becomes the Set difference between Set *this and Set S
Set& Set::operator-=(const Set& S)
{
	Node* left = head->next;
	Node* right = S.head->next;

	while (left != tail && right != S.tail)
	{
		//Value does not exist in both sets, keep value in this
		//point to the next value in left
		if (left->value  < right->value)
		{
			left = left->next;
		}

		//Value only exists in right, insert to this and point to the
		//next value in right
		else if (left->value > right->value)
		{
			right = right->next;
		}

		//If values are the same, delete value from this
		else
		{
            left = left->next;
            del(left->prev);
		}
	}

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

void Set::insert(Node *p, int val)
{
	//Insert a value to the set and increment the counter
	Node* newNode = new Node(val, p, p->prev); //steps 1 and 2
	p->prev = p->prev->next = newNode; //steps 3 and 4
	counter++;
}

//Send in node you want to delete
Set& Set::del(Node *p)
{
	//Delete a value from the set and decrement the counter
	p->prev->next = p->next;
	p->next->prev = p->prev;
	counter--;

	delete p; //deallocate
	return *this;
}
