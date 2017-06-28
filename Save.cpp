#include "Save.h"

#include "../ApplicationManager.h"

#include <sstream>

using namespace std;

//constructor: set the ApplicationManager pointer inside this action
Save::Save(ApplicationManager *pAppManager):Action(pAppManager)
{}

void Save::ReadActionParameters()
{}

void Save::Execute()
{
	ofstream savedfile;
	if(!savedfile.is_open())
		savedfile.open("Saved Flowchart.txt");
	pManager->SaveFlowchart(savedfile);
	savedfile.close();
}

