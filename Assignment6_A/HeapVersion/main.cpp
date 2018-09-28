/* File: main.cpp
 * --------------
 * Simple main module for PQueue assignment.
 */
 
#include "pqueuetest.h"
#include "performance.h"
#include <iostream>
#include "genlib.h"


/*
 * Use these functions to test your PQueue implementation.
 * Comment out those tests you aren't interested in running
 * while you are mid-development.
 */
int main()
{
	// PQueue pq;
	// cout << pq.size() << endl;
	// for(int i = 1;i < 8;i++)
	// 	pq.enqueue(i);
	// cout << pq.size() << endl << endl;

	// for (int i = 0;i < 7;i++)
	// 	cout << pq.dequeueMax() << endl;
	// cout << pq.size() << endl << endl;

	BasicPQueueTest();
	MorePQueueTest();
	PQueueSortTest();
   	PQueuePerformance();
    cout << endl << "Goodbye and have a nice day!" << endl;
    return (0);
}

