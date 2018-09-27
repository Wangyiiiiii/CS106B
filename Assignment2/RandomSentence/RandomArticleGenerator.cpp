#include "genlib.h"
#include "simpio.h"
#include "map.h"
#include "vector.h"
#include "random.h"
#include <iostream>
#include <fstream> 

void ReadGrammar(ifstream& in,Map<Vector<char> >& m,int n);
void Makeup(Map<Vector<char> >& m,int n);

int main(){
	string filename;
	ifstream in;
	Map<Vector<char> > m;
	int order;

lp: 	cout<<"Enter the name of file:";
   	filename=GetLine();
   	in.open(filename.c_str());
   	if (in.fail()){
   	in.clear();
   	cout<<"Could not open file "<<endl;
   	goto lp;}

   	cout<<"Enter Order:";
   	order=GetInteger();

   	ReadGrammar(in,m,order);
 	Makeup(m,order);

   	return 0;
}

void ReadGrammar(ifstream& in,Map<Vector<char> >& m,int n){
	string index;
	Vector<char> newVec;
	for  (int i=0;i<n;i++){
		char c=in.get();
		index+=c;
	}
		//cout<<index<<endl;
	while(!in.eof()){
		char c=in.get();
		if(m.containsKey(index))
			m[index].add(c);
		else{
			newVec.add(c);
			m.add(index,newVec);
			newVec.removeAt(0);
			}
		index.erase(0,1);
		index+=c;
		//cout<<index<<endl;
	}
}
void Makeup(Map<Vector<char> >& m,int n){
	Map<Vector<char> >::Iterator itr = m.iterator();
	string index;
	int count=0;
	int rand=0;
	Randomize();
	char c='a';
	while (itr.hasNext()){
		string temp;
		temp=itr.next();
		if (m[temp].size()>count){
			count=m[temp].size();index=temp;
		}
	}
	cout<<index;
	while (true){
		if(!m.containsKey(index))
			break;
		else{
			rand=RandomInteger(0,m[index].size());
			c=m[index].getAt(rand);
			cout<<m[index].getAt(rand);
		}
		index.erase(0,1);
		index+=c;
	}

}

