#include "Cut.h"

#include "../ApplicationManager.h"

#include <sstream>

#include "../Statements/Start.h"
#include "../Statements/End.h"
#include "../Statements/Read.h"
#include "../Statements/Write.h"
#include "../Statements/SmplAssign.h"
#include "../Statements/VarAssign.h"
#include "../Statements/SnglOpAssign.h"
#include "../Statements/Conditional.h"

using namespace std;

//constructor: set the ApplicationManager pointer inside this action
Cut::Cut(ApplicationManager *pAppManager):Action(pAppManager)
{}

void Cut::ReadActionParameters()
{
	if (pManager->MultiplySelected()==false)
	{
		pIn=pManager->GetInput();
		Position=pIn->GetDrawingAreaClick();
		pOut=pManager->GetOutput();
		pOut->PrintMessage("Select the statement you want to Cut");
		pIn->GetPointClicked(Position);
	}
	else 
	{
		pIn=pManager->GetInput();
		Position=pIn->GetDrawingAreaClick();
		pOut=pManager->GetOutput();
		pOut->PrintMessage(" Cut selected statements");
	}
}

void Cut::Execute()
{
	if (pManager->MultiplySelected()==false)
	{
		ReadActionParameters();
		for(int i=0;i<pManager->GetStatCount();i++)
		{
			if (pManager->GetStatList()[i]==pManager->GetStatement(Position))
			{
				if(pManager->GetCopiedStatement()!=NULL)
				{
					delete pManager->GetCopiedStatement();
					pManager->SetCopiedStatement(NULL);
				}
				Statement* pStat;
				if(dynamic_cast<SmplAssign*>(pManager->GetStatList()[i]))
					pStat=new SmplAssign((*dynamic_cast<SmplAssign*>(pManager->GetStatList()[i])),Position);
				if(dynamic_cast<VarAssign*>(pManager->GetStatList()[i]))
					pStat=new VarAssign((*dynamic_cast<VarAssign*>(pManager->GetStatList()[i])),Position);
				if(dynamic_cast<SnglOpAssign*>(pManager->GetStatList()[i]))
					pStat=new SnglOpAssign((*dynamic_cast<SnglOpAssign*>(pManager->GetStatList()[i])),Position);
				if(dynamic_cast<Conditional*>(pManager->GetStatList()[i]))
					pStat=new Conditional((*dynamic_cast<Conditional*>(pManager->GetStatList()[i])),Position);
				if(dynamic_cast<Read*>(pManager->GetStatList()[i]))
					pStat=new Read((*dynamic_cast<Read*>(pManager->GetStatList()[i])),Position);
				if(dynamic_cast<Write*>(pManager->GetStatList()[i]))
					pStat=new Write((*dynamic_cast<Write*>(pManager->GetStatList()[i])),Position);
				if(dynamic_cast<Start*>(pManager->GetStatList()[i]))
					pStat=new Start((*dynamic_cast<Start*>(pManager->GetStatList()[i])),Position);
				if(dynamic_cast<End*>(pManager->GetStatList()[i]))
					pStat=new End((*dynamic_cast<End*>(pManager->GetStatList()[i])),Position);
				if(pStat!=NULL)
					pManager->SetCopiedStatement(pStat);
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
				break;
			}
		}
	}
	else
	{
		int k;
		ReadActionParameters();
		for(int i=0;i<pManager->GetStatCount();i++)
		{
			if (pManager->GetStatList()[i]->IsSelected()==true)
			{
				Statement* pStat;
				if(dynamic_cast<SmplAssign*>(pManager->GetStatList()[i]))
					pStat=new SmplAssign((*dynamic_cast<SmplAssign*>(pManager->GetStatList()[i])),Position);
				if(dynamic_cast<VarAssign*>(pManager->GetStatList()[i]))
					pStat=new VarAssign((*dynamic_cast<VarAssign*>(pManager->GetStatList()[i])),Position);
				if(dynamic_cast<SnglOpAssign*>(pManager->GetStatList()[i]))
					pStat=new SnglOpAssign((*dynamic_cast<SnglOpAssign*>(pManager->GetStatList()[i])),Position);
				if(dynamic_cast<Conditional*>(pManager->GetStatList()[i]))
					pStat=new Conditional((*dynamic_cast<Conditional*>(pManager->GetStatList()[i])),Position);
				if(dynamic_cast<Read*>(pManager->GetStatList()[i]))
					pStat=new Read((*dynamic_cast<Read*>(pManager->GetStatList()[i])),Position);
				if(dynamic_cast<Write*>(pManager->GetStatList()[i]))
					pStat=new Write((*dynamic_cast<Write*>(pManager->GetStatList()[i])),Position);
				if(dynamic_cast<Start*>(pManager->GetStatList()[i]))
					pStat=new Start((*dynamic_cast<Start*>(pManager->GetStatList()[i])),Position);
				if(dynamic_cast<End*>(pManager->GetStatList()[i]))
					pStat=new End((*dynamic_cast<End*>(pManager->GetStatList()[i])),Position);
				if(pStat!=NULL)
				{
					for( k=0;k<200;k++)
					{
						if (pManager->GetCpdStat()[k]==NULL)
						{
							pManager->GetCpdStat()[k]=pStat;
							break;
						}
						
					}
				}
				for(int j=0;j<pManager->GetConnCount();j++)
				{
					if(pManager->GetStatList()[i]==pManager->GetConnList()[j]->getSrcStat()||pManager->GetStatList()[i]==pManager->GetConnList()[j]->getDstStat())
					{
						pManager->GetConnList()[j]->getSrcStat()->setpConn(NULL);
						delete pManager->GetConnList()[j];
						pManager->GetConnList()[j]=NULL;
						for(int l=j;l<pManager->GetConnCount()-1;l++)
						{
							pManager->GetConnList()[l]=pManager->GetConnList()[l+1];
							pManager->GetConnList()[l+1]=NULL;
						}
						j--;
						pManager->DecrementConnCount();
					}
				}
				for (int j=0;j<pManager->GetStatCount();j++)
				{
					if (pManager->GetStatList()[j]->IsSelected()==true)
					{
						delete pManager->GetStatList()[i];
						pManager->GetStatList()[i]=NULL;
						for(int j=i;j<pManager->GetStatCount()-1;j++)
						{
							pManager->GetStatList()[j]=pManager->GetStatList()[j+1];
							pManager->GetStatList()[j+1]=NULL;
						}
						pManager->DecrementStatCount();
						i--;
						break;
					}	
				}
			}
		}
	}
	pOut->ClearStatusBar();
}