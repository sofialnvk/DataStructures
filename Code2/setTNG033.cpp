#include "set.h"
#include <new>
#include <cassert>  //assert
#include <iomanip>

//Default constructor
Set::Set ()
{
    //If there is no input arguments, create an empty list with dummy node
    head = new Node(0, nullptr); //Dummynode
    head->next = nullptr;

}

//Constructor creating a set
//from n integers in a non-sorted array a
Set::Set (int a[], int n)
{
    //Create dummy node
    head = new Node(0, nullptr);
    //Insert elements from array to the list
    for(int i = 0; i < n; i++)
    {
        insert(a[i]);
    }
}

//copy constructor
Set::Set (const Set &source)
{
    //Create new set dummy node
    head = new Node(0, nullptr);
    for (Node* ptr = source.head->next; ptr; ptr = ptr->next )
    {
        insert(ptr->value);
    }

}

//Destructor: deallocate all nodes
Set::~Set ()
{
    for (Node* n = head; n; n = head)
    {
        //Point to the value after n, then delete n
        head = head->next;
        delete n;
    }
}

//Test if set is empty
bool Set::empty () const
{
    //If the list is empty (after dummy node).
    if(!head->next) //head->next==nullptr
        return true;
    else
        return false;

}

//Return number of elements in the set
int Set::cardinality() const
{
    Node *ptr = head;
    int elements = 0; //Number of elements in set

    while(ptr->next != nullptr)
    {
        //Increment number of elements and point to next value
        elements++;
        ptr = ptr->next;
    }

    return elements;
}

//Test if x is an element of the set
//If x is found the function returns true
bool Set::member (int x) const
{
    Node *p = head->next;  //skip the dummy node
    //Point to the next value until we find a value that is equal to x or we reach the end of the list
    while( (p != nullptr) && (p->value != x) )
        p = p->next;

    return p;

}

//Subset
bool Set:: operator<=(const Set& b) const
{
    Node *right = this->head->next;

    while (right != nullptr)
    {
		if(!b.member(right->value))
            return false;
		right = right->next;
	}
    return true;
}

//If the sets are exactly equal
bool Set:: operator==(const Set& b) const
{
    Set temp(*this); //copy constructor is called

    Node *left = temp.head->next;
    Node *right = b.head->next;

    if(temp.cardinality() != b.cardinality())
        return false;
    else
    {
        while ((left->next != nullptr) && (right->next != nullptr))
        {
            if (left->next->value != right->next->value)
                return false;
            left = left->next;
            right = right->next;
        }
        return true;
    }
}

//Proper subset
bool Set:: operator<(const Set& b)  const
{

    if(this->head<=b.head)
    {
        if(this->cardinality() < b.cardinality())
            return true;
    }
    return false;
}

//Set union
//Repeated values are not allowed
Set Set::operator+ (const Set& b) const
{
    Node* left = head->next;
    Node* right = b.head->next;
    Set newSet;

    while(left)
    {
        newSet.insert(left->value);
        left = left->next;
    }
    while(right)
    {
        newSet.insert(right->value);
        right = right->next;
    }

    return newSet;


//    Set n = *this;
//	if(!n.member(right->value)){
//		n.insert(right->value);
//		right = right->next;
//	}
//	return n;




}

//Set intersection
Set Set::operator* (const Set& b) const
{
    //Node* left = head->next;
    Node* right = b.head->next;
    Set newSet;

    //combine the sets
    while (right)
    {
        if(this->member(right->value)){
            newSet.insert(right->value);
        }
        right = right->next;
    }

    return newSet;
}

//Set difference
Set Set::operator- (const Set& b) const
{
    Set newSet(*this);

    Node *right = b.head->next;

    while(right != nullptr)
    {
        newSet.del(right->value);
		right = right->next;
    }
    return newSet;
}

//set union with set {x}
Set Set::operator+(int x) const
{
    Set n = *this;
	if(!n.member(x)){
		n.insert(x);
	}
	return n;

}

//set difference with set {x}
Set Set::operator-(int x) const
{
    Set n = *this;
	if(n.member(x)){
		n.del(x);
	}
	return n;
}

//Assignment operator
const Set& Set::operator=(const Set &s)
{
    if (this != &s) //self assignment
    {
        //Copy constructorperforms a deep copy
        Set copy(s);
        swap(head, copy.head); //swap the pointers
        swap(head->value, copy.head->value);
    }


    return *this;
}

ostream& operator<< (ostream& os, const Set& theSet)
{
    Node *ptr = theSet.head->next;
    if(!ptr)
        cout << "Set is empty! " << endl;
    else
    {
        os << setw(2) << "{";
        while(ptr != nullptr)
        {
            os << ptr->value << " ";
            ptr = ptr->next;
        }

        os << "}" << endl;
    }


    return os;
}
void Set::insert(int value)
{
    Node *newNode = new Node(value, nullptr);

    if(empty())
    {
        newNode->next = head->next; //link the new node to the node after the dummy node
        head->next = newNode;//Insert after the dummy node
	}
	else {
		Node* temp = head;
		while (temp->next){ // tittar en framåt
			if(value > temp->next->value){ // mindre gå vidare
				temp = temp->next;
			}
			else if(value == temp->next->value){ // om det redan finns
				return;
			}
			else if	(value < temp->next->value){ // lägger till
                newNode->next = temp->next; //link the new node to the node after the dummy node
                temp->next = newNode;//Insert after the dummy node
                return;
			}
		}
        newNode->next = temp->next; //link the new node to the node after the dummy node
        temp->next = newNode;//Insert after the dummy node
	} 

}

void Set::del(int value)
{
    Node *ptr = head;  //DONT skip the dummy node ??

    while( (ptr->next != nullptr) && (ptr->next->value != value))  //do not swap the tests
        ptr = ptr->next;

    //If we find the value we want to delete
    if (ptr->next != nullptr)
    {
        //2. Remove
        Node *node = ptr->next;
        ptr->next = node->next;
        delete node; //deallocate
    }

}


