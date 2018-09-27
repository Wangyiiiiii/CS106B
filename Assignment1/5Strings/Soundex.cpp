#include <iostream>
#include "simpio.h"
#include "genlib.h"
#include <string>

string GetSoundexCode(string str);
int main()
{ 
   string str="";
   string Sdcode;
    do
   {
     cout<<"Enter surname(RETURN to quit):";
     str=GetLine();
     if (str=="RETURN") break;
     Sdcode=GetSoundexCode(str);
     cout<<"Soundex code for "<<str<<" is "<<Sdcode<<endl;
     //cout<<"Soundex code for "<<str<<" is 566"<<endl;
   }while(str!="RETURN") ;
   return 0;
}

string GetSoundexCode(string str)
{
    
    for (int i=1;i<str.length();i++)
    {
         switch (str[i]){
        case'A':case'a':case'E':case'e':
        case'i':case'I':case'O':case'o':
        case'U':case'u':case'H':case'h':
        case'W':case'w':case'Y':case'y': str[i]='0';  break;
        case'B':case'b':case'F':case'f':
        case'P':case'p':case'V':case'v': str[i]='1';    break;
        case'C':case'c':case'G':case'g':
        case'J':case'j':case'K':case'k':
        case'Q':case'q':case'S':case's':
        case'X':case'x':case'Z':case'z': str[i]='2';break;
        case'D':case'd':case'T':case't': str[i]='3';break;
	case'M':case'm':case'N':case'n': str[i]='4';break;
	case'L':case'l':                 str[i]='5';break;
	case'R':case'r':                 str[i]='6';break;
        }
     }
     if ((int)str[0]>=97)
        str[0]=   (char)((int)str[0]-32);

lp2:  for (int i=1;i<str.length();i++)
     {
          if (str[i]==str[i+1])
             {str.erase(i,1);
              goto lp2;}
     }
lp1:  for (int i=1;i<str.length();i++)
     {
          if (str[i]=='0')
             {str.erase(i,1);
              goto lp1;}
             
     }
   if (str.length()<4)
      { 
        for (int i=1;i<=(5-str.length());i++)
         str+='0';
      }   
     
   return str;
}
