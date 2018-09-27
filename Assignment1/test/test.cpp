#include "genlib.h"
#include <iostream>
#include "random.h"
int main()
{
  int rand;
  Randomize();
  for (int i=0;i<20;i++){
      rand=RandomInteger(0,2);
      cout<<rand<<endl;
  }
  return 0;
}

