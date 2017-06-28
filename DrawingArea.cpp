#include "DrawingArea.h"

#include "../ApplicationManager.h"

#include <sstream>

using namespace std;

//constructor: set the ApplicationManager pointer inside this action
DrawingArea::DrawingArea(ApplicationManager *pAppManager):Action(pAppManager)
{}

void DrawingArea::ReadActionParameters()
{
	Input* pIn=pManager->GetInput();
	Position=pIn->GetDrawingAreaClick();
}

void DrawingArea::Execute()
{
	Output* pOut=pManager->GetOutput();
	pOut->ClearStatusBar();
	ReadActionParameters();
	for(int i=0;i<pManager->GetStatCount();i++)
	{
		if(pManager->GetStatList()[i]==pManager->GetStatement(Position))
		{
			if(pManager->GetSelectedStatement()!=NULL)
				Unselect();
			Select(pManager->GetStatList()[i]);
			break;
		}
		if(i==pManager->GetStatCount()-1&&pManager->GetSelectedStatement()!=NULL)
		{
			Unselect();
		}
	}
	MultipleUnselect();
}

void DrawingArea::Select(Statement* stat)
{
	pManager->SetSelectedStatement(stat);
	Output* pOut=pManager->GetOutput();
	pOut->ClearStatusBar();
	stat->PrintInfo();
}

void DrawingArea::Unselect()
{
	Output* pOut=pManager->GetOutput();
	pOut->ClearStatusBar();
	pManager->SetSelectedStatement(NULL);
}

void DrawingArea::MultipleUnselect()
{
	for(int i=0;i<200;i++)
	{
		if(pManager->GetSelectedStat()[i]!=NULL)
		{
			pManager->GetSelectedStat()[i]->SetSelected(false);
			pManager->GetSelectedStat()[i]=NULL;
		}
		else
			break;
	}
}