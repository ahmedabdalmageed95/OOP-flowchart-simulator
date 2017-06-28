#include "SwitchToSimulation.h"





#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>

using namespace std;

//constructor: set the ApplicationManager pointer inside this action
SwitchToSimulation ::SwitchToSimulation (ApplicationManager *pAppManager):Action(pAppManager)
{}

void SwitchToSimulation ::ReadActionParameters()
{}

void SwitchToSimulation ::Execute()
{
	Input *pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	pOut->CreateSimulationToolBar();
	pOut->ClearStatusBar();		
}

