#include "StepByStep.h"

#include "../ApplicationManager.h"
#include "../Statements/Conditional.h"

#include <sstream>

using namespace std;

//constructor: set the ApplicationManager pointer inside this action
StepByStep::StepByStep(ApplicationManager *pAppManager):Action(pAppManager)
{}

void StepByStep::ReadActionParameters()
{}

void StepByStep::Execute()
{
	pIn=pManager->GetInput();
	pOut=pManager->GetOutput();

	if(pManager->ValidateFlowchart())
	{
		for(int i=0;i<pManager->GetStatCount();i++)
		{
			if(pManager->GetStatList()[i]->GetType()==START)
			{
				pManager->SetSelectedStatement(pManager->GetStatList()[i]);
				pOut->PrintMessage("Step by step run has started. Press Enter to go to the next step. Press Escape to stop");
				pManager->UpdateInterface();
				break;
			}
		}

		char c;
		c=pIn->GetCharPressed();

		while(pManager->GetSelectedStatement()->GetType()!=END&&c!=1)
		{
			pManager->SetSelectedStatement(pManager->GetSelectedStatement()->Simulate(true));
			pManager->UpdateInterface();
			c=0;
			while(c!=13&&c!=1)
				c=pIn->GetCharPressed();
		}
		if(pManager->GetSelectedStatement()->GetType()==END)
			pManager->SetSelectedStatement(pManager->GetSelectedStatement()->Simulate(true));
		else
		{
			pOut->PrintMessage("The step by step run has been stopped");
			pManager->SetSelectedStatement(NULL);
		}
	}
}