#include "genlib.h"
#include "vector.h"
#include <iostream>

bool Solvable(int start, Vector<int> & squares);
bool IfSolvable(int start, Vector<int> & squares, Vector<bool> HazardZone);

int main (){
	Vector<int> game_1,game_2;
	
	game_1.add(3);
	game_1.add(6);
	game_1.add(4);
	game_1.add(1);
	game_1.add(3);
	game_1.add(4);
	game_1.add(2);
	game_1.add(5);
	game_1.add(3);
	game_1.add(0);

	game_2.add(3);
	game_2.add(1);
	game_2.add(2);
	game_2.add(3);
	game_2.add(0);

	cout<< Solvable(0,game_2) << endl;
	cout<< Solvable(0,game_1) << endl;

}

bool Solvable(int start, Vector<int> & squares){
	Vector<bool> HazardZone;
	for (int i = 0;i < squares.size();i++)
		HazardZone.add(false);
	return IfSolvable(start,squares,HazardZone);
}
bool IfSolvable(int start, Vector<int> & squares, Vector<bool> HazardZone){
	HazardZone[start] = true;
	if (squares[start] == 0)
		return true;
	for (int i = 0;i < 2;i++){
		switch(i){
			case 0:{
				// cout << start << "  case0  "<<squares[start]<<endl;
				if (start - squares[start] > 0){
					// cout << "go left" << endl;
					if(HazardZone[start - squares[start]] == false){
						if (IfSolvable((start - squares[start]),squares,HazardZone)) return true;
					}
					}
			break;}


			case 1:{
				// cout << start << "  case1  "<<squares[start]<<endl;
				if (start + squares[start] < squares.size()){
					 if (HazardZone[start + squares[start]] == false)
						{if (IfSolvable((start + squares[start]),squares,HazardZone)) return true;

						}}
				break;
					}

		
	}}
	return false;
}