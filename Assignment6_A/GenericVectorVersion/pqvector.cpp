/*
 * File: pqvector.cpp
 * ------------------
 * This file implements the priority queue class as a vector
 * of integers stored in no particular order.  This makes it easy
 * enqueue new elements, but hard to dequeue the max (have to search for it).
 *
 * Julie Zelenski, CS106
 */
 
#include "pqueue.h"
#include "genlib.h"
#include <iostream>
// #include "vector.h"
// #include "random.h"

/* Implementation notes: PQueue class
 * ----------------------------------
 * The private section for the pqvector looks like this:
 *
 *	Vector<int> entries;
 */


template <typename ElemType>
PQueue<ElemType>::PQueue(int (*cmp)(ElemType,ElemType))
{
	cmpFn = cmp;
}

template <typename ElemType>
PQueue<ElemType>::~PQueue()
{
}

template <typename ElemType>
bool PQueue<ElemType>::isEmpty()
{
    return (entries.isEmpty());  
}

template <typename ElemType>
int PQueue<ElemType>::size()
{
	return (entries.size());
}


/* Implementation notes: enqueue
 * -----------------------------
 * Since we're keeping the vector in no particular order, we just append this
 * new element to the end.  It's the easiest/fastest thing to do.
 */
template <typename ElemType>
void PQueue<ElemType>::enqueue(ElemType newValue)
{
	entries.add(newValue);
}


/* Implementation notes: dequeueMax
 * --------------------------------
 * Since we're keeping the vector in no particular order, we have to search to
 * find the largest element.  Once found, we remove it from the vector and
 * return that value.
 */
template <typename ElemType>
ElemType PQueue<ElemType>::dequeueMax()
{	
	if (isEmpty())
		Error("Tried to dequeue max from an empty pqueue!");
		
	int maxIndex = 0;	// assume first element is largest until proven otherwise
	ElemType maxValue = entries[0];
	for (int i = 1; i < entries.size(); i++) {
		if (cmpFn(entries[i],maxValue) == 1 ){
			maxValue = entries[i];
			maxIndex = i;
		}
	}
	entries.removeAt(maxIndex);	// remove entry from vector
	return maxValue;
}

template <typename ElemType>		
int PQueue<ElemType>::bytesUsed() 
{
	return sizeof(*this) + entries.bytesUsed();
}

template <typename ElemType>
string PQueue<ElemType>::implementationName()
{
	return "unsorted vector";
}

template <typename ElemType>
void PQueue<ElemType>::printDebuggingInfo()
{
	cout << "------------------ START DEBUG INFO ------------------" << endl;
	cout << "Pqueue contains " << entries.size() << " entries" << endl;
	for (int i = 0; i < entries.size(); i++) 
		cout << entries[i] << " ";
	cout << endl;
	cout << "------------------ END DEBUG INFO ------------------" << endl;
}

