#ifndef INPUT_H
#define INPUT_H

#include "..\DEFS.h"
#include "UI_Info.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"

class Output;
class ApplicationManager;
class Input		//The application manager should have a pointer to this class
{
private:
	window *pWind;	//Pointer to the Graphics Window
	ApplicationManager* pManager;	//Pointer to Application Manager
	bool CancelDoubleValue;	//becomes true when the user presses Escape in GetValue
	Point DrawingAreaClick,DraggingPoint;
	//DrawingAreaClick is assigned a value when the user clicks on the drawing area
	//DraggingPoint is used in Move action
public:
	Input(window* pW,ApplicationManager *pAppManager);		//Consturctor
	void GetPointClicked(Point &P) const;//Gets coordinate where user clicks
	char GetCharPressed();

	Point GetDrawingAreaClick() const;

	//The following three functions are used in Move action
	Point GetDraggingPoint();
	bool Dragging();
	void UpdateDraggingPoint();
	//

	double GetValue(Output* pO);	// Reads a double value from the user 

	string GetString(Output* pO) const ; //Returns a string entered by the user

	ActionType GetUserAction(); //Reads the user click and maps it to an action

	void InitializeCancelDoubleValue();	//Reinitializes CancelDoubleValue to false to be used again
	bool GetCancelDoubleValue();

	//The following four functions are used in ApplicationManager::GetStatement
	//They return the statement dimensions from the statement text
	void GetAssignDimensions(string text, int &width, int &height);
	void GetConditionalDimensions(string text, int &diagonallength);
	void GetIODimensions(string text, int &width, int &height);
	void GetStartEndDimensions(string text, int &width, int &height);
	//

	~Input();
};

#endif