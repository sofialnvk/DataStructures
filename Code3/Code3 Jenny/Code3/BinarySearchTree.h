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
        //No children: set corresponding link of parent to nullptr and dispose the node
        else if( t->left == nullptr && t->right == nullptr ) // No children
        {
            if ( t->parent != nullptr)
            {
                BinaryNode* nodeParent = t->parent;
                //If value to be removed was left child
                if (nodeParent->left->element == x)
                    nodeParent->left = nullptr;
                //If value to remove was right child
                else
                    nodeParent->right = nullptr;
            }
            //delete t;

        }
        //Only one child: node is cut from the tree, link single child with its subtree
        //directly to the parent of the removed node
        else if( (t->left != nullptr && t->right == nullptr) || (t->left == nullptr && t->right != nullptr))
        {
            BinaryNode* nextNode = t->left;
            if ( t->parent != nullptr)
            {
                BinaryNode* nodeParent = t->parent;
                //If value to be removed was left child
                if (nodeParent->left->element == x)
                {
                    nodeParent->left = nextNode;
                    nextNode->parent = nodeParent;
                }
                
                //If value to remove was right child
                else
                {
                    nodeParent->right = nextNode;
                    nextNode->parent = nodeParent;
                }
            }
            //If value becomes new root, make parent nullptr
            else
                nextNode->parent = nullptr;
            //delete t;
            t->parent = nullptr;
            t->left = nullptr;
            t->right = nullptr;
        }
        //Two children: choose minium element of right subtree
        // Replace value of node to be removed with found minimun ( Change this later!! )
        // Remove the duplicate
        else //if( t->left != nullptr && t->right != nullptr )
        {
            /*BinaryNode* temp = findMin(t->right);
            BinaryNode* par1 = t->parent;
            BinaryNode* par2 = temp->parent;
            
            
            par1->left = temp;
            par2->left = t;
            
            par2->parent = temp;
            if ( t->left != nullptr)
                t->left->parent = temp;
            
            std::swap(t,temp);*/
            
            
            
            t->element = findMin(t->right)->element;
            remove( t->element, t->right );
        }
        /*else
        {
            BinaryNode *oldNode = t;
            BinaryNode* oldParent = t->parent;
            t = ( t->left != nullptr ) ? t->left : t->right;
            if ( t != nullptr)
                t->parent = oldNode->parent;
            else
                oldParent->left = nullptr;
            delete oldNode;
            oldNode = nullptr;
        }*/
    }
    
    
    void find_pred_succ(const Comparable& x, Comparable& pred, Comparable& suc, BinaryNode* rt)
    {
        BinaryNode* t = rt;
        if (t != nullptr && x == t->element)
        {
            return;
        }
        else if (t != nullptr && x < t->element)
        {
            suc = t->element;
            find_pred_succ(x, pred, suc, t->left);
        }
        else if(t != nullptr)
        {
            pred = t->element;
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
                if (ptr == ptr_parent->right)
                {
                    ptr = ptr->parent;
                    ptr_parent = ptr_parent->parent;
                }
                else
                    return ptr_parent;
            }
        }
        return nullptr;
    }
    
    BinaryNode* find_predecessor(BinaryNode* t)
    {
        if (t != nullptr && t->left != nullptr) //t has a left sub-tree
        {
            return findMax(t->left);
            cout << "hej 4" << endl;
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
                if (ptr == ptr_parent->left)
                {
                    ptr = ptr->parent;
                    ptr_parent = ptr_parent->parent;
                }
                else
                    return ptr_parent;
            }
        }
        return nullptr;
    }
    
    
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
            BinaryNode* ptr = new BinaryNode(t->element,nullptr,nullptr,nullptr);
            ptr->left = clone(t->left);
            ptr->right = clone(t->right);
            
            if(ptr->left != nullptr)
                ptr->left->parent = ptr;
            if(ptr->right != nullptr)
                ptr->right->parent = ptr;
            
            return ptr;
        }
            
            //return new BinaryNode{ t->element, clone( t->left ), clone( t->right ),  t->parent };
    }
    
    
};

#endif
