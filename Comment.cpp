#include "Comment.h"

#include "../ApplicationManager.h"

#include <sstream>

using namespace std;

//constructor: set the ApplicationManager pointer inside this action
Comment::Comment(ApplicationManager *pAppManager):Action(pAppManager)
{}

void Comment::ReadActionParameters()
{
	pIn=pManager->GetInput();
	Position=pIn->GetDrawingAreaClick();
	pOut=pManager->GetOutput();
	pOut->PrintMessage("Select the statement you want to comment on");
	pIn->GetPointClicked(Position);
}

void Comment::Execute()
{
	ReadActionParameters();
	for(int i=0;i<pManager->GetStatCount();i++)
	{
		if(pManager->GetStatList()[i]==pManager->GetStatement(Position))
		{
			pOut->PrintMessage("Enter your comment");
			pManager->GetStatList()[i]->SetComment(pIn->GetString(pOut));
			pOut->ClearStatusBar();
		}
		
	}
}

