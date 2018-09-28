#include <iostream>
#include "genlib.h"
#include "simpio.h"

int CountWays(int numStairs);

int main(){
	int num;
	while (1){
	num = GetInteger();
	cout <<"There are " << CountWays(num) <<" ways to get up " << num << " floors." << endl;
	// cout << num;
	}
}

int CountWays(int numStairs){
	if (numStairs <= 1)
		return 1;

	return CountWays(numStairs - 1) + CountWays(numStairs -2);

}