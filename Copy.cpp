#include "Copy.h"

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
Copy::Copy(ApplicationManager *pAppManager):Action(pAppManager)
{}

void Copy::ReadActionParameters()
{
	if (pManager->MultiplySelected()==false)
	{
		pIn=pManager->GetInput();
		Position=pIn->GetDrawingAreaClick();
		pOut=pManager->GetOutput();
		pOut->PrintMessage("Select the statement you want to Copy");
		pIn->GetPointClicked(Position);
	}
	else
	{
		pIn=pManager->GetInput();
		Position=pIn->GetDrawingAreaClick();
		pOut=pManager->GetOutput();
		pOut->PrintMessage("The selected statements have been copied");
	}
}

void Copy::Execute()
{
	if(pManager->MultiplySelected()==false)
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
				break;
			}
		}
	}
	else
	{
		int j;
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
					for( j=0;j<200;j++)
					{
						if (pManager->GetCpdStat()[j]==NULL)
						{
							pManager->GetCpdStat()[j]=pStat;
							break;
						}
					}
					j++;
				}
			}
		}
	}
	pOut->ClearStatusBar();
}