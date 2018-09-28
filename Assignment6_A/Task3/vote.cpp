#include <iostream>
#include "simpio.h"
#include "genlib.h"
#include "vector.h"

int CountCriticalVotes(Vector<int> blocks, int blockIndex);
int recursion(int sofar,Vector<int> remain,int StateValue, int TotalValue);

int main(){
	Vector<int> states;
	int num;

	states.add(4);
	states.add(2);
	states.add(7);
	states.add(4);

	while(1){
	cout << "Enter the index:";
	num = GetInteger();
	cout << "Critical times:" <<CountCriticalVotes(states,num) << endl;
	}
}

int CountCriticalVotes(Vector<int> blocks, int blockIndex){
	int num = blocks[blockIndex]; 
	int total = 0;
	int CriticalVotes = 77;

	for (int i = 0;i < blocks.size();i++){
		total += blocks[i];
	}

	blocks.removeAt(blockIndex);
	CriticalVotes = recursion(0,blocks,num,total);

	return CriticalVotes;
}	
int recursion(int sofar,Vector<int> remain,int StateValue, int TotalValue){
	if (remain.size() == 0){
		if (sofar >= (TotalValue/2 + 1) or (sofar + StateValue) < (TotalValue/2 + 1))
			return 0;
		// cout << sofar <<endl;
		return 1;
	}
	else {
		int temp = remain[0];
		remain.removeAt(0);
		// cout << remain.size() << endl;
		return recursion(sofar + temp,remain,StateValue,TotalValue)+recursion(sofar,remain,StateValue,TotalValue);
	}
}