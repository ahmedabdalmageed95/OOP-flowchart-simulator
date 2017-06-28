#include "Delete.h"

#include "../ApplicationManager.h"
#include "../Statements/Conditional.h"

#include <sstream>

using namespace std;

//constructor: set the ApplicationManager pointer inside this action
Delete::Delete(ApplicationManager *pAppManager):Action(pAppManager)
{}

void Delete::ReadActionParameters()
{
	if (pManager->MultiplySelected()==false)
	{
		pIn=pManager->GetInput();
		Position=pIn->GetDrawingAreaClick();
		pOut=pManager->GetOutput();
		pOut->PrintMessage("Select the statement or the connector you want to delete");
		pIn->GetPointClicked(Position);
	}
	else
	{
		pIn=pManager->GetInput();
		Position=pIn->GetDrawingAreaClick();
		pOut=pManager->GetOutput();
		pOut->PrintMessage("Deleting");
	}
}

void Delete::Execute()
{
	if (pManager->MultiplySelected()==false)
	{
		ReadActionParameters();
		for(int i=0;i<pManager->GetStatCount();i++)
		{
			if(pManager->GetStatList()[i]==pManager->GetStatement(Position))
			{
				for(int j=0;j<pManager->GetConnCount();j++)
				{
					if(pManager->GetStatList()[i]==pManager->GetConnList()[j]->getSrcStat()||pManager->GetStatList()[i]==pManager->GetConnList()[j]->getDstStat())
					{
						pManager->GetConnList()[j]->getSrcStat()->setpConn(NULL);
						delete pManager->GetConnList()[j];
						pManager->GetConnList()[j]=NULL;
						for(int k=j;k<pManager->GetConnCount()-1;k++)
						{
							pManager->GetConnList()[k]=pManager->GetConnList()[k+1];
							pManager->GetConnList()[k+1]=NULL;
						}
						j--;
						pManager->DecrementConnCount();
					}
				}
				delete pManager->GetStatList()[i];
				pManager->GetStatList()[i]=NULL;
				for(int j=i;j<pManager->GetStatCount()-1;j++)
				{
					pManager->GetStatList()[j]=pManager->GetStatList()[j+1];
					pManager->GetStatList()[j+1]=NULL;
				}
				pManager->DecrementStatCount();
				pOut->ClearStatusBar();
				break;
			}
		}
		for(int i=0;i<pManager->GetConnCount();i++)
		{
			if(pManager->GetConnList()[i]==pManager->GetConnector(Position))
			{
				if(pManager->GetConnList()[i]->getSrcStat()->GetType()==COND)
				{
					if(*pManager->GetConnList()[i]->getCondValue()==true)
						((Conditional*)pManager->GetConnList()[i]->getSrcStat())->makepYesConnNull();
					else
						((Conditional*)pManager->GetConnList()[i]->getSrcStat())->makepNoConnNull();
				}
				else
					pManager->GetConnList()[i]->getSrcStat()->setpConn(NULL);
				delete pManager->GetConnList()[i];
				pManager->GetConnList()[i]=NULL;
				for(int j=i;j<pManager->GetConnCount()-1;j++)
				{
					pManager->GetConnList()[j]=pManager->GetConnList()[j+1];
					pManager->GetConnList()[j+1]=NULL;
				}
				pManager->DecrementConnCount();
				pOut->ClearStatusBar();
				break;
			}
		}
		pOut->ClearStatusBar();
	}
	else
	{
		ReadActionParameters();
		for(int i=0;i< pManager->GetStatCount();i++)
		{
			if(pManager->GetStatList()[i]->IsSelected()==true)
			{
				for(int j=0;j<pManager->GetConnCount();j++)
				{
					if(pManager->GetStatList()[i]==pManager->GetConnList()[j]->getSrcStat()||pManager->GetStatList()[i]==pManager->GetConnList()[j]->getDstStat())
					{
						pManager->GetConnList()[j]->getSrcStat()->setpConn(NULL);
						delete pManager->GetConnList()[j];
						pManager->GetConnList()[j]=NULL;
						for(int k=j;k<pManager->GetConnCount()-1;k++)
						{
							pManager->GetConnList()[k]=pManager->GetConnList()[k+1];
							pManager->GetConnList()[k+1]=NULL;
						}
						j--;
						pManager->DecrementConnCount();
					}
				}
				delete pManager->GetStatList()[i];
				pManager->GetStatList()[i]=NULL;
				for(int j=i;j<pManager->GetStatCount()-1;j++)
				{
					pManager->GetStatList()[j]=pManager->GetStatList()[j+1];
					pManager->GetStatList()[j+1]=NULL;
				}
				pManager->DecrementStatCount();
				i--;
				pOut->ClearStatusBar();
			}
		}
	}
	pOut->ClearStatusBar();
}