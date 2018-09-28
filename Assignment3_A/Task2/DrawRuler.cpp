#include "graphics.h"
#include "extgraph.h"
#include "genlib.h"

void DrawRuler(double x,double y,double w,double h);
void DrawPart(double x,double y,double w,double h);

int main(){
	InitGraphics();	
	DrawRuler (0.5,0.5,3,0.3);


}

void DrawRuler(double x,double y,double w,double h){
		DrawPart(x,y,w,h);
		if (w<0.05) return;
		double halfH = h/2;
		double halfW = w/2;
		DrawRuler(x,y,halfW,halfH);
		DrawRuler(x + halfW,y,halfW,halfH);
}
void DrawPart(double x,double y,double w,double h){
	MovePen(x,y+h);
	DrawLine(0,(-1)*h);
	DrawLine(w,0);
	DrawLine(0,h);
	UpdateDisplay();
}
