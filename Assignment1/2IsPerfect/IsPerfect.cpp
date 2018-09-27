/*
 * Program: IsPerfect.cpp
 * --------------------
 * To find the perfect numbers from 1 to 10000
 *
 * wangyi 2017.10.12
 */

#include <iostream>
#include "genlib.h"

bool perfect(int n);
int main()
{
   bool cdt;
   for (int i=1;i<10001;i++){
       cdt=perfect(i);
       if (cdt==true)
         cout<<i<<endl;
       
   
  }
   return 0;   

}
bool perfect(int n)
{
     if (n==1)
       return false;
     else {
       int sum=0;
       for (int i=1;i<n;i++){
          if (n%i==0)
            sum+=i;
         }
       if (sum==n)
         return true ;
       else
         return false; 
     } 

}
