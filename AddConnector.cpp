#include "AddConnector.h"



#include "../ApplicationManager.h"
#include "../Statements/SmplAssign.h"
#include "../Statements/VarAssign.h"
#include "../Statements/SnglOpAssign.h"
#include "../Statements/Conditional.h"
#include "../Statements/Read.h"
#include "../Statements/Write.h"
#include "../Statements/Start.h"
#include "../Statements/End.h"
#include "../GUI/input.h"
#include "../GUI/Output.h"

#include <sstream>

using namespace std;

//constructor: set the ApplicationManager pointer inside this action
AddConnector::AddConnector(ApplicationManager *pAppManager):Action(pAppManager)
{}

void AddConnector::ReadActionParameters()
{
	Input* pIn=pManager->GetInput();
	Output* pOut=pManager->GetOutput();
	pOut->PrintMessage("Connector between two statements: Select the source statement");
	pIn->GetPointClicked(Position1);
	SrcStat=pManager->GetStatement(Position1);
	while(SrcStat==NULL)
	{
		pOut->PrintMessage("No statement has been selected. Please select the source statement");
		pIn->GetPointClicked(Position1);
		SrcStat=pManager->GetStatement(Position1);
	}
	pOut->PrintMessage("Select the destination statement");
	pIn->GetPointClicked(Position2);
	DstStat=pManager->GetStatement(Position2);
	while(DstStat==NULL||DstStat==SrcStat)
	{
		pOut->PrintMessage("No statement has been selected. Please select the destination statement");
		pIn->GetPointClicked(Position2);
		DstStat=pManager->GetStatement(Position2);
	}
	if(SrcStat->GetType()==COND)
	{
		pOut->PrintMessage("Which conditional outlet do you want? Press \"y\" for yes and \"n\" for no");
		cond=pIn->GetCharPressed();
		while(cond!='y'&&cond!='n')
			cond=pIn->GetCharPressed();
	}
	pOut->ClearStatusBar();
}

void AddConnector::Execute()
{
	ReadActionParameters();
	Connector* Conn;
	if(SrcStat->GetType()==END)
	{
		Output* pOut=pManager->GetOutput();
		pOut->PrintMessage("Cannot draw a connector whose source statement is an End statement");
	}
	else
	{
		if(cond=='n')
		{
			Conn=new Connector(SrcStat,DstStat,pManager,false);
			Conn->getSrcStat()->setpConn(Conn);
		}
		else
		{
			Conn=new Connector(SrcStat,DstStat,pManager);
			Conn->getSrcStat()->setpConn(Conn);
		}
		pManager->AddConn(Conn);
	}
}