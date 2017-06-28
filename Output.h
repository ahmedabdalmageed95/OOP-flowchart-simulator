#ifndef OUPTUT_H
#define OUPTUT_H

#include "Input.h"

class Output	//The application manager should have a pointer to this class
{
private:	
	window* pWind;	//Pointer to the Graphics Window
public:
	Output();	

	void WindowPause(); //Pauses the window for 100ms

	window* CreateWind(int, int, int , int);
	void CreateDesignToolBar();	//Tool bar of the design mode
	void CreateSimulationToolBar();//Tool bar of the simulation mode

	void CreateStatusBar();

	Input* CreateInput(ApplicationManager* pManager); //creates a pointer to the Input object	
	void ClearStatusBar();	//Clears the status bar
	void ClearDrawArea();	//Clears the drawing area

	// -- Statements Drawing Functions
	void DrawAssign(Point Left, string Text, bool Selected=false); //Draws all types of assignment statements
	
	void DrawStartEnd(string type, Point Left, bool Selected=false); //Draws Start and End statements
	void DrawConditional(Point Left, string Text, bool Selected=false);	//Draws conditional statement
	void DrawIO(Point Left, string type, string Text, bool Selected=false);	//Draws read and write statements
	void DrawConnector(Point a, Point b, bool selected=false); //Draws connector

	//The following five functions return the inlets and outlets of the statements from their texts and main points
	void GetAssignPoints(Point left, string text, Point &in, Point &out);
	void GetConditionalPoints(Point left, string text, Point &in, Point &yesOut, Point &noOut);
	void GetIOPoints(Point left, string text, Point &in, Point &out);
	void GetStartPoints(Point left, string text, Point &out);
	void GetEndPoints(Point left, string text, Point &in);
	//

	void PrintMessage(string msg);	//Prints a message on Status bar
	void PrintDouble(double d, string str="", int x=10, int y=UI.height - (int) (UI.StBrWdth/1.5)); //Prints a double value in the location specified
	
	~Output();
};

#endif