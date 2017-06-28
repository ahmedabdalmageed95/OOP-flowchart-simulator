#ifndef Copy_H
#define Copy_H

#include "Action.h"
#include "../ApplicationManager.h"
#include "../Statements/Start.h"
#include "../Statements/End.h"
#include "../Statements/Conditional.h"
#include "../Statements/Read.h"
#include "../Statements/Write.h"
#include "../Statements/SmplAssign.h"
#include "../Statements/SnglOpAssign.h"
#include "../Statements/VarAssign.h"

class Copy : public Action
{
private:
	Point Position;
	Input* pIn;
	Output* pOut;

public:
	Copy(ApplicationManager *pAppManager);


	virtual void ReadActionParameters();
	

	virtual void Execute() ;
};
#endif