#include "vector.h"
#include "genlib.h"
#include <iostream>
#include "random.h"

void swap(int &a,int &b);
void sort(Vector<int> &arr);

int main(){
	
	Vector<int> rand_int;

	Randomize();
	for (int i = 0;i < 10;i++)
		rand_int.add(RandomInteger(0,10));
	sort(rand_int);
	cout << "rand_int:";
	for (int i = 0;i < 10;i++)
		cout << rand_int[i] << " ";
	cout << endl;


}

void swap(int &a,int &b){
	int temp = a;
	a = b;
	b = temp;
}
void sort(Vector<int> &arr){
	int len = arr.size();
	len /= 1.3;
	for (;len > 0;len /= 1.3){
		for (int i = 0;i < arr.size() - len;i++){
			if (arr[i] > arr[i + len])
				swap (arr[i],arr[i + len]);
		}
	}
}