#include "AddWrite.h"



#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>

using namespace std;

//constructor: set the ApplicationManager pointer inside this action
AddWrite::AddWrite(ApplicationManager *pAppManager):Action(pAppManager)
{}

void AddWrite::ReadActionParameters()
{
	pIn = pManager->GetInput();
	pOut = pManager->GetOutput();
	
	pOut->PrintMessage("Write Statement: Add the statement text");
	str=pIn->GetString(pOut);
	pOut->PrintMessage("Click where you want to add the statement");
	pIn->GetPointClicked(Position);
	pOut->ClearStatusBar();	
}

void AddWrite::Execute()
{
	ReadActionParameters();
		
	
	//Calculating left corner of Write statement block
	Point Corner;
	Corner.x = Position.x;
	Corner.y = Position.y;

	if(Corner.y<UI.TlBrWdth)
		Corner.y=UI.TlBrWdth;
	if(Corner.y>UI.height-UI.StBrWdth)
		Corner.y=(UI.height-UI.StBrWdth)-39;

	Write *pAssign = new Write(pManager->GetOutput(), Corner, str);
	bool validate=pAssign->Edit(str);
	while(!validate)
	{
		pOut->PrintMessage("Invalid statement text! Please enter the statement text again");
		str=pIn->GetString(pOut);
		validate=pAssign->Edit(str);
	}

	pManager->AddStatement(pAssign);
}

