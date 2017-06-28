#include "AddStart.h"



#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>

using namespace std;

//constructor: set the ApplicationManager pointer inside this action
AddStart::AddStart(ApplicationManager *pAppManager):Action(pAppManager)
{}

void AddStart::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	
	pOut->PrintMessage("Start Statement: Click to add the statement");

	pIn->GetPointClicked(Position);
	pOut->ClearStatusBar();		
}

void AddStart::Execute()
{
	ReadActionParameters();
		
	
	//Calculating left corner of Start statement block
	Point Corner;
	Corner.x = Position.x;
	Corner.y = Position.y;

	if(Corner.y<UI.TlBrWdth)
		Corner.y=UI.TlBrWdth;
	if(Corner.y>UI.height-UI.StBrWdth)
		Corner.y=(UI.height-UI.StBrWdth)-58;
	
	Start *pAssign = new Start(pManager->GetOutput(), Corner);

	pManager->AddStatement(pAssign);
}

