#include "Load.h"

#include "../ApplicationManager.h"

#include <sstream>

using namespace std;

//constructor: set the ApplicationManager pointer inside this action
Load::Load(ApplicationManager *pAppManager):Action(pAppManager)
{}

void Load::ReadActionParameters()
{}

void Load::Execute()
{
	ifstream loadedfile;
	loadedfile.open("Saved Flowchart.txt");
	pManager->LoadFlowchart(loadedfile);
	loadedfile.close();
	Output* pOut;
	pOut=pManager->GetOutput();
	pOut->PrintMessage("Flowchart has been loaded from \"Saved Flowchart.txt\"");
}

