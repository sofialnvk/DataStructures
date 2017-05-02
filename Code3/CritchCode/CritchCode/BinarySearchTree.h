#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "dsexceptions.h"
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
class BinarySearchTree
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
     * Returns true if x is found in the tree.
     */
    bool contains( const Comparable & x ) const
    {
        return contains( x, root );
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
            printTree( root, out );
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
     * Remove x from the tree. Nothing is done if x is not found.
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
		//Add code
		find_pred_succ(x, pred, suc, root);
	}


	/*class BiIterator
	{
	public:
		BiIterator(BinaryNode* p = nullptr) : current(p) { }

		Comparable& operator*() const;
		Comparable* operator->() const;
		bool operator==(const BiIterator &it) const
		{
			if (current == it->current)
				return true;
			else
				return false;
		}
		bool operator!=(const BiIterator &it) const
		{
			if (this == it)
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
		BinaryNode *current;
	};	*/

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

    BinaryNode *root;



    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( const Comparable & x, BinaryNode * & t )
    {
        if( t == nullptr )
            t = new BinaryNode{ x, nullptr, nullptr, nullptr };
        else if( x < t->element )
        {
            if ( t->left == nullptr )
            {
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
                //t = t->left;
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
                //t = t->right;
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
    void remove( const Comparable & x, BinaryNode * & t )
    {
        if( t == nullptr )
            return;   // Item not found; do nothing
		if (x < t->element)
		{
				remove(x, t->left);
		}

		else if (t->element < x)
		{
			remove(x, t->right);
		}
        else if( t->left != nullptr && t->right != nullptr ) // Two children
        {
            t->element = findMin( t->right )->element;
            remove( t->element, t->right );
        }
        else
        {
            BinaryNode *oldNode = t;
            t = ( t->left != nullptr ) ? t->left : t->right;
			if ( t != nullptr)
				t->parent = oldNode->parent;
            delete oldNode;
        }
    }


	void find_pred_succ(const Comparable& x, Comparable& pred, Comparable& suc, BinaryNode* rt) 
	{
		BinaryNode* t = rt;
		if (x == t->element)
		{
			pred = find_predecessor(t)->element;
			suc = find_successor(t)->element;
		}
		else if (x < t->element)
		{
			find_pred_succ(t->left->element, pred, t->left->element, t->left);
		}
		else
		{
			find_pred_succ(t->right->element, t->right->element, suc, t->right);
		}
	}

	BinaryNode* find_successor(BinaryNode* t)	{		if (t != nullptr && t->right != nullptr) //t has a right sub-tree
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
			//Point to parent
			t = t->parent;
			//If t is left child of parent
			if (t == t->parent->left)
			{
				//Return value of parent
				return t->parent;
			}
			else
			{
				//Move up
				find_successor(t);
			}
		}	}	BinaryNode* find_predecessor(BinaryNode* t)	{		if (t != nullptr && t->left != nullptr) //t has a left sub-tree
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
			//Point to parent
			t = t->parent;
			//If t is right child of parent
			if (t == t->parent->right)
			{
				//Return value of parent
				return t->parent;
			}
			else
			{
				//Move up
				find_predecessor(t);
			}
		}	}

    Comparable get_parent(const Comparable &x, BinaryNode* &t)
    {
        if (!t)
            return Comparable();
        if (x < t->element)
            return get_parent(x, t->left);
        else if (t->element < x)
            return get_parent(x, t->right);
        else
        {
            auto parent = t->parent;

            if (parent)
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
    /*BiIterator* contains( const Comparable & x, BinaryNode *t ) const
    {
        if( t == nullptr )
            return new BiIterator();
        else if( x < t->element )
            return contains( x, t->left );
        else if( t->element < x )
            return contains( x, t->right );
		else
		{
			return new BiIterator(t); // Match
		}

    }*/

	bool contains(const Comparable & x, BinaryNode *t) const
	{
		if (t == nullptr)
			return false;
		else if (x < t->element)
			return contains(x, t->left);
		else if (t->element < x)
			return contains(x, t->right);
		else
			return true;    // Match
	}
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

    void printTreePreOrder( BinaryNode *t, ostream & out ) const
    {
        if( t != nullptr )
        {
            out << t->element << endl;

            printTreePreOrder( t->left, out );
            printTreePreOrder( t->right, out );
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
            return new BinaryNode{ t->element, clone( t->left ), clone( t->right ),  t->parent };
    }
};

#endif
