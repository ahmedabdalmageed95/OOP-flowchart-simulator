#include "Edit.h"

#include "../ApplicationManager.h"
#include "../Statements/Conditional.h"

#include <sstream>

using namespace std;

//constructor: set the ApplicationManager pointer inside this action
Edit::Edit(ApplicationManager *pAppManager):Action(pAppManager)
{}

void Edit::ReadActionParameters()
{
	pIn=pManager->GetInput();
	Position=pIn->GetDrawingAreaClick();
	pOut=pManager->GetOutput();
	pOut->PrintMessage("Select the statement or the connector you want to edit");
	pIn->GetPointClicked(Position);
}

void Edit::Execute()
{
	ReadActionParameters();
	for(int i=0;i<pManager->GetStatCount();i++)
	{
		if(pManager->GetStatList()[i]==pManager->GetStatement(Position))	//If a statement is selected
		{
			pOut->PrintMessage("Add the statement text");
			bool validate=pManager->GetStatList()[i]->Edit(pIn->GetString(pOut));
			while(!validate)
			{
				pOut->PrintMessage("Invalid statement text! Please enter the statement text again");
				validate=pManager->GetStatList()[i]->Edit(pIn->GetString(pOut));
			}
			pOut->ClearStatusBar();
			break;
		}
	}
	for(int i=0;i<pManager->GetConnCount();i++)
	{
		if(pManager->GetConnList()[i]==pManager->GetConnector(Position))	//If a connector is selected
		{
			Point Position1,Position2;
			pOut->PrintMessage("Select the new source statement");
			pIn->GetPointClicked(Position1);
			Statement* SrcStat=pManager->GetStatement(Position1);
			while(SrcStat==NULL)
			{
				pOut->PrintMessage("No statement has been selected. Please select the new source statement");
				pIn->GetPointClicked(Position1);
				SrcStat=pManager->GetStatement(Position1);
			}
			pOut->PrintMessage("Select the new destination statement");
			pIn->GetPointClicked(Position2);
			Statement* DstStat=pManager->GetStatement(Position2);
			while(DstStat==NULL||DstStat==SrcStat)
			{
				pOut->PrintMessage("No statement has been selected. Please select the new destination statement");
				pIn->GetPointClicked(Position2);
				DstStat=pManager->GetStatement(Position2);
			}
			char cond;
			if(SrcStat->GetType()==COND)
			{
				pOut->PrintMessage("Which conditional outlet do you want? Press \"y\" for yes and \"n\" for no");
				cond=pIn->GetCharPressed();
				while(cond!='y'&&cond!='n')
					cond=pIn->GetCharPressed();
			}
			if(pManager->GetConnList()[i]->getSrcStat()->GetType()==COND)
			{
				if(*pManager->GetConnList()[i]->getCondValue()==true)
					((Conditional*)pManager->GetConnList()[i]->getSrcStat())->makepYesConnNull();
				else
					((Conditional*)pManager->GetConnList()[i]->getSrcStat())->makepNoConnNull();
			}
			else
				pManager->GetConnList()[i]->getSrcStat()->setpConn(NULL);
			pManager->GetConnList()[i]->setSrcStat(SrcStat);
			pManager->GetConnList()[i]->setDstStat(DstStat);
			if(SrcStat->GetType()==COND)
			{
				if(cond=='n')
				{
					pManager->GetConnList()[i]->setCondValue(false);
				}
				else
				{
					pManager->GetConnList()[i]->setCondValue(true);
				}
			}
			pManager->GetConnList()[i]->getSrcStat()->setpConn(pManager->GetConnList()[i]);
			break;
		}
	}
	pOut->ClearStatusBar();
}