#include "Paste.h"

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
Paste::Paste(ApplicationManager *pAppManager):Action(pAppManager)
{}

void Paste::ReadActionParameters()
{
	if (pManager->MultiplySelected()==false)
	{
		Input*pIn=pManager->GetInput();
		Position=pIn->GetDrawingAreaClick();
		Output*pOut=pManager->GetOutput();
		pOut->PrintMessage("Select where you want to paste");
		pIn->GetPointClicked(Position);
	}
	else
	{
		Input*pIn=pManager->GetInput();
		Position=pIn->GetDrawingAreaClick();
		Output*pOut=pManager->GetOutput();
		pOut->PrintMessage("Select where you want to paste");
		pIn->GetPointClicked(Position);
	}
}

void Paste::Execute()
{
	if (pManager->MultiplySelected()==false)
	{
		ReadActionParameters();
		Statement* pStat=NULL;
		if(dynamic_cast<SmplAssign*>(pManager->GetCopiedStatement()))
			pStat=new SmplAssign((*dynamic_cast<SmplAssign*>(pManager->GetCopiedStatement())),Position);
		if(dynamic_cast<VarAssign*>(pManager->GetCopiedStatement()))
			pStat=new VarAssign((*dynamic_cast<VarAssign*>(pManager->GetCopiedStatement())),Position);
		if(dynamic_cast<SnglOpAssign*>(pManager->GetCopiedStatement()))
			pStat=new SnglOpAssign((*dynamic_cast<SnglOpAssign*>(pManager->GetCopiedStatement())),Position);
		if(dynamic_cast<Conditional*>(pManager->GetCopiedStatement()))
			pStat=new Conditional((*dynamic_cast<Conditional*>(pManager->GetCopiedStatement())),Position);
		if(dynamic_cast<Read*>(pManager->GetCopiedStatement()))
			pStat=new Read((*dynamic_cast<Read*>(pManager->GetCopiedStatement())),Position);
		if(dynamic_cast<Write*>(pManager->GetCopiedStatement()))
			pStat=new Write((*dynamic_cast<Write*>(pManager->GetCopiedStatement())),Position);
		if(dynamic_cast<Start*>(pManager->GetCopiedStatement()))
			pStat=new Start((*dynamic_cast<Start*>(pManager->GetCopiedStatement())),Position);
		if(dynamic_cast<End*>(pManager->GetCopiedStatement()))
			pStat=new End((*dynamic_cast<End*>(pManager->GetCopiedStatement())),Position);
		if(pStat!=NULL)
		{
			pManager->AddStatement(pStat);
		}
		pManager->SetCopiedStatement(NULL);
	}
	else
	{
		ReadActionParameters();
		Statement* pStat=NULL;
		for (int i=0;i<200;i++)
		{
			if (pManager->GetCpdStat()[i]!=NULL)
			{
				if(dynamic_cast<SmplAssign*>(pManager->GetCpdStat()[i]))
					pStat=new SmplAssign((*dynamic_cast<SmplAssign*>(pManager->GetCpdStat()[i])),Position);
				if(dynamic_cast<VarAssign*>(pManager->GetCpdStat()[i]))
					pStat=new VarAssign((*dynamic_cast<VarAssign*>(pManager->GetCpdStat()[i])),Position);
				if(dynamic_cast<SnglOpAssign*>(pManager->GetCpdStat()[i]))
					pStat=new SnglOpAssign((*dynamic_cast<SnglOpAssign*>(pManager->GetCpdStat()[i])),Position);
				if(dynamic_cast<Conditional*>(pManager->GetCpdStat()[i]))
					pStat=new Conditional((*dynamic_cast<Conditional*>(pManager->GetCpdStat()[i])),Position);
				if(dynamic_cast<Read*>(pManager->GetCpdStat()[i]))
					pStat=new Read((*dynamic_cast<Read*>(pManager->GetCpdStat()[i])),Position);
				if(dynamic_cast<Write*>(pManager->GetCpdStat()[i]))
					pStat=new Write((*dynamic_cast<Write*>(pManager->GetCpdStat()[i])),Position);
				if(dynamic_cast<Start*>(pManager->GetCpdStat()[i]))
					pStat=new Start((*dynamic_cast<Start*>(pManager->GetCpdStat()[i])),Position);
				if(dynamic_cast<End*>(pManager->GetCpdStat()[i]))
					pStat=new End((*dynamic_cast<End*>(pManager->GetCpdStat()[i])),Position);
				if(pStat!=NULL)
					pManager->AddStatement(pStat);
				Position.y=Position.y+50;
			}
		}
		pManager->SetCopiedStatement(NULL);
		for (int i=0;i<200;i++)
		{
			if (pManager->GetCpdStat()[i]!=NULL)
			{
				pManager->GetCpdStat()[i]->SetSelected(false);
				pManager->GetCpdStat()[i]=NULL;
				pManager->GetSelectedStat()[i]=NULL;
			}
		}
	}
	pManager->GetOutput()->ClearStatusBar();
}

