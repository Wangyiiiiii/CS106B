#include "genlib.h"
#include <iostream>
#include "pqueue.h"

void PQueue::swap(int &a,int &b){
	int temp = a;
	a = b;
	b = temp;
}

PQueue::PQueue(){
	elems.add(0);
}

PQueue::~PQueue(){}

bool PQueue::isEmpty(){
	return (elems.size() == 1 or elems.size() == 0);
}

int PQueue::size(){
	return elems.size() - 1;
}

void PQueue::enqueue(int newValue){
	int index;
	elems.add(newValue);
	index = elems.size() - 1;
	for (;index > 1;index /= 2){
		if(elems[index] <= elems[index / 2])
			break;
		swap(elems[index],elems[index / 2]);
	}
	// for (int i = 1; i < elems.size();i++)
	// 	cout << elems[i];
	// cout << endl;
}

int PQueue::dequeueMax(){
	if (isEmpty())
		Error("huh?");
	int max = elems[1];
	int index = 1;
	int nextIndex;
	// for (int i = 1; i < elems.size();i++)
	// 	cout << elems[i];
	// cout << endl;
	if (size() == 1){
		elems.removeAt(1);
		return max;
	}
	swap(elems[1],elems[elems.size() - 1]);
	elems.removeAt(elems.size() - 1);
	// cout << elems.size() - 1 << endl;
	while(1){
		// cout << index <<endl;
		if (index * 2 > elems.size() - 1)
			break;
		if (index * 2 + 1 > elems.size() - 1){
			if (elems[index] < elems[2 * index])
				swap(elems[index],elems[2 * index]);
			break;
		}
		if (elems[index] >= elems[2 * index] and elems[index] >= elems[2 * index + 1] )
			break;
		nextIndex = (elems[2 * index] > elems[2 * index + 1]) ? 2 * index: 2 * index + 1;
		swap(elems[index],elems[nextIndex]);
		index = nextIndex; 
	}
	return max;
}

int PQueue::bytesUsed(){
	return sizeof(*this);
}

string PQueue::implementationName(){
	return "heap list";
}

void PQueue::printDebuggingInfo(){
	cout << "That's it" << endl;
}