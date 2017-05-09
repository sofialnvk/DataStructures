#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "dsexceptions.h"
#include "keyCount.h"
#include <algorithm>

using namespace std;

// BinarySearchTree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class BinarySearchTree : public keyCount
{
public:

    BinarySearchTree( ) : root{ nullptr }
    {
    }

    /**
     * Copy constructor
     */
    BinarySearchTree( const BinarySearchTree & rhs ) : root{ nullptr }
    {
        root = clone( rhs.root );
    }

    /**
     * Move constructor
     */
    BinarySearchTree( BinarySearchTree && rhs ) : root{ rhs.root }
    {
        rhs.root = nullptr;
    }

    /**
     * Destructor for the tree
     */
    ~BinarySearchTree( )
    {
        makeEmpty( );
    }

    /**
     * Copy assignment
     */
    BinarySearchTree & operator=( const BinarySearchTree & rhs )
    {
        BinarySearchTree copy = rhs;
        std::swap( *this, copy );
        return *this;
    }

    /**
     * Move assignment
     */
    BinarySearchTree & operator=( BinarySearchTree && rhs )
    {
        std::swap( root, rhs.root );
        return *this;
    }


    /**
     * Find the smallest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMin( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMin( root )->element;
    }

    /**
     * Find the largest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMax( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMax( root )->element;
    }

    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty( ) const
    {
        return root == nullptr;
    }

    /**
     * Print the tree contents in sorted order.
     */
    void printTree( ostream & out = cout ) const
    {
        if( isEmpty( ) )
            out << "Empty tree" << endl;
        else
            printTreePreOrder( root, out);
    }

    /**
     * Make the tree logically empty.
     */
    void makeEmpty( )
    {
        makeEmpty( root );
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    //Insert for keyCount
    /*void insert( Comparable  x )
    {
        insert( x, root );
    }*/

    void insert( const Comparable & x )
    {
        insert( x, root );
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( Comparable && x )
    {
        insert( std::move( x ), root );
    }

    /**
     * x from the tree. Nothing is done if x is not found.
     */
    void remove( const Comparable & x )
    {
        remove( x, root );
    }

    Comparable get_parent(const Comparable &x)
    {
        return get_parent(x, root);
    }

    void find_pred_succ(const Comparable& x, Comparable& pred, Comparable& suc)
    {
        find_pred_succ(x, pred, suc, root);
    }

private:
    struct BinaryNode
    {
        Comparable element;
        BinaryNode *left;
        BinaryNode *right;
        BinaryNode *parent;

        BinaryNode( const Comparable & theElement, BinaryNode *lt, BinaryNode *rt, BinaryNode *pt )
        : element{ theElement }, left{ lt }, right{ rt }, parent{ pt } { }

        BinaryNode( Comparable && theElement, BinaryNode *lt, BinaryNode *rt, BinaryNode *pt )
        : element{ std::move( theElement ) }, left{ lt }, right{ rt }, parent{ pt } { }
    };

public:
     class BiIterator : public BinarySearchTree
     {
     public:
         BiIterator(BinaryNode* p = nullptr) : current(p) { }

         Comparable& operator*() const
         {
             return current->element;
         }
         Comparable* operator->() const
         {
             return &(current->element);
         }
         bool operator==(const BiIterator &it) const
         {
             if (current == it.current)
                 return true;
             else
                 return false;
         }
         bool operator!=(const BiIterator &it) const
         {
             if (*this == it)
                 return false;
             else
                 return true;
         }
         BiIterator& operator++() //pre-increment
         {
             current = find_successor(current);
             return *this;
         }
         BiIterator& operator--() //pre-decrement
         {
             current = find_predecessor(current);
             return *this;
         }

        private:
            BinaryNode *current;
     };

    /**
     * Returns true if x is found in the tree.
     */
     BiIterator contains( const Comparable & x ) const
     {
        return contains( x, root );
     }

     /*bool contains( const Comparable & x ) const
     {
        return contains( x, root );
     }*/

     BiIterator begin() const
     {
         if (isEmpty()) return end();
         return BiIterator(findMin(root));
     }

     BiIterator end() const
     {
         return BiIterator();
     }

private:
    BinaryNode *root;

    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    //Insert for keyCount
    /*void insert( Comparable  x, BinaryNode * & t )
    {
        if( t == nullptr )
        {
            increment_counter(x);
            t = new BinaryNode{ x, nullptr, nullptr, nullptr };
        }
        else if( x < t->element )
        {
            if ( t->left == nullptr )
            {
                increment_counter(x);
                //t = t->left;
                BinaryNode* p;
                p = new BinaryNode{ x, nullptr, nullptr, nullptr };
                t->left = p;
                p->parent = t;
            }
            else
                insert( x, t->left);
        }
        else if( t->element < x )
        {
            if ( t->right == nullptr )
            {
                increment_counter(x);
                //t = t->right;
                BinaryNode* p;
                p = new BinaryNode{ x, nullptr, nullptr, nullptr };
                t->right = p;
                p->parent = t;
            }
            else
                insert( x, t->right);
        }
        else
        {

            increment_counter(t->element);  // Duplicate; do nothing
        }
    }*/

    void insert( const Comparable & x, BinaryNode * & t )
    {
        //If the tree is empty, create a new node
        if( t == nullptr )
            t = new BinaryNode{ x, nullptr, nullptr, nullptr };
        //If x is smaller than the root, enter the left subtree
        else if( x < t->element )
        {
            //If there is no left subtree, insert value
            if ( t->left == nullptr )
            {
                //Create a node with value x
                BinaryNode* p;
                p = new BinaryNode{ x, nullptr, nullptr, nullptr };
                //Link the parent to the new node
                t->left = p;
                //Link new node to parent
                p->parent = t;
            }
            //if there is a left subtree
            else
                insert( x, t->left);
        }
        //If x is larger than the root, enter the right subtree
        else if( t->element < x )
        {
            //If there is no right subtree, insert value
            if ( t->right == nullptr )
            {
                BinaryNode* p;
                p = new BinaryNode{ x, nullptr, nullptr, nullptr };
                t->right = p;
                p->parent = t;
            }
            else
                insert( x, t->right);
        }
        else
        {
            ;  // Duplicate; do nothing
        }
    }

    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( Comparable && x, BinaryNode * & t, BinaryNode* parent )
    {
        if( t == nullptr )
            t = new BinaryNode{ std::move( x ), nullptr, nullptr, parent };
        else if( x < t->element )
        {
            if ( t->left == nullptr )
            {
                BinaryNode* p;
                p = new BinaryNode{ std::move( x ), nullptr, nullptr, nullptr };
                t->left = p;
                p->parent = t;
            }
            else
                insert( std::move( x ), t->left);
        }
        else if( t->element < x )
        {
            if ( t->right == nullptr )
            {
                BinaryNode* p;
                p = new BinaryNode{ std::move( x ), nullptr, nullptr, nullptr };
                t->right = p;
                p->parent = t;
            }
            else
                insert( std::move( x ), t->right);
        }

        else
        {
            ;  // Duplicate; do nothing
        }
    }

    /**
     * Internal method to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */

    BinaryNode* remove_aux( const Comparable & x, BinaryNode* t )
    {
        //Create a temporary node which is the node we want to remove
        BinaryNode* oldNode = t;
        //BinaryNode* oldParent = t->parent;

        //Point t to its child
        // Aida say?? BUT WHY?? t->parent->left or right
        t = ( t->left != nullptr ) ? t->left : t->right;
        //If t has a child
        if ( t != nullptr)
        {
            if(oldNode->parent->left->element == x)
            {
                //Point the child to its new parent
                t->parent = oldNode->parent;
                oldNode->parent->left = t;
            }
            else
            {
                t->parent = oldNode->parent;
                oldNode->parent->right = t;
            }
        }

        //If t is childless
        //Remove "link" to the deleted child
        if(oldNode->parent->left->element == x)
        {
            oldNode->parent->left = nullptr;
        }
        else
        {
            oldNode->parent->right = nullptr;
        }

        //Free the node from all responsibilities
        oldNode->parent = nullptr;
        oldNode->left = nullptr;
        oldNode->right = nullptr;

        cout << "hej : " << endl;
        printTree();
        //Return the node
        return oldNode;
    }


    void remove( const Comparable & x, BinaryNode * & t )
    {
        // Item not found; do nothing
        if( t == nullptr )
            return;
        //If x is smaller than the root, search in left subtree for x
        if (x < t->element)
        {
            remove(x, t->left);
        }
        //If x is larger than the root, search in right subtree for x
        else if (t->element < x)
        {
            remove(x, t->right);
        }
        //If the node has two children
        else if (t->left!= nullptr && t->right!=nullptr)
        {
            //Find min in the right subtree
            //Assign the min value to t
            //t->element = findMin(t->right)->element;
            //Remove the duplicates
            BinaryNode* testL = t->left;
            BinaryNode* testR = t->right;
            BinaryNode* temp = findMin(t->right);
            BinaryNode* temp1 = remove_aux(temp->element,temp);

            //If node to be removed was a left child
            if(t->parent->left->element == x)
            {
                //Point the child to its new parent
                t->parent->left = temp1;
                temp1->parent = t->parent;
            }
            else
            {
                t->parent->right = temp1;
                temp1->parent = t->parent;
            }
            t->parent = nullptr;

            temp1->left = t->left;
            testL->parent = temp1;
            t->left = nullptr;

            temp1->right = t->right;
            testR->parent = temp1;
            t->right = nullptr;



            //remove( t->element, t );
        }
        //If the node has one child or no child
        else
        {
            remove_aux(t->element, t);
        }
    }


    //Function to find the largest number that is smaller than x = pred
    //and the smallest value larger than x = succ
    void find_pred_succ(const Comparable& x, Comparable& pred, Comparable& suc, BinaryNode* rt)
    {
        //Create a temporary node of the root
        BinaryNode* t = rt;
        //Return if element is found
        if (t != nullptr && x == t->element)
        {
            return;
        }
        else if (t != nullptr && x < t->element)
        {
            //We know that the smallest value larger than x can be at most the value of t
            //Therefore, we update the successor
            suc = t->element;
            //Keep looking in the left subtree
            find_pred_succ(x, pred, suc, t->left);
        }
        else if(t != nullptr)
        {
            //We know that the largest value smaller than x can be at least the value of t
            //Therefore, we update the predecessor
            pred = t->element;
            //Keep looking in the right subtree
            find_pred_succ(x, pred, suc, t->right);
        }
    }

    BinaryNode* find_successor(BinaryNode* t)
    {
        if (t != nullptr && t->right != nullptr) //t has a right sub-tree
        {
            return findMin(t->right);
        }
        else //successor is one of the ancestors
        {
            /*
             Algorithm: climb up using the parent pointer until
             one finds a node N which is left child of its parent
             The parent of N is the successor of node t
             */
            BinaryNode* ptr = t;
            BinaryNode* ptr_parent = t->parent;
            while(ptr_parent != nullptr)
            {
                //If the node is left child of parent, return parent
                if (ptr == ptr_parent->left)
                {
                    return ptr_parent;
                }
                //Move up in tree
                else
                {
                    ptr = ptr->parent;
                    ptr_parent = ptr_parent->parent;
                }

            }
        }
        return nullptr;
    }

    BinaryNode* find_predecessor(BinaryNode* t)
    {
        if (t != nullptr && t->left != nullptr) //t has a left sub-tree
        {
            return findMax(t->left);
        }
        else //predecessor is one of the ancestors
        {
            /*
             Algorithm: climb up using the parent pointer until
             one finds a node N which is right child of its parent
             The parent of N is the predecessor of node t
             */
            BinaryNode* ptr = t;
            BinaryNode* ptr_parent = t->parent;
            while(ptr_parent != nullptr)
            {
                //If the node is right child of parent, return parent
                if (ptr == ptr_parent->right)
                {
                    return ptr_parent;
                }
                //Move up in tree
                else
                {
                    ptr = ptr->parent;
                    ptr_parent = ptr_parent->parent;
                }
            }
        }
        return nullptr;
    }

    //
    Comparable get_parent(const Comparable &x, BinaryNode* &t)
    {
        //If element is not in the tree
        if (t == nullptr)
            return Comparable();
        //Enter left subtree
        if (x < t->element)
            return get_parent(x, t->left);
        //Enter right subtree
        else if (t->element < x)
            return get_parent(x, t->right);
        //Element found
        else
        {
            //Create a node to parent of t
            BinaryNode *parent = t->parent;

            //If t is not the root of the tree
            if (parent != nullptr)
                return parent->element;
            else
                return Comparable();
        }
    }

    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    BinaryNode * findMin( BinaryNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        if( t->left == nullptr )
            return t;
        return findMin( t->left );
    }

    /**
     * Internal method to find the largest item in a subtree t.
     * Return node containing the largest item.
     */
    BinaryNode * findMax( BinaryNode *t ) const
    {
        if( t != nullptr )
            while( t->right != nullptr )
                t = t->right;
        return t;
    }


    /**
     * Internal method to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the subtree.
     */
     BiIterator contains( const Comparable & x, BinaryNode *t ) const
     {
         if( t == nullptr )
             return *new BiIterator();
         else if( x < t->element )
             return contains( x, t->left );
         else if( t->element < x )
             return contains( x, t->right );
         else
         {
             return *new BiIterator(t); // Match
         }

     }

	/*bool contains(const Comparable & x, BinaryNode *t) const
	{
		if (t == nullptr)
			return false;
		else if (x < t->element)
			return contains(x, t->left);
		else if (t->element < x)
			return contains(x, t->right);
		else
			return true;    // Match
	}*/
    /****** NONRECURSIVE VERSION*************************
     bool contains( const Comparable & x, BinaryNode *t ) const
     {
     while( t != nullptr )
     if( x < t->element )
     t = t->left;
     else if( t->element < x )
     t = t->right;
     else
     return true;    // Match

     return false;   // No match
     }
     *****************************************************/

    /**
     * Internal method to make subtree empty.
     */
    void makeEmpty( BinaryNode * & t )
    {
        if( t != nullptr )
        {
            makeEmpty( t->left );
            makeEmpty( t->right );
            delete t;
        }
        t = nullptr;
    }

    /**
     * Internal method to print a subtree rooted at t in sorted order.
     * In-order traversal is used
     */
    void printTree( BinaryNode *t, ostream & out ) const
    {
        if( t != nullptr )
        {
            printTree( t->left, out );
            out << t->element << endl;
            printTree( t->right, out );
        }
    }

    void printTreePreOrder( BinaryNode *t, ostream & out, int count_width = 0 ) const
    {
        if( t != nullptr )
        {
            out << setw(count_width) << t->element << endl;
            printTreePreOrder( t->left, out, count_width+5 );
            printTreePreOrder( t->right, out, count_width+5 );
        }
    }

    /**
     * Internal method to clone subtree.
     */
    BinaryNode * clone( BinaryNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        else
        {
            //Create a pointer ptr with the element of t
            BinaryNode* ptr = new BinaryNode(t->element,nullptr,nullptr,nullptr);
            //Clone the left node of t
            ptr->left = clone(t->left);
            //lone the right node of t
            ptr->right = clone(t->right);

            //If ptr has a left child
            if(ptr->left != nullptr)
                //Link it to its parent
                ptr->left->parent = ptr;
            //If ptr has a right child
            if(ptr->right != nullptr)
                //Link it to its parent
                ptr->right->parent = ptr;

            return ptr;
        }

            //return new BinaryNode{ t->element, clone( t->left ), clone( t->right ),  t->parent };
    }


};

#endif
