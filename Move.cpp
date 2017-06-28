#include "Move.h"

#include "../ApplicationManager.h"
#include "../Statements/Conditional.h"

#include <sstream>

using namespace std;

//constructor: set the ApplicationManager pointer inside this action
Move::Move(ApplicationManager *pAppManager):Action(pAppManager)
{}

void Move::ReadActionParameters()
{
	pIn=pManager->GetInput();
	pOut=pManager->GetOutput();
	pIn->UpdateDraggingPoint();
	OldPosition=pIn->GetDraggingPoint();
	NewPosition=OldPosition;
}

void Move::Execute()
{
	ReadActionParameters();
	while(pIn->Dragging())
	{
		if(pManager->MultiplySelected()==false)
		{
			pIn->UpdateDraggingPoint();
			NewPosition=pIn->GetDraggingPoint();
			if(NewPosition.y<UI.TlBrWdth)
			{
				if(pManager->GetSelectedStatement()->GetType()==SMPL_ASSIGN)
					NewPosition.y=UI.TlBrWdth;
				if(pManager->GetSelectedStatement()->GetType()==VAR_ASSIGN)
					NewPosition.y=UI.TlBrWdth;
				if(pManager->GetSelectedStatement()->GetType()==SNGL_OP_ASSIGN)
					NewPosition.y=UI.TlBrWdth;
				if(pManager->GetSelectedStatement()->GetType()==READ)
					NewPosition.y=UI.TlBrWdth;
				if(pManager->GetSelectedStatement()->GetType()==WRITE)
					NewPosition.y=UI.TlBrWdth;
				if(pManager->GetSelectedStatement()->GetType()==START)
					NewPosition.y=UI.TlBrWdth;
				if(pManager->GetSelectedStatement()->GetType()==END)
					NewPosition.y=UI.TlBrWdth;
			}
			if(pManager->GetSelectedStatement()->GetType()==COND)
			{
				if(NewPosition.y<UI.TlBrWdth+((Conditional*)pManager->GetSelectedStatement())->getWidth()/2)
					NewPosition.y=UI.TlBrWdth+((Conditional*)pManager->GetSelectedStatement())->getWidth()/2;
			}
			if(NewPosition.y>(UI.height-UI.StBrWdth)-38)
			{
				if(pManager->GetSelectedStatement()->GetType()==SMPL_ASSIGN)
					NewPosition.y=(UI.height-UI.StBrWdth)-38;
				if(pManager->GetSelectedStatement()->GetType()==VAR_ASSIGN)
					NewPosition.y=(UI.height-UI.StBrWdth)-38;
				if(pManager->GetSelectedStatement()->GetType()==SNGL_OP_ASSIGN)
					NewPosition.y=(UI.height-UI.StBrWdth)-38;
			}
			if(pManager->GetSelectedStatement()->GetType()==COND)
				if(NewPosition.y>(UI.height-UI.StBrWdth)-((Conditional*)pManager->GetSelectedStatement())->getWidth()/2)
					NewPosition.y=(UI.height-UI.StBrWdth)-((Conditional*)pManager->GetSelectedStatement())->getWidth()/2;
			if(NewPosition.y>(UI.height-UI.StBrWdth)-39)
			{
				if(pManager->GetSelectedStatement()->GetType()==READ)
					NewPosition.y=(UI.height-UI.StBrWdth)-39;
				if(pManager->GetSelectedStatement()->GetType()==WRITE)
					NewPosition.y=(UI.height-UI.StBrWdth)-39;
			}
			if(NewPosition.y>(UI.height-UI.StBrWdth)-58)
			{
				if(pManager->GetSelectedStatement()->GetType()==START)
					NewPosition.y=(UI.height-UI.StBrWdth)-58;
				if(pManager->GetSelectedStatement()->GetType()==END)
					NewPosition.y=(UI.height-UI.StBrWdth)-58;
			}
			if(NewPosition.x!=OldPosition.x||NewPosition.y!=OldPosition.y)
			{
				pManager->GetSelectedStatement()->Move(NewPosition);
					OldPosition=NewPosition;
			}
			pManager->UpdateInterface();
			pOut->WindowPause();
		}
		else
		{
			Point PointMovedTo;
			int xchange,ychange;
			for(int i=0;i<200;i++)
			{
				if(pManager->GetSelectedStat()[i]==NULL)
					break;
				else
				{
					pIn->UpdateDraggingPoint();
					NewPosition=pIn->GetDraggingPoint();
					xchange=NewPosition.x-OldPosition.x;
					ychange=NewPosition.y-OldPosition.y;
					PointMovedTo.x=pManager->GetSelectedStat()[i]->GetPoint().x+xchange;
					PointMovedTo.y=pManager->GetSelectedStat()[i]->GetPoint().y+ychange;
					if(PointMovedTo.y<UI.TlBrWdth)
					{
						if(pManager->GetSelectedStat()[i]->GetType()==SMPL_ASSIGN)
							PointMovedTo.y=UI.TlBrWdth;
						if(pManager->GetSelectedStat()[i]->GetType()==VAR_ASSIGN)
							PointMovedTo.y=UI.TlBrWdth;
						if(pManager->GetSelectedStat()[i]->GetType()==SNGL_OP_ASSIGN)
							PointMovedTo.y=UI.TlBrWdth;
						if(pManager->GetSelectedStat()[i]->GetType()==READ)
							PointMovedTo.y=UI.TlBrWdth;
						if(pManager->GetSelectedStat()[i]->GetType()==WRITE)
							PointMovedTo.y=UI.TlBrWdth;
						if(pManager->GetSelectedStat()[i]->GetType()==START)
							PointMovedTo.y=UI.TlBrWdth;
						if(pManager->GetSelectedStat()[i]->GetType()==END)
							PointMovedTo.y=UI.TlBrWdth;
					}
					if(pManager->GetSelectedStat()[i]->GetType()==COND)
					{
						if(PointMovedTo.y<UI.TlBrWdth+((Conditional*)pManager->GetSelectedStat()[i])->getWidth()/2)
							PointMovedTo.y=UI.TlBrWdth+((Conditional*)pManager->GetSelectedStat()[i])->getWidth()/2;
					}
					if(PointMovedTo.y>(UI.height-UI.StBrWdth)-38)
					{
						if(pManager->GetSelectedStat()[i]->GetType()==SMPL_ASSIGN)
							PointMovedTo.y=(UI.height-UI.StBrWdth)-38;
						if(pManager->GetSelectedStat()[i]->GetType()==VAR_ASSIGN)
							PointMovedTo.y=(UI.height-UI.StBrWdth)-38;
						if(pManager->GetSelectedStat()[i]->GetType()==SNGL_OP_ASSIGN)
							PointMovedTo.y=(UI.height-UI.StBrWdth)-38;
					}
					if(pManager->GetSelectedStat()[i]->GetType()==COND)
						if(PointMovedTo.y>(UI.height-UI.StBrWdth)-((Conditional*)pManager->GetSelectedStat()[i])->getWidth()/2)
							PointMovedTo.y=(UI.height-UI.StBrWdth)-((Conditional*)pManager->GetSelectedStat()[i])->getWidth()/2;
					if(PointMovedTo.y>(UI.height-UI.StBrWdth)-39)
					{
						if(pManager->GetSelectedStat()[i]->GetType()==READ)
							PointMovedTo.y=(UI.height-UI.StBrWdth)-39;
						if(pManager->GetSelectedStat()[i]->GetType()==WRITE)
							PointMovedTo.y=(UI.height-UI.StBrWdth)-39;
					}
					if(PointMovedTo.y>(UI.height-UI.StBrWdth)-58)
					{
						if(pManager->GetSelectedStat()[i]->GetType()==START)
							PointMovedTo.y=(UI.height-UI.StBrWdth)-58;
						if(pManager->GetSelectedStat()[i]->GetType()==END)
							PointMovedTo.y=(UI.height-UI.StBrWdth)-58;
					}
					if(NewPosition.x!=OldPosition.x||NewPosition.y!=OldPosition.y)
					{
						pManager->GetSelectedStat()[i]->Move(PointMovedTo);
							OldPosition=NewPosition;
					}
					pManager->UpdateInterface();
					pOut->WindowPause();
				}
			}
		}
	}
}