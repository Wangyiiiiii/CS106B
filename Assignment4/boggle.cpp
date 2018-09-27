/* File: boggle.cpp
 * ----------------
 * Your name here!
 */
 
#include "genlib.h"
#include "simpio.h"
#include <iostream>
#include "extgraph.h"
#include "gboggle.h"
#include "random.h"
#include <set>
#include "lexicon.h"
#include "grid.h"
#include "vector.h"

string StandardCubes[16]  = 
{"AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS", "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
 "DISTTY", "EEGHNW", "EEINSU", "EHRTVW", "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"};
 
string BigBoggleCubes[25]  = 
{"AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM", "AEEGMU", "AEGMNN", "AFIRSY", 
"BJKQXZ", "CCNSTW", "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT", "DHHLOR", 
"DHLNOR", "EIIITT", "EMOTTT", "ENSSSU", "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"};

void GiveInstructions()
{
    cout << endl << "The boggle board is a grid onto which I will randomly distribute " 
	 << "cubes. These 6-sided cubes have letters rather than numbers on the faces, " 
	 << "creating a grid of letters on which you try to form words. You go first, " 
	 << "entering all the words you can find that are formed by tracing adjoining " 
	 << "letters. Two letters adjoin if they are next to each other horizontally, " 
	 << "vertically, or diagonally. A letter can only be used once in the word. Words "
	 << "must be at least 4 letters long and can only be counted once. You score points "
	 << "based on word length: a 4-letter word is worth 1 point, 5-letters earn 2 "
	 << "points, and so on. After your puny brain is exhausted, I, the super computer, "
	 << "will find all the remaining words and double or triple your paltry score." << endl;
	
    cout << "\nHit return when you're ready...";
    GetLine();
}

static void Welcome()
{
    cout << "Welcome!  You're about to play an intense game of mind-numbing Boggle. " 
	 << "The good news is that you might improve your vocabulary a bit.  The "
	 << "bad news is that you're probably going to lose miserably to this little "
	 << "dictionary-toting hunk of silicon.  If only YOU had a gig of RAM..." << endl << endl;
}

string GenerateBoard(string cubes[16]);

string GetWord(set<string> &human,Lexicon &lex);

void HumanTurn(string word,Grid<char> &boggle,set<string> &human);

bool IfExists(string remain,Grid<char> &boggle,Vector<int> &path);

bool FitHere(Vector<int> &path,int i,int j,char tar,Grid<char> &boggle);

void ComputerTurn(Grid<char> &boggle,set<string> &human,set<string> &computer,Lexicon &lex);

void BeatHuman(string sofar,Grid<char> &boggle,Vector<int> path,set<string> &human,set<string> &computer,Lexicon &lex);

bool FitThere(Vector<int> &path,int i,int j);

int main()
{
	string board;
	Grid<char> boggle(4,4);
	string word;
	set<string> HumanList;
	set<string> ComputerList;
	Lexicon lex("lexicon.dat");

	InitGraphics();
	Randomize();
	SetWindowSize(9, 5);
	Welcome();
	GiveInstructions();
	DrawBoard(4,4);

	

	cout << "Custom board ---------- 0" << endl;
	cout << "Auto board   ---------- 1" << endl;

	int mode = GetInteger();
	if (mode == 0){
		cout << "Enter your board" << endl;
		board = GetLine();
		while(board.length() < 16){
			cout << "Please make sure your string is at least 16" << endl;
			board = GetLine();
		}
	}
	else 
		board = GenerateBoard(StandardCubes);
	
	for (int i = 0;i < 4;i++)
		for (int j = 0;j < 4;j++){
			LabelCube(i,j,board[i * 4 + j]);
			boggle.setAt(i,j,board[i * 4 + j]);
		}

	while (word != ""){
		cout << "Input here:";
		word = GetWord(HumanList,lex);
		cout << word << endl;
		HumanTurn(word,boggle,HumanList);
	}

	cout << "Now let's see how CPU kicks your ass"<< endl;

	ComputerTurn(boggle,HumanList,ComputerList,lex);

	// cout << "Press Enter to play again" << endl;

	// GetLine();

	return 0;
}

string GenerateBoard(string cubes[16]){
	
	set<int> s;
	int index,temp;
	string result;

	for (int i = 0;i < 16;i++){
		index = RandomInteger(0,17);
		while(s.count(index) != 0){
			index = RandomInteger(0,17);
		}
		s.insert(index);
		temp = RandomInteger(0,6);
		result += cubes[index][temp];
	}
	return result;
}

string GetWord(set<string> &human,Lexicon &lex){
	string input;
	while(1){
		input = GetLine();
		input = ConvertToUpperCase(input);

		if (input == "")
			return input;
		if (input.length() < 4)
			cout << "Length at least 4" << endl;
		else{ 
			if (!lex.containsWord(input))
				cout << "No such a word" << endl;
			else{
				if (human.count(input) != 0)
					cout << "You have already got this word" << endl;
				else
					return input;
				}
			}
	}
}

void HumanTurn(string word,Grid<char> &boggle,set<string> &human){
	// Grid<bool> hazard(4,4);
	Vector<int> path; 
	bool state = false;

	// for (int i = 0;i < 4;i++)
	// 	for (int j = 0;j < 4;j++)
	// 		hazard.setAt(i,j,false);
	state = IfExists(word,boggle,path);

	if (state == false)
		cout <<"No such a word from board" << endl;
	else {
		if (word == "")
			return;
		human.insert(word);
		RecordWordForPlayer(word,Human);
		UpdateDisplay();
		for (int i = 0;i < path.size();i += 2)
			HighlightCube(path[i],path[i+1],true);
		Pause(0.5);
		for (int i = 0;i < path.size();i += 2)
			HighlightCube(path[i],path[i+1],false);

	}
}

bool IfExists(string remain,Grid<char> &boggle,Vector<int> &path){
	if (remain == "")
		return true;
	for (int i = 0;i < 4;i++){
		for (int j = 0;j < 4;j++){
			if (FitHere(path,i,j,remain[0],boggle)){
				path.add(i);
				path.add(j);
				// hazard.setAt(i,j,true);
				string temp = remain;				
				if (IfExists(temp.erase(0,1),boggle,path)) return true;
				path.removeAt(path.size()-1);
				path.removeAt(path.size()-1);
				// hazard.setAt(i,j,false);
			}
		}
	}
	return false;
}

bool FitHere(Vector<int> &path,int i,int j,char tar,Grid<char> &boggle){
	if (tar != boggle.getAt(i,j))
		return false;
	if (path.size() == 0)
		return true;
	for (int c = 0;c < path.size() - 2;c += 2){
		if (i == path[c] and j == path[c + 1])
			return false;
	}
	
	int sum = (i - path[path.size()-2]) * (i - path[path.size()-2]) 
			+ (j - path[path.size()-1]) * (j - path[path.size()-1]);
	if (sum <= 2 and sum != 0)
		return true;
	else return false; 
}

void ComputerTurn(Grid<char> &boggle,set<string> &human,set<string> &computer,Lexicon &lex){
	Vector<int> path;
	Grid<bool> hazard(4,4);

	for (int i = 0;i < 4;i++)
		for (int j = 0;j < 4;j++)
			hazard.setAt(i,j,false);

	BeatHuman("",boggle,path,human,computer,lex);
}

void BeatHuman(string sofar,Grid<char> &boggle,Vector<int> path,set<string> &human,set<string> &computer,Lexicon &lex){
	if(!lex.containsPrefix(sofar))
		return ;
	for (int i = 0;i < 4;i++){
		for (int j = 0;j < 4;j++){
			if (FitThere(path,i,j)){
				string temp;
				temp = sofar + boggle.getAt(i,j);
				path.add(i);
				path.add(j);
				// hazard.setAt(i,j,true);
				if (lex.containsWord(temp) and temp.length() >=4){
					if(human.count(temp) == 0 and computer.count(temp) == 0){
						computer.insert(temp);
						RecordWordForPlayer(temp,Computer);
						UpdateDisplay();
					}
				}
				BeatHuman(temp,boggle,path,human,computer,lex);
				path.removeAt(path.size()-1);
				path.removeAt(path.size()-1);
			}

		}
	}

}

bool FitThere(Vector<int> &path,int i,int j){
	if (path.size() == 0)
		return true;
	for (int c = 0;c < path.size() - 2;c += 2){
		if (i == path[c] and j == path[c + 1])
			return false;
	}
	
	int sum = (i - path[path.size()-2]) * (i - path[path.size()-2]) 
			+ (j - path[path.size()-1]) * (j - path[path.size()-1]);
	if (sum <= 2 and sum != 0)
		return true;
	else return false; 
}