/* File: main.cpp
 * --------------
 * Simple main module for PQueue assignment.
 */
 
#include <iostream>
#include "genlib.h"
#include "random.h"
#include "pqueue.h"
#include "cmpfn.h"
#include "other.h"
/*
 * Use these functions to test your PQueue implementation.
 * Comment out those tests you aren't interested in running
 * while you are mid-development.
 */
int structCmp(decimal a,decimal b);

int main()
{
	PQueue<int> pqint;
	PQueue<decimal> pqdec(structCmp);
	Randomize();

	cout << "Here are ints" << endl;
	
	for (int i = 0;i < 10;i++)
		pqint.enqueue(RandomInteger(0,100));

	for (int i = 0;i < 10;i++)
		cout << pqint.dequeueMax() << endl;

	cout << "Here are stucts" << endl;
	for (int i = 0;i < 10;i++){
		decimal temp;
		temp.before = RandomInteger(0,10);
		temp.after = RandomInteger(0,10);
		pqdec.enqueue(temp);
	} 
	for (int i = 0;i < 10;i++){
		decimal temp = pqdec.dequeueMax();
		cout << temp.before << "." << temp.after << " ";
	}
	cout << endl;
		
}

int structCmp(decimal a,decimal b){
	if (a.before > b.before)
		return 1;
	if (a.before < b.before)
		return -1;
	if (a.after > b.after)
		return 1;
	if (a.after < b.after)
		return -1;
	return 0;  
}