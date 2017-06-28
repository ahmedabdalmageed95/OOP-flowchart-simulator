#include "MultipleSelection.h"



#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>



//constructor: set the ApplicationManager pointer inside this action
MultipleSelection::MultipleSelection(ApplicationManager *pAppManager):Action(pAppManager)
{
}

void MultipleSelection::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	
	pOut->PrintMessage("Select the statements you want");
	pIn->GetPointClicked(Position);
	pOut->ClearStatusBar();		
	
}

void MultipleSelection::Execute()
{
	while (1)
	{
		ReadActionParameters();
		for (int i=0;i<pManager->GetStatCount();i++)
		{
			if (pManager->GetStatList()[i]==pManager->GetStatement(Position))
			{
				for (int j=0;j<200;j++)
				{
					if (pManager->GetSelectedStat()[j]==NULL)
					{
						pManager->GetSelectedStat()[j]=pManager->GetStatList()[i];
						pManager->GetSelectedStat()[j]->SetSelected(true);
						break;
					}
				}
				pManager->UpdateInterface();
			}
		}
		if (pManager->GetStatement(Position)==NULL)
			break;
	}
}