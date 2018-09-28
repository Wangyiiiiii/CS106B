#include "vector.h"
#include "genlib.h"
#include <iostream>
#include "random.h"
#include "other.h"

template <typename Type>
int OperatorCmp(Type one, Type two){
	if (one == two) 
		return 0;
	return (one < two ? -1 : 1);
}
template <typename Type>
void myswap(Type &a,Type &b){
	Type temp = a;
	a = b;
	b = temp;
}
template <typename Type>
void sort(Vector<Type> &arr,int (cmp)(Type one,Type two) = OperatorCmp){
	int len = arr.size();
	len /= 1.3;
	for (;len > 0;len /= 1.3){
		for (int i = 0;i < arr.size() - len;i++){
			if (cmp(arr[i],arr[i + len]) == 1)
				myswap(arr[i],arr[i + len]);
		}
	}
}
int structCmp(decimal a,decimal b);


int main(){
	
	Vector<int> rand_int;
	Vector<decimal> rand_decimal;

	Randomize();
	// for (int i = 0;i < 10;i++)
	// 	rand_int.add(RandomInteger(0,10));
	// sort(rand_int);
	// cout << "rand_int:";
	// for (int i = 0;i < 10;i++)
	// 	cout << rand_int[i] << " ";
	// cout << endl;

	for (int i = 0;i < 10;i++){
		decimal temp;
		temp.before = RandomInteger(0,10);
		temp.after = RandomInteger(0,10);
		rand_decimal.add(temp);
	}
	sort(rand_decimal,structCmp);
	cout << "rand_decimal:";
	for (int i = 0;i < 10;i++)
		cout << rand_decimal[i].before<< "." << rand_decimal[i].after << " ";
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
