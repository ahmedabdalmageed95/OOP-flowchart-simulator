#include "Validate.h"



#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include "..\Statements\SmplAssign.h"
#include "..\Statements\VarAssign.h"
#include "..\Statements\SnglOpAssign.h"
#include "..\Statements\Conditional.h"
#include "..\Statements\Read.h"
#include "..\Statements\Write.h"
#include "..\Statements\Start.h"
#include "..\Statements\End.h"

#include <sstream>

using namespace std;

//constructor: set the ApplicationManager pointer inside this action
Validate::Validate(ApplicationManager *pAppManager):Action(pAppManager)
{}

void Validate::ReadActionParameters()
{}

void Validate::Execute()
{
	pManager->ValidateFlowchart();
}