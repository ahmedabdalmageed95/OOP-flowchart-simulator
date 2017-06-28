#include "Undo.h"

#include "../ApplicationManager.h"

#include <sstream>

using namespace std;

//constructor: set the ApplicationManager pointer inside this action
Undo::Undo(ApplicationManager *pAppManager):Action(pAppManager)
{}

void Undo::ReadActionParameters()
{}

void Undo::Execute()
{
	if(pManager->GetUndoStatListsUsed()!=0)
		pManager->RecoverStatListFromUndoStatArray(pManager->GetUndoStatListsUsed()-1);
	if(pManager->GetUndoConnListsUsed()!=0)
		pManager->RecoverConnListFromUndoConnArray(pManager->GetUndoConnListsUsed()-1);
}