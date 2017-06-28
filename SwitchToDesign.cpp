#include "SwitchToDesign.h"





#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>

using namespace std;

//constructor: set the ApplicationManager pointer inside this action
SwitchToDesign ::SwitchToDesign (ApplicationManager *pAppManager):Action(pAppManager)
{}

void SwitchToDesign ::ReadActionParameters()
{}

void SwitchToDesign ::Execute()
{
	Input *pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	pOut->CreateDesignToolBar();
	pOut->ClearStatusBar();		
}

