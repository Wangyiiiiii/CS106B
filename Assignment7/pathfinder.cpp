/* pathfinder.cpp
 * ---------------
 * A starter file with some starting constants and handy utility routines.
 */
 
#include "genlib.h"
#include "extgraph.h"
#include <iostream>
#include <cmath>
#include "pqueue.h"
#include "structused.h"
#include <map>
#include <fstream>
#include "simpio.h"
#include "set.h"
/* Constants
 * --------
 * A few program-wide constants concerning the graphical display.
 */
const double CircleRadius =.05;     	// the radius of a node
const int LabelFontSize = 9;          // for node name labels


/* Type: coordT
 * ------------
 * Just a simple struct to handle a pair of x,y coordinate values.
 */



/* Function: DrawFilledCircleWithLabel
 * Usage:  DrawFilledCircleWithLabel(center, "Green", "You are here");
 * -------------------------------------------------------------------
 * Uses facilities from extgraph to draw a circle filled with
 * color specified. The circle is centered at the given coord has the
 * specified radius.  A label is drawn to the right of the circle.
 * You can leave off the last argument if no label is desired.
 */
void DrawFilledCircleWithLabel(coordT center, string color, string label = "")
{
	MovePen(center.x + CircleRadius, center.y);
	SetPenColor(color);
	StartFilledRegion(1.0);
	DrawArc(CircleRadius, 0, 360);
	EndFilledRegion();
	if (!label.empty()) {
		MovePen(center.x + CircleRadius, center.y);
		SetFont("Helvetica");
		SetPointSize(LabelFontSize);
		DrawTextString(label);
	}
}

/* Function: DrawLineBetween
 * Usage:  DrawLineBetween(coord1, coord2, "Black");
 * -------------------------------------------------
 * Uses facilities from extgraph to draw a line of the
 * specified color between the two given coordinates.
 */
void DrawLineBetween(coordT start, coordT end, string color)
{
	SetPenColor(color);
	MovePen(start.x, start.y);
	DrawLine(end.x - start.x, end.y - start.y);
}

int computeDistance(node a,node b){
	node tempNode;
	for (int i = 0;i < a.outgoing.size();i++){
		tempNode = ((*(a.outgoing[i]->end1)).name == a.name) ? (*(a.outgoing[i]->end2)) : (*(a.outgoing[i]->end1));
		if (tempNode.name == b.name)
			return a.outgoing[i]->length;
	}

}

/* Function: GetMouseClick
 * Usage:  loc = GetMouseClick();
 * ------------------------------
 * Waits for the user to click somewhere on the graphics window
 * and returns the coordinate of where the click took place.
 */
coordT GetMouseClick()
{
	coordT where;
	WaitForMouseDown();
	WaitForMouseUp();
	where.x = GetMouseX();
	where.y = GetMouseY();
	return where;
}

/* Function: WithinDistance
 * Usage:  if (WithinDistance(click, pt))...
 * -----------------------------------------
 * Returns true if the Cartesian distance between the two coordinates
 * is <= the specified distance, false otherwise. If not specified,
 * the distance is assumed to be size of the node diameter on screen.
 */
bool WithinDistance(coordT pt1, coordT pt2, double maxDistance = CircleRadius*2)
{
	double dx = pt2.x - pt1.x;
	double dy = pt2.y - pt1.y;
	double distance = sqrt(dx*dx + dy*dy);
	return (distance <= maxDistance);
}

int cmp(path p1,path p2)
{
	int count1 = 0;
	int count2 = 0;

	if (p1.area.size() == 1)
		count1 = 0;
	else{
		for(int i = 0;i < p1.area.size() - 1;i++)
			count1 += computeDistance(p1.area.pop(),p1.area.peek());
	}

	if (p2.area.size() == 1)
		count2 = 0;
	else{
		for(int i = 0;i < p2.area.size() - 1;i++)
			count2 += computeDistance(p2.area.pop(),p2.area.peek());
	}

	if (count1 < count2)
		return 1;
	if (count1 == count2)
		return 0;
	else
		return -1;
}

int cmpfn(arc a1,arc a2){
	if (a1.length > a2.length)
		return -1;
	if (a1.length < a2.length)
		return 1;
	else return 0;
} 

void DijkstraIt(node startPoint,node endPoint)
{
	PQueue<path> pq(cmp);
	path temp;
	path basis;
	node tempNode;
	node basisNode;
	int size;

	temp.area.push(startPoint);
	temp.walked.insert(startPoint.name);
	pq.enqueue(temp);

	while(1){
		temp = pq.dequeueMax();
		// cout << "dequeue completed" << endl;
		tempNode = temp.area.peek();
		if (tempNode.name == endPoint.name)
			break;
		basis = temp;
		basisNode = tempNode;
		for (int i = 0;i < basisNode.outgoing.size();i++){
			temp = basis;
			tempNode = ((*(basisNode.outgoing[i]->end1)).name == basisNode.name) ? (*(basisNode.outgoing[i]->end2)) : (*(basisNode.outgoing[i]->end1));
			if (basis.walked.count(tempNode.name) == 0){
				temp.area.push(tempNode);
				temp.walked.insert(tempNode.name);
				pq.enqueue(temp);
				// cout << "enqueue " << tempNode.name << endl;
			}
		}
	}

	size = temp.area.size();

	// cout << size << endl;
	for (int i = 0;i < size -1 ;i++){
		tempNode = temp.area.pop();
		DrawLineBetween(tempNode.loc,(temp.area.peek()).loc,"red");
		UpdateDisplay();
	}
}

void KruskalIt(map<string,node> &Nodes,Vector<arc> &Arcs)
{
	// int size;
	Vector<Set<string> > wholePicture;
	arc tempArc;

	PQueue<arc> pq(cmpfn);
	for (int i = 0;i < Arcs.size();i++)
		pq.enqueue(Arcs[i]);
	// size = pq.size();
	// for (int i = 0;i < size;i++)
	// 	cout << pq.dequeueMax().length << endl;
	for (map<string,node>::iterator it = Nodes.begin();it != Nodes.end();++it){
		Set<string> temp;
		temp.add(it->first);
		wholePicture.add(temp);
	}
	// for (int i = 0;i < wholePicture.size();i++)
	// 	cout << wholePicture[i].size() << endl;
	while(wholePicture.size() != 1){
		tempArc = pq.dequeueMax();
		int set1,set2;
		string node1,node2;
		node1 = tempArc.end1->name;
		node2 = tempArc.end2->name;
		for (int i = 0;i < wholePicture.size();i++){
			if (wholePicture[i].contains(node1))
				set1 = i;
			if (wholePicture[i].contains(node2))
				set2 = i;
		}
		if (set1 != set2){
			wholePicture[set1].unionWith(wholePicture[set2]);
			wholePicture.removeAt(set2);
			DrawLineBetween((*(tempArc.end1)).loc,(*(tempArc.end2)).loc,"red");
			UpdateDisplay();
		}
	}
}

int main()
{
	InitGraphics();
	SetWindowSize(6.5, 4);
	SetWindowTitle("CS106 Pathfinder");
    cout << "This masterful piece of work is a graph extravaganza!" << endl
        << "The main attractions include a lovely visual presentation of the graph" << endl
        << "along with an implementation of Dijkstra's shortest path algorithm and" << endl
        << "the computation of a minimal spanning tree.  Enjoy!" << endl;
    
    map<string,node> Nodes;
    Vector<arc> Arcs;
    ifstream in;
    string filename,arcNameTemp;
    string graphname;
    node readtemp,startPoint,endPoint;
    arc arctemp;
    coordT click;
    bool flag = false;

lp: cout<<"Enter the name of file:";
    filename = GetLine();
  

   	in.open(filename.c_str());
   	if (in.fail()){
   	in.clear();
   	cout << "Could not open file" << endl;
   	goto lp;}
   	cout << filename << endl;

	in >> graphname;
	in >> filename; //just for skipping the "NODES"
	in >> readtemp.name;

	while(readtemp.name != "ARCS"){
			in >> readtemp.loc.x;
			in >> readtemp.loc.y;
			Nodes.insert(pair<string,node>(readtemp.name,readtemp));
			in >> readtemp.name;
	}
	while(1){
			in >> arcNameTemp;
			if (in.fail())
				break;
			arctemp.end1 = & Nodes[arcNameTemp];
			in >> arcNameTemp;
			arctemp.end2 = & Nodes[arcNameTemp];
			in >> arctemp.length;
			Arcs.add(arctemp);
	}

	for (int i = 0;i < Arcs.size();i++){
		Nodes[(*(Arcs[i].end1)).name].outgoing.add(&(Arcs[i]));
		Nodes[(*(Arcs[i].end2)).name].outgoing.add(&(Arcs[i]));
	}

	// cout << "---------------NODES---------------" << endl;
	// for (map<string,node>::iterator it = Nodes.begin();it != Nodes.end();++it){
	// 	cout << it->second.name << "   " << it->second.loc.x << " " << it->second.loc.y << endl;
	// 	for (int i = 0;i < it->second.outgoing.size();i++)
	// 		cout << "Paths:" << (*(it->second.outgoing[i])).length << " ";
	// 	cout << endl;
	// }
	// cout << "---------------ARCS----------------" << endl;
	// for (int i = 0;i < Arcs.size();i++)
	// 	cout << (*(Arcs[i].end1)).name << "  " << (*(Arcs[i].end2)).name << "  " << Arcs[i].length << endl;

	DrawNamedPicture(graphname);
	for (map<string,node>::iterator it = Nodes.begin();it != Nodes.end();++it)
		DrawFilledCircleWithLabel(it->second.loc,"blue",it->first);
	for (int i = 0;i < Arcs.size();i++)
		DrawLineBetween((*(Arcs[i].end1)).loc,(*(Arcs[i].end2)).loc,"blue");
	
	cout << "choose start and end point plz" << endl;

	flag = false;
	click = GetMouseClick();
	cout << "Start: ";
	for (map<string,node>::iterator it = Nodes.begin();it != Nodes.end();++it){
		if (WithinDistance(click,it->second.loc)){
			flag = true;
			cout << it->first << endl;
			startPoint = it->second;
			break;
		}
 	}
 	if (flag == false)
 		cout << "Blank Area!!" << endl;

 	flag = false;
	click = GetMouseClick();
	cout << "End: ";
	for (map<string,node>::iterator it = Nodes.begin();it != Nodes.end();++it){
		if (WithinDistance(click,it->second.loc)){
			flag = true;
			cout << it->first << endl;
			endPoint = it->second;
			break;
		}
 	}
 	if (flag == false)
 		cout << "Blank Area!!" << endl;
 	DijkstraIt(startPoint,endPoint);
 	
 	// KruskalIt(Nodes,Arcs);

    return (0);
}