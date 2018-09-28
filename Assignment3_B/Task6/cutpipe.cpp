#include "genlib.h"
#include "vector.h"
#include <iostream>
#include "simpio.h"

int CutStock(Vector<int> & requests, int stockLength);
int recursion(Vector<int> requests,int stockLength);
void shrink(Vector<int> &requests, int stockLength);
void FindSub(Vector<int> sofar,Vector<int> remain,Vector<int> & result, int stockLength);


int main(){
	Vector<int> requests;

	requests.add(4);
	requests.add(3);
	requests.add(4);
	requests.add(1);
	requests.add(6);
	requests.add(8);

	// shrink(requests,10);
	cout << CutStock(requests,10) << endl;
	// for (int i = 0; i < requests.size();i++)
	// 	cout << requests[i] << endl;

}

int CutStock(Vector<int> & requests, int stockLength){
	Vector<int> temp = requests;
	return recursion(requests,stockLength);
}
int recursion(Vector<int> requests,int stockLength){
	int count = 0;
	for (int i = 0;i < requests.size();i++)
		count += requests[i];
	if (count <= 10)
		return 1;
	shrink(requests,stockLength);
	return 1 + recursion(requests,stockLength);
}
void shrink(Vector<int> &requests, int stockLength){
	// cout << "I am called(shrink)" << endl;
	Vector<int> temp = requests;
	Vector<int> result;
	FindSub(result,requests,result,stockLength);
	// cout << result.size() << endl;
	// for (int i = 0;i < result.size();i++)
		// cout << result[i] << endl;
	for (int i = 0;i < result.size();i++){
		for (int j = 0; j < requests.size();j++){
			if (requests[j] == result[i])
				{requests.removeAt(j); break;}
		} 
	} 
}
void FindSub(Vector<int> sofar,Vector<int> remain,Vector<int> & result, int stockLength){
	// cout << "I am called(FindSub)" << endl;
	if (remain.size() == 0){
		// cout <<"sofar size " << sofar.size() << endl;
		int count1 = 0;
		for (int i = 0;i < sofar.size();i++)
			count1 += sofar[i];
		// cout << "count1 " << count1 << endl;
		if (count1 <= stockLength){
			int count2 = 0;
			for (int i = 0;i < result.size();i++)
			count2 += result[i];
			if (count1 > count2) result = sofar;
		}
	}else{	
			int temp = remain[0];

			remain.removeAt(0);
			FindSub(sofar,remain,result,stockLength);
			sofar.add(temp);
			FindSub(sofar,remain,result,stockLength);
	}
}