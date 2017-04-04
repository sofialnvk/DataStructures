#include "set.h"

/*****************************************************
* Implementation of the member functions             *
******************************************************/

//Default constructor
Set::Set()
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
Set::Set(int n)
	: counter(0) 
{
	//Default: value = 0, nex = prev = nullptr
	head = new Node();
	// (value, next, prev)
	tail = new Node(0, nullptr, head);
	head->next = tail;

	insert(n);
	//IMPLEMENT before HA session on week 14
}


//Constructor to create a Set from a sorted array
Set::Set(int a[], int n) // a is sorted
	: counter(0)
{
	//Default: value = 0, nex = prev = nullptr
	head = new Node();
	// (value, next, prev)
	tail = new Node(0, nullptr, head);
	head->next = tail;
	for (int i = 0; i < n; i++)
	{
		insert(a[i]);
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
Set::Set(const Set& source)
	: counter(0)
{
	//Default: value = 0, nex = prev = nullptr
	head = new Node();
	// (value, next, prev)
	tail = new Node(0, nullptr, head);
	head->next = tail;

	for (Node* ptr = source.head->next; ptr->next != nullptr; ptr = ptr->next)
	{
		insert(ptr->value);
	}

	//IMPLEMENT before HA session on week 14
}


//Copy-and-swap assignment operator
// Assigns new contents to the Set, replacing its current content
// \param source Set to be copied into Set *this
Set& Set::operator=(Set source)
{
	//Dont forget to check self assignment

	Set copy(source);
	swap(head, copy.head); //swap the pointers
	swap(head->value, copy.head->value);
	swap(tail, copy.tail); //swap the pointers
	swap(tail->value, copy.tail->value);
	swap(counter, copy.counter);

	//IMPLEMENT before HA session on week 14

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
	Node *ptr = head;  //DONT skip the dummy node ??

	while (ptr->next != tail)  //do not swap the tests
	{
		Node *node = ptr->next;
		ptr->next = node->next;
		node->next->prev = head;

		delete node; //deallocate
	}
	counter = 0;
	//IMPLEMENT before HA session on week 14
}

//Modify *this such that it becomes the union of *this with Set S
//Add to *this all elements in Set S (repeated elements are not allowed)
// Set *this is modified and then returned
Set& Set::operator+=(const Set& S)
{
	//IMPLEMENT before HA session on week 14
	/*Node* left = head->next;
	Node* right = S.head->next;
	Set newSet;

	while (left->next)
	{
		newSet.insert(left->value);
		left = left->next;
	}
	while (right->next)
	{
		newSet.insert(right->value);
		right = right->next;
	}

	swap(head, newSet.head); //swap the pointers
	swap(head->value, newSet.head->value);
	swap(tail, newSet.tail); //swap the pointers
	swap(tail->value, newSet.tail->value);*/
	Node* right = S.head->next;
	while (right->next)
	{
		this->insert(right->value);
		right = right->next;
	}
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

void Set::insert(int value)
{
	Node* newNode = new Node(value, tail, tail->prev);
	
	if (_empty())
	{
		tail->prev = tail->prev->next = newNode;
		counter++;
		//std::cout << "första värdet i newNode" << std::endl;
	}

	else 
	{
		Node* temp = head;
		while (temp->next != tail) 
		{ // tittar en framåt
			if (value > temp->next->value)
			{ // mindre gå vidare
				temp = temp->next;
				//std::cout << "if1" << std::endl;
			}
			else if (value == temp->next->value)
			{ // om det redan finns
				return;
			}
			else if (value < temp->next->value) 
			{ // lägger till
				tail->prev = tail->prev->next = newNode;
				counter++;
				//std::cout << "if3" << std::endl;
				return;
			}
		}
		tail->prev = tail->prev->next = newNode;
		counter++;
		//std::cout << "Utanför while-loopen" << std::endl;

	}
	
}
