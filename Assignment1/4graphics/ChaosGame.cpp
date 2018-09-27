#include "extgraph.h"
#include "genlib.h"
#include <iostream>
#include <string>
#include "random.h"
int main()
{  
   double cod[3][2]={0,0,0,0,0,0};
   double codtemp[2]={0,0} ;  
   int rand;
   Randomize(); 

   SetCoordinateSystem("cartesian");
   InitGraphics();
   string str="Click three different places";
   DrawTextString(str);
  
   WaitForMouseDown();
   cod[0][0]=GetMouseX();
   cod[0][1]=GetMouseY();
   WaitForMouseUp();
   MovePen(cod[0][0],cod[0][1]);
   
   WaitForMouseDown();
   cod[1][0]=GetMouseX();
   cod[1][1]=GetMouseY();
   WaitForMouseUp();

   DrawLine(cod[1][0]-cod[0][0],cod[1][1]-cod[0][1]);
   UpdateDisplay();
   

   WaitForMouseDown();
   cod[2][0]=GetMouseX();
   cod[2][1]=GetMouseY();
   WaitForMouseUp();

   DrawLine(cod[2][0]-cod[1][0],cod[2][1]-cod[1][1]);
   UpdateDisplay();

   DrawLine(cod[0][0]-cod[2][0],cod[0][1]-cod[2][1]);
   UpdateDisplay();

   rand=RandomInteger(0,3);
   codtemp[0]=cod[rand][0];
   codtemp[1]=cod[rand][1];
   
   MovePen(cod[rand][0],cod[rand][1]);
   
   DrawArc(1,0,360); 
   
   StartFilledRegion();
   EndFilledRegion();
   UpdateDisplay();
   
   while((!MouseButtonIsDown()))
   {   
       rand=RandomInteger(0,3);
       MovePen(0.5*(cod[rand][0]+codtemp[0]),0.5*(cod[rand][1]+codtemp[1]));
       codtemp[0]=0.5*(cod[rand][0]+codtemp[0]);
       codtemp[1]=0.5*(cod[rand][1]+codtemp[1]);
       StartFilledRegion();
       DrawArc(1,0,360);
       EndFilledRegion();
       UpdateDisplay();
       Pause(0.1);
       
   }

   return 0;
}
