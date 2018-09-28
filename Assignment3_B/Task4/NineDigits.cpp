#include <iostream>
#include "simpio.h"
#include "lexicon.h"
#include "genlib.h"
#include <string>
#include "vector.h"

void ListCompletions(string digitSequence, Lexicon & lex);
void FindPerfix(string sofar,string rest,Vector<string> & KeyMap,Vector <string> & prefix);
void FindWord(string target,Lexicon &lex);

int main(){
	Lexicon lex("lexicon.dat");
	string str;

	// char c = '7';
	cout << (char)(97)<< endl;
 	// cout<< lex.containsPrefix("ugly") << endl;

	while(1){
	cout << "Enter digit sequense:";
	str = GetLine();
	ListCompletions(str,lex);
	}
	return 0;
	// cout << lex.size() << endl;

}

void ListCompletions(string digitSequence, Lexicon & lex){
	Vector <string> KeyMap;
	
	KeyMap.add("none");
	KeyMap.add("none");
	KeyMap.add("abc");
	KeyMap.add("def");
	KeyMap.add("ghi");
	KeyMap.add("jkl");
	KeyMap.add("mno");
	KeyMap.add("pqrs");
	KeyMap.add("tuv");
	KeyMap.add("wxyz");

	Vector <string> prefix;
	FindPerfix("",digitSequence,KeyMap,prefix);

	for (int i = 0;i < prefix.size();i++){
		if (!lex.containsPrefix(prefix[i]))
			prefix.removeAt(i);
	}

	for (int i = 0;i < prefix.size();i++){
		FindWord (prefix[i],lex);
	}

}
void FindPerfix(string sofar,string rest,Vector<string> & KeyMap,Vector <string> & prefix){
	int index = (int)rest[0] - 48;
	string temp; 
	if (rest == ""){
		prefix.add(sofar);
		return;
	}
	else{ 	
			for (int i = 0;i < KeyMap[index].length();i++){
				string next = sofar + KeyMap[index][i];
				temp = rest;
				string remain = temp.erase(0,1);
				FindPerfix(next,remain,KeyMap,prefix);
			}
		}	
}
void FindWord(string target,Lexicon &lex){
	if (!lex.containsPrefix(target))
		return;
	else {
		if (lex.containsWord(target))
			cout << target << endl;
		for (int i = 0;i < 26;i++){
			string next = target + (char)(i+97);
			FindWord(next,lex);
		}
	}


}