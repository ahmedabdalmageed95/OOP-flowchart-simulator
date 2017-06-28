#include "Input.h"
#include "Output.h"
#include "..\ApplicationManager.h"


Input::Input(window* pW,ApplicationManager *pAppManager)
{
	InitializeCancelDoubleValue();
	pWind = pW; //point to the passed window
	pManager=pAppManager;
}

void Input::GetPointClicked(Point &P) const
{
	pWind->FlushMouseQueue();
	pWind->WaitMouseClick(P.x, P.y);	//Wait for mouse click
}

Point Input::GetDrawingAreaClick() const
{return DrawingAreaClick;}

Point Input::GetDraggingPoint()
{return DraggingPoint;}

char Input::GetCharPressed() //Waits for a keyboard press from the user
{
	pWind->FlushKeyQueue();
	char c;
	pWind->WaitKeyPress(c);
	return c;
}

bool Input::Dragging() //Returns true as long as the left mouse button is held down, otherwise it returns false
{
	Point P;
	if(pWind->GetButtonState(LEFT_BUTTON,P.x,P.y)==BUTTON_DOWN)
		return true;
	else
		return false;
}

void Input::UpdateDraggingPoint() //Makes DraggingPoint equal to the current mouse location
{
	pWind->GetButtonState(LEFT_BUTTON,DraggingPoint.x,DraggingPoint.y);
}

string Input::GetString(Output *pO) const //Gets a string from the user
{
	pWind->FlushKeyQueue();
	string Str;
	char Key;
	while(1)
	{
		pWind->WaitKeyPress(Key);
		if(Key == 27 )	//ESCAPE key is pressed
		{
			pWind->FlushMouseQueue();
			return "";	//returns nothing as user has cancelled label
		}
		if(Key == 13 )	//ENTER key is pressed
		{
			pWind->FlushMouseQueue();
			return Str;
		}
		if(Key == 8 )	//BackSpace is pressed
		{
			if(Str.size()!=0)
				Str.resize(Str.size() -1 );
		}
		else
			Str += Key;
		pO->PrintMessage(Str);
	}
}


double Input::GetValue(Output* pO)	// Reads a double value from the user 
{
	pWind->FlushKeyQueue();
	double D = 0;
	bool negativesign=false,decimalpoint=false;
	string Str;
	char Key;
	while(1)
	{
		pWind->WaitKeyPress(Key);
		if(Key == 27 )	//ESCAPE key is pressed
		{
			CancelDoubleValue=true;
			pWind->FlushMouseQueue();
			return D;
		}
		if(Key == 13 )	//ENTER key is pressed
		{
			if(Str=="")
				CancelDoubleValue=true;
			else
				D=stod(Str);
			pWind->FlushMouseQueue();
			return D;
		}
		if(Key == 8 )	//BackSpace is pressed
		{
			if(Str.size()!=0)
			{
				Str.resize(Str.size() -1 );
				pO->PrintMessage(Str);
				negativesign=false; decimalpoint=false;
				for(int i=0;i<abs((int) Str.size());i++)
				{
					if(Str[i]==45)
					{
						negativesign=true;
					}
					if(Str[i]==46)
					{
						decimalpoint=true;
					}
					if(negativesign==true&&decimalpoint==true)
						break;
				}
			}
		}
		if(Key>=48&&Key<=57||Key==45&&negativesign==false&&Str.size()==0||Key==46&&decimalpoint==false)
		{
			Str+=Key;
			pO->PrintMessage(Str);
			if(Key==45)
				negativesign=true;
			else if(Key==46)
				decimalpoint=true;
		}
	}
}

void Input::InitializeCancelDoubleValue()
{
	CancelDoubleValue=false;
}

bool Input::GetCancelDoubleValue()
{
	return CancelDoubleValue;
}

ActionType Input::GetUserAction()
{
	pWind->FlushMouseQueue();
	Point P;
	int x,y;
	while(pWind->GetButtonState(LEFT_BUTTON,x,y)==BUTTON_UP) //This loop is broken when the left mouse button is clicked
	{}
	P.x=x;
	P.y=y;
	for(int i=0;i<pManager->GetStatCount();i++)
	{
		if(pManager->GetStatList()[i]==pManager->GetStatement(P)&&pManager->GetStatList()[i]->IsSelected())
		{
			return MOVE; //MOVE is returned when the left mouse button is held down on a selected statement
		}
	}
	pWind->WaitMouseClick(x, y); //If MOVE is not returned the click is saved in the mouse buffer and assigned to x and y as usual
	if(UI.AppMode == DESIGN ) //design mode
	{
		if ( y >= 0 && y < UI.TlBrWdth)
		{
			int ClickedItem = (x / UI.MnItWdth);
			if(y<0.5*UI.TlBrWdth)
			{
				switch (ClickedItem)
				{
				case 0: return EXIT;
				case 1: return SAVE;
				case 2: return LOAD;
				case 3: return UNDO;
				case 4: return ADD_SMPL_ASSIGN;
				case 5: return ADD_VAR_ASSIGN;
				case 6: return ADD_OP_ASSIGN;
				case 7: return ADD_CONDITION;
				case 8: return ADD_READ;
				case 9: return ADD_WRITE;
				case 10: return ADD_START;
				case 11: return ADD_END;
				case 12: return ADD_CONNECTOR;
				case 13: return MULTIPLE_SELECTION;
				case 14: return EDIT_STAT;
				default: return DSN_TOOL;
				}
			}
			else
			{
				switch (ClickedItem)
				{
				case 0: return COMMENT;
				case 1: return COPY;
				case 2: return CUT;
				case 3: return PASTE;
				case 4: return DEL;
				case 5: return SIM_MODE;
				default: return DSN_TOOL;
				}
			}

		}
		if ( y >= UI.TlBrWdth && y < UI.height - UI.StBrWdth)
		{
			DrawingAreaClick.x=x;
			DrawingAreaClick.y=y;
			return DRAW_AREA; //DRAW_AREA is for both Select and Unselect actions
		}
		return STATUS;
	}
	else //simulation mode
	{
		int ClickedItem = (x / UI.MnItWdth);
		if ( y >= 0 && y < UI.TlBrWdth)
		{
			switch (ClickedItem)
			{
			case 0: return EXIT;
			case 1: return VALIDATE;
			case 2: return RUN;
			case 3: return STP;
			case 4: return GENERATE;
			case 5: return DSN_MODE;
			default: return SIM_TOOL;
			}
		}
		if ( y >= UI.TlBrWdth && y < UI.height - UI.StBrWdth)
		{
			DrawingAreaClick.x=x;
			DrawingAreaClick.y=y;
			return DRAW_AREA;
		}
		return STATUS;
	}
}

void Input::GetAssignDimensions(string text, int &width, int &height)
{
	pWind->GetStringSize(width,height,text);
	width+=20;
	height+=20;
}

void Input::GetConditionalDimensions(string text, int &diagonallength)
{
	int height;
	pWind->GetStringSize(diagonallength,height,text);
	diagonallength+=40;
}

void Input::GetIODimensions(string text, int &width, int &height)
{
	pWind->GetStringSize(width,height,text);
	height+=20;
	width+=(int) round(height/tan(3.1415/3));
}

void Input::GetStartEndDimensions(string type, int &width, int &height)
{
	pWind->GetStringSize(width,height,type);
	width+=80;
	height+=40;
}

Input::~Input()
{
}
