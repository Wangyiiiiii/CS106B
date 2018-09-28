#include "pqueue.h"
#include "genlib.h"
#include <iostream>


bool PQueue::isFull(chunk* elem){
	bool b = true;
	for (int i = 0;i < MaxElemsPerBlock;i++){
		if (elem->manage[i] == false)
			{b = false;break;} 
	}
	return b;
}

void PQueue::GoDown(chunk* elem){
	int count = 0;
	for (int i = 0;i < MaxElemsPerBlock;i++){
		if (elem->manage[i] == true)
			count++;
	}
	for (int i = 0;i < count;i++){
		if (elem->manage[MaxElemsPerBlock - 1 - i] == false){
			for (int j = MaxElemsPerBlock - 2 - i;j > -1;j--){
				if (elem->manage[j] == true){
					elem->manage[MaxElemsPerBlock - 1 - i] = true;
					elem->arr[MaxElemsPerBlock - 1 - i] = elem->arr[j];
					elem->manage[j] == false; 
				}
			}	
		}
	}
}

PQueue::PQueue(){
	head = NULL;
	length = 0;
}

PQueue::~PQueue(){
	while (head != NULL) {
    	chunk *next = head->next;
    	delete head;
    	head = next;
    }
}

bool PQueue::isEmpty(){
	return (head == NULL);
}

int PQueue::size(){
	return length;
}

void PQueue::enqueue(int newValue){
	chunk *cur;
	int FirstIndex;
	chunk *prev;
	int ProperIndex = -1;

	if (isEmpty()){
		chunk *newOne = new chunk;
		for (int i = 0;i < MaxElemsPerBlock;i++)
			newOne->manage[i] = false;
		newOne->arr[0] = newValue;
		newOne->manage[0] = true;
		head = newOne;
		length++;
		// cout << "type1" << endl;
		return;
	}
	
	cur = head;
	for (;cur->next != NULL;cur = cur->next){
		for (int i = 0;i < MaxElemsPerBlock;i++){
			if (cur->manage[i] == true)
				FirstIndex = i;
				break;
		}
		if (newValue >= cur->arr[FirstIndex])
			break;
	}
	if (newValue >= cur->arr[FirstIndex]){
		if (cur == head){
			if(!isFull(cur)){
				GoDown(cur);
				cur->arr[0] = newValue;
				cur->manage[0] = true;
				length++;
				// cout << "type2" << endl;
				return;
			}
			chunk* newOne = new chunk;
			for (int i = 0;i < MaxElemsPerBlock;i++)
				newOne->manage[i] = false;
			newOne->arr[0] = newValue;
			newOne->manage[0] = true;
			newOne->next = head;
			head = newOne;
			length++;
			// cout << "type3" << endl;
			return;
		}
		for (prev = head;prev->next != cur;prev = prev->next);
		for (int i = 0;i < MaxElemsPerBlock;i++){
			// cout << i <<":";
			if (prev->manage[i] == false){
				// cout << "false" << endl;
				ProperIndex = i;continue;
			}
			// cout << newValue << "vs" << prev->arr[i] << endl;
			if (newValue >= prev->arr[i])
				{ProperIndex = i;break;}
			else
				ProperIndex = -1;
		}
		if (ProperIndex == -1){
			if (isFull(cur)){
				chunk* newOne = new chunk;
				for (int i = 0;i < MaxElemsPerBlock;i++)
					newOne->manage[i] = false;
				newOne->arr[0] = newValue;
				newOne->manage[0] = true;
				newOne->next = cur;
				prev->next = newOne;
				length++;
				// cout << "type4" << endl;
				return;
			}
			GoDown(cur);
			cur->arr[0] = newValue;
			cur->manage[0]=true;
			length++;
			// cout << "type5" << endl;
			return;
		}
		if (prev->manage[ProperIndex] == false){
			prev->arr[ProperIndex] = newValue;
			prev->manage[ProperIndex] = true;
			length++;
			// cout << "type6" << endl;
			return;
		}

		chunk* newOne = new chunk;
		for (int i = 0;i < MaxElemsPerBlock;i++)
			newOne->manage[i] = false;
		for(int i = ProperIndex,j = 0;i < MaxElemsPerBlock;i++,j++){
			if (prev->manage[i] == true){
				newOne->arr[j] = prev->arr[i];
				newOne->manage[j] = true;
				prev->manage[i] = false;
			}
		}
		prev->arr[ProperIndex] = newValue;
		prev->manage[ProperIndex] = true;
		length++;
		newOne->next = cur;
		prev->next = newOne;
		// cout << "type7" << endl;
		return;
	}
	for (int i = 0;i < MaxElemsPerBlock;i++){
			if (cur->manage[i] == false)
				{ProperIndex = i;continue;}
			if (newValue >= cur->arr[i])
				{ProperIndex = i;break;}
			else
				ProperIndex = -1;
		}
	if (ProperIndex == -1){
		chunk* newOne = new chunk;
		for (int i = 0;i < MaxElemsPerBlock;i++)
			newOne->manage[i] = false;
		newOne->arr[0] = newValue;
		newOne->manage[0] = true;
		cur->next = newOne;
		length++;
		// cout << "type8" << endl;
		return;
	}

	if (cur->manage[ProperIndex] == false){
			cur->arr[ProperIndex] = newValue;
			cur->manage[ProperIndex] = true;
			length++;
			return;
		}

	chunk* newOne = new chunk;
	for (int i = 0;i < MaxElemsPerBlock;i++)
		newOne->manage[i] = false;
	int j = 0;
	for(int i = ProperIndex;i < MaxElemsPerBlock;i++,j++){
		if (cur->manage[i] == true){
			newOne->arr[j] = cur->arr[i];
			newOne->manage[j] = true;
			cur->manage[i] = false;
		}
	}
	cur->arr[ProperIndex] = newValue;
	cur->manage[ProperIndex] = true;
	length++;
	cur->next = newOne;
	// cout << "type9" << endl;
	return;
}

int PQueue::dequeueMax(){
	int maxIndex,maxValue;
	bool b = false;

	if (isEmpty())
		Error("huh?");
	for (int i = 0;i < MaxElemsPerBlock;i++){
		if (head->manage[i] == true){
			maxIndex = i;
			break;
		}
	}
	maxValue = head->arr[maxIndex];
	head->manage[maxIndex] = false;
	for (int i = 0;i < MaxElemsPerBlock;i++){
		if (head->manage[i] == true)
			{b = true;break;}
	}
	if (!b){
		// chunk* temp = head;
		head = head->next;
		// delete temp;
	}
	length--;
	return maxValue;
}

int PQueue::bytesUsed(){
	int total = sizeof(*this);
	for (chunk *cur = head; cur != NULL; cur = cur->next)
		total += sizeof(*cur);
	return total;
}
string PQueue::implementationName(){
	return "chunk linked list";
}

void PQueue::printDebuggingInfo(){
	cout << "I don't like this" << endl; 
}