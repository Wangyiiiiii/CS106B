#include "genlib.h"
#include <iostream>
#include <string>
#include "simpio.h"
#include <fstream>
#include "vector.h"
int main()
{
   string filename;
   ifstream in;
   Vector<int> myVec;
   int num;

lp:cout<<"Enter the name of file:";
   filename=GetLine();
  

   in.open(filename.c_str());
   if (in.fail()){
   in.clear();
   cout<<"Could not open file "<<endl;
   
   goto lp;}
 
   cout<<filename<<endl;
  
   while(1)
   {
      in>>num;
      if (in.fail()) break;
      myVec.add(num);
   }

   for (int i=0;i<10;i++)
   {   
       int count=0;
       cout<<i<<"0-"<<i<<"9:";
       for (int j=0;j<myVec.size();j++){
          if ((myVec.getAt(j)>=(10*i)) and (myVec.getAt(j)<=(9+10*i)))
          count++;}
       for (int j=0;j<count;j++)
          cout<<'X';
       cout<<endl;
   }
   
   return 0;
}
