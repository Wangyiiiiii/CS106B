#include "genlib.h"
#include "stack.h"
#include "queue.h"
#include "random.h"
#include  "maze.h"
#include "graphics.h"
#include "extgraph.h"
#include "grid.h"
#include "set.h"
#include <iostream>
#include "simpio.h"

int main(){
	InitGraphics();
	Randomize();
	int randx,randy,randneighbor;
	pointT cur,neighbor;
	cur.col=3;
	cur.row=4;
	int countgrid=100;
	
      	Maze m(10,10,true);
      	m.draw();
             	Grid<bool> g(10,10);
             	for (int i=0;i<10;i++)
             		for (int j=0;j<10;j++)
             			g.setAt(i,j,false);


      	randx=RandomInteger(0,10);
                randy=RandomInteger(0,10);
                cur.col=randx;
                cur.row=randy;
                g.setAt(randx,randy,true);
                countgrid--;

                while(countgrid!=0){
lp:           randneighbor=RandomInteger(0,4);
                switch (randneighbor){
                	case 0: 
                	if (cur.row+1>9) 
                		goto lp;
                	neighbor.col=cur.col;
                	neighbor.row= cur.row+1;
                	break;
                	case 1: 
                	if (cur.col+1>9) 
                		goto lp;
                	neighbor.col=cur.col+1;
                	neighbor.row= cur.row;
                	break;
                	case 2: 
                	if (cur.row-1<0) 
                		goto lp;
                	neighbor.col=cur.col;
                	neighbor.row= cur.row-1;
                	break;
                	case 3: 
                	if (cur.col-1<0) 
                		goto lp;
                	neighbor.col=cur.col-1;
                	neighbor.row= cur.row;
                	break;
                }
                if  (g.getAt(neighbor.col,neighbor.row)==false){
                	m.setWall(cur,neighbor,false);
                	g.setAt(neighbor.col,neighbor.row,true);
                	countgrid--;
                }
                cur = neighbor;}


             	pointT start,end,temppoint,tempneighbor;
             	start.col=0;
             	start.row=0;
             	end.col=9;
             	end.row=9;
             	temppoint.col=0;
             	temppoint.row=0;
                Queue<Stack<pointT> > search;
                Queue<pointT> loop;
                Stack<pointT> temp,tempcopy;
                loop.enqueue(temppoint);
                cout<<"83loop has "<<loop.size()<<"items"<<endl;

                //cout<<"Enter start and end position";
                // start.col=GetInteger();
                // start.row=GetInteger();
                // end.col=GetInteger();
                // end.row=GetInteger();

                temp.push(start);
          	search.enqueue(temp);
          	cout<<"93search has "<<search.size()<<"items"<<endl;

          	while(true){
          	temp=search.dequeue();cout<<"97search has "<<search.size()<<"items"<<endl;
          	if (temp.peek().col==end.col and temp.peek().row==end.row)
          		break;
          	else {
          		temppoint=loop.dequeue();
          		cout<<"101loop has "<<loop.size()<<"items"<<endl;
          		bool wall=true;

          		tempneighbor.col=temp.peek().col+1;
          		tempneighbor.row=temp.peek().row;
          		
          		if  (temp.peek().col+1<10){
          			wall=m.isWall(temp.peek(),tempneighbor);
          			if  ((!wall) and (tempneighbor.col !=temppoint.col  or tempneighbor.row!=temppoint.row )) {
          			tempcopy=temp;
          			tempcopy.push(tempneighbor);
          			search.enqueue(tempcopy);cout<<"113search has "<<search.size()<<"items"<<endl;
          			loop.enqueue(temp.peek());
          			cout<<"114loop has "<<loop.size()<<"items"<<endl;
          		}}

          		tempneighbor.col=temp.peek().col;
          		tempneighbor.row=temp.peek().row+1;
          		if  (temp.peek().row+1<10){
          			wall=m.isWall(temp.peek(),tempneighbor);
          			if  ((!wall) and (tempneighbor.col !=temppoint.col  or tempneighbor.row!=temppoint.row )) {
          			tempcopy=temp;
          			tempcopy.push(tempneighbor);
          			search.enqueue(tempcopy);cout<<"125search has "<<search.size()<<"items"<<endl;
          			loop.enqueue(temp.peek());
          			cout<<"126loop has "<<loop.size()<<"items"<<endl;
          		}}

          		tempneighbor.col=temp.peek().col-1;
          		tempneighbor.row=temp.peek().row;
          		if  (temp.peek().col-1>=0){
          			wall=m.isWall(temp.peek(),tempneighbor);
          			if  ((!wall) and (tempneighbor.col !=temppoint.col  or tempneighbor.row!=temppoint.row )) {
          			tempcopy=temp;
          			tempcopy.push(tempneighbor);
          			search.enqueue(tempcopy);cout<<"137search has "<<search.size()<<"items"<<endl;
          			loop.enqueue(temp.peek());
          			cout<<"138loop has "<<loop.size()<<"items"<<endl;
          		}}

          		tempneighbor.col=temp.peek().col;
          		tempneighbor.row=temp.peek().row-1;
          		if  (temp.peek().row-1>=0){
          			wall=m.isWall(temp.peek(),tempneighbor);
          			if  ((!wall) and (tempneighbor.col !=temppoint.col  or tempneighbor.row!=temppoint.row )) {
          			tempcopy=temp;
          			tempcopy.push(tempneighbor);
          			search.enqueue(tempcopy);cout<<"149search has "<<search.size()<<"items"<<endl;
          			loop.enqueue(temp.peek());
          			cout<<"150loop has "<<loop.size()<<"items"<<endl;
          		}}

          	}}

          	while(!temp.isEmpty()){
          		temppoint=temp.pop();
          		m.drawMark(temppoint,"Red");
          	}


                return 0;
}