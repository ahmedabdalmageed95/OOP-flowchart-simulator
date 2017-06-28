#include "AddConditional.h"



#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>

using namespace std;

//constructor: set the ApplicationManager pointer inside this action
AddConditional::AddConditional(ApplicationManager *pAppManager):Action(pAppManager)
{}

void AddConditional::ReadActionParameters()
{
	pIn = pManager->GetInput();
	pOut = pManager->GetOutput();
	
	pOut->PrintMessage("Conditional Statement: Add the statement text");
	str=pIn->GetString(pOut);
	pOut->PrintMessage("Click where you want to add the statement");
	pIn->GetPointClicked(Position);
	pOut->ClearStatusBar();


}

void AddConditional::Execute()
{
	ReadActionParameters();
		
	
	//Calculating left corner of Conditional statement block
	Point Corner;
	Corner.x = Position.x;
	Corner.y = Position.y;

	Conditional *pAssign = new Conditional(pManager->GetOutput(), Corner);

	bool validate=pAssign->Edit(str);
	while(!validate)
	{
		pOut->PrintMessage("Invalid statement text! Please enter the statement text again");
		str=pIn->GetString(pOut);
		validate=pAssign->Edit(str);
	}

	if(Corner.y<UI.TlBrWdth)
	{
		Corner.y=UI.TlBrWdth+pAssign->getWidth()/2;
		pAssign->Move(Corner);
	}
	if(Corner.y>UI.height-UI.StBrWdth)
	{
		Corner.y=(UI.height-UI.StBrWdth)-pAssign->getWidth()/2;
		pAssign->Move(Corner);
	}

	pManager->AddStatement(pAssign);
}

