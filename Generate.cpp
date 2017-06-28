#include "Generate.h"

#include "Action.h"
#include "../ApplicationManager.h"

#include "../Statements/Start.h"
#include "../Statements/End.h"
#include "../Statements/Read.h"
#include "../Statements/Write.h"
#include "../Statements/SmplAssign.h"
#include "../Statements/VarAssign.h"
#include "../Statements/SnglOpAssign.h"
#include "../Statements/Conditional.h"

#include <sstream>

using namespace std;

//constructor: set the ApplicationManager pointer inside this action
Generate::Generate(ApplicationManager *pAppManager):Action(pAppManager)
{}

void Generate::ReadActionParameters()
{}

void Generate::Execute()
{
	pIn=pManager->GetInput();
	pOut=pManager->GetOutput();

	Statement* pStat;
	for(int i=0;i<pManager->GetStatCount();i++)
	{
		if(pManager->GetStatList()[i]->GetType()==START)
		{
			pStat=pManager->GetStatList()[i];
			break;
		}
	}
	ofstream out;
	out.open("C++ code.txt");
	out<<"#include <iostream>\nusing namespace std;\n\nint main()\n{\n";
	string variables[200];
	int numberofvariables=0;
	for(int i=0;i<pManager->GetStatCount();i++)
	{
		if(pManager->GetStatList()[i]->GetType()==SMPL_ASSIGN)
		{
			variables[numberofvariables]=((SmplAssign*)pManager->GetStatList()[i])->GetLHS();
			numberofvariables++;
		}
		if(pManager->GetStatList()[i]->GetType()==VAR_ASSIGN)
		{
			variables[numberofvariables]=((VarAssign*)pManager->GetStatList()[i])->GetLHS();
			numberofvariables++;
		}
		if(pManager->GetStatList()[i]->GetType()==SNGL_OP_ASSIGN)
		{
			variables[numberofvariables]=((SnglOpAssign*)pManager->GetStatList()[i])->GetLHS();
			numberofvariables++;
		}
		if(pManager->GetStatList()[i]->GetType()==READ)
		{
			variables[numberofvariables]=((Read*)pManager->GetStatList()[i])->Getinput();
			numberofvariables++;
		}
	}
	for(int i=0;i<numberofvariables;i++)
	{
		for(int j=0;j<i;j++)
			if(variables[i]==variables[j])
				variables[i]="";
	}
	for(int i=0;i<numberofvariables;i++)
	{
		if(variables[i]!="")
			out<<"\tdouble "<<variables[i]<<";\n";
	}
	while(pStat->GetType()!=END)
		pStat=pStat->GenerateCode(out);
	pStat=pStat->GenerateCode(out);
	pOut->PrintMessage("Flowchart equivalent C++ code has been generated in \"C++ code.txt\"");
}