#ifndef LEFTIST_HEAP_H
#define LEFTIST_HEAP_H

#include "dsexceptions.h"
#include <iostream>
#include <queue>
using namespace std;

// Leftist heap class
//
// CONSTRUCTION: with no parameters
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// deleteMin( minItem )   --> Remove (and optionally return) smallest item
// Comparable findMin( )  --> Return smallest item
// bool isEmpty( )        --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void merge( rhs )      --> Absorb rhs into this heap
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class LeftistHeap
{
	  public:
	    LeftistHeap( ) : root( NULL )
	      { comparisons = 0; }
	    LeftistHeap( const LeftistHeap & rhs ) : root( NULL )
	      { *this = rhs; }
	    ~LeftistHeap( )
	      { makeEmpty( ); }
	    
	    /**
	     * Returns true if empty, false otherwise.
	     */
	    bool isEmpty( ) const
	      { return root == NULL; }
	    
	    int getComparisons( ) const
	      { return comparisons; }
	    
	    /**
	     * Find the smallest item in the priority queue.
	     * Return the smallest item, or throw Underflow if empty.
	     */
	    const Comparable & findMin( ) const
	    {
		if( isEmpty( ) )
		    throw UnderflowException( );
		return root->element;
	    }

	    /**
	     * Inserts x; duplicates allowed.
	     */
	    void insert( const Comparable & x )
	      { root = merge( new LeftistNode( x ), root ); }

	    /**
	     * Remove the minimum item.
	     * Throws UnderflowException if empty.
	     */
	    void deleteMin( )
	    {
		if( isEmpty( ) )
		    throw UnderflowException( );

		LeftistNode *oldRoot = root;
		comparisons++;
		
		root = merge( root->left, root->right );
		delete oldRoot;
	    }

	    /**
	     * Remove the minimum item and place it in minItem.
	     * Throws UnderflowException if empty.
	     */
	    void deleteMin( Comparable & minItem )
	    {
		minItem = findMin( );
		deleteMin( );
	    }

	    void displayHeap( ) {
	    	queue<Comparable> pq;
	    	LeftistHeap<Comparable> temp = *this;
	    	pq.push( temp.findMin( ) );
	    	temp.deleteMin( );
	    	
	    	while (!temp.isEmpty( ) ) {
	    		cout << pq.front( ) << endl;
	    		pq.pop( );
	    		pq.push( temp.findMin( ) );
	    		temp.deleteMin( );
	    	}
	    }	
	    		
	    /**
	     * Make the priority queue logically empty.
	     */
	    void makeEmpty( )
	    {
		reclaimMemory( root );
		root = NULL;
	    }

	    /**
	     * Merge rhs into the priority queue.
	     * rhs becomes empty. rhs must be different from this.
	     */
	    void merge( LeftistHeap & rhs )
	    {
		if( this == &rhs )    // Avoid aliasing problems
		    return;

		root = merge( root, rhs.root );
		rhs.root = NULL;
	    }

	    const LeftistHeap & operator=( const LeftistHeap & rhs )
	    {
		if( this != &rhs )
		{
		    makeEmpty( );
		    root = clone( rhs.root );
		    comparisons = rhs.comparisons;
		}
		return *this;
	    }

	  private:
	    struct LeftistNode
	    {
		Comparable   element;
		LeftistNode *left;
		LeftistNode *right;
		int          npl;

		LeftistNode( const Comparable & theElement, LeftistNode *lt = NULL,
		                LeftistNode *rt = NULL, int np = 0 )
		  : element( theElement ), left( lt ), right( rt ), npl( np ) { }
	    };

	    int comparisons;
	    LeftistNode *root;

	    /**
	     * Internal method to merge two roots.
	     * Deals with deviant cases and calls recursive merge1.
	     */
	    LeftistNode * merge( LeftistNode *h1, LeftistNode *h2 )
	    {
		if( h1 == NULL ) {
		    return h2;
		    comparisons++;
		}
		
		if( h2 == NULL ) {
		    return h1;
		    comparisons++;
		}
		
		if( h1->element < h2->element )
		    return merge1( h1, h2 );
		else 
		    return merge1( h2, h1 );
	    }

	    /**
	     * Internal method to merge two roots.
	     * Assumes trees are not empty, and h1's root contains smallest item.
	     */
	    LeftistNode * merge1( LeftistNode *h1, LeftistNode *h2 )
	    {
		if( h1->left == NULL ) { // Single node
		    h1->left = h2;       // Other fields in h1 already accurate
		    comparisons++;
		}
		
		else
		{
		    h1->right = merge( h1->right, h2 );
		    if( h1->left->npl < h1->right->npl )
		        swapChildren( h1 );
		    h1->npl = h1->right->npl + 1;
		    comparisons++;
		}
		return h1;
	    }

	    /**
	     * Swaps t's two children.
	     */
	    void swapChildren( LeftistNode *t )
	    {
		LeftistNode *tmp = t->left;
		t->left = t->right;
		t->right = tmp;
		comparisons += 3;
	    }

	    /**
	     * Internal method to make the tree empty.
	     * WARNING: This is prone to running out of stack space;
	     *          exercises suggest a solution.
	     */
	    void reclaimMemory( LeftistNode *t )
	    {
		if( t != NULL )
		{
		    reclaimMemory( t->left );
		    reclaimMemory( t->right );
		    delete t;
		}
	    }
	    
	    /**
	     * Internal method to clone subtree.
	     * WARNING: This is prone to running out of stack space.
	     *          exercises suggest a solution.
	     */
	    LeftistNode * clone( LeftistNode *t ) const
	    {
		if( t == NULL )
		    return NULL;
		else
		    return new LeftistNode( t->element, clone( t->left ), clone( t->right ), t->npl );
	    }
	};

#endif
