/*
 * Program: VoteSim.cpp
 * --------------------
 * To find the perfect numbers from 1 to 10000
 *
 * wangyi 2017.10.12
 */
#include <iostream>
#include "genlib.h"
#include "random.h"
#include "simpio.h"

double Sim(int num,double spreadper,double errper);

int main()
{ 
    int num;
    double perspd,pererr,failrate;

    cout<<"Enter number of voters:";
    num=GetInteger();
    while (num<=0){
	cout<<"positive only, try again:";
        num=GetInteger(); 
    }

    cout<<"Enter percentage spread between candidates:";
    perspd=GetReal();

    while(perspd<0.0 or perspd>0.5){
    	cout<<"0-0.5 only,try again:";
    	perspd=GetReal();
    }
            
    cout<<"Enter voting error percentage:";
    pererr=GetReal();

   while(pererr<0.0 or pererr>1.0){
    	cout<<"0-1.0 only,try again:";
    	pererr=GetReal();
    }
    
    cout<<num<<" "<<perspd<<" "<<pererr<<endl;
    failrate=Sim(num,perspd,pererr);

    cout<<"chance of an invalid election result after 500 trials =="<<failrate<<endl;
 
    return 0;
}

double Sim(int num,double spreadper,double errper)
{  
   int Sumfail=0;
   for(int i=0;i<500;i++)
   { 
     int SumHilary=0;
     int SumTrump=0; 
     bool vote;   
     for(int m=0;m<num*(0.5-spreadper);m++)
	{
          
           Randomize();
           vote=RandomChance(1-errper);
           if (vote==true)
              SumHilary++;
           else
              SumTrump++;
	}
     for(int n=0;n<num*(0.5+spreadper);n++)
	{
          
           Randomize();
           vote=RandomChance(1-errper);
           if (vote==true)
              SumTrump++;
           else
              SumHilary++;
	}
      if (SumTrump<=SumHilary)
        Sumfail++;
   }
  return Sumfail/500.0;   


}
