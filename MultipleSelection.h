#ifndef MULTIPLE_SELECTION_H
#define MULTIPLE_SELECTION_H

#include "Action.h"
#include "..\Statements\Write.h"


class MultipleSelection : public Action
{
private:
	Point Position;
	

public:
	MultipleSelection(ApplicationManager *pAppManager);


	virtual void ReadActionParameters();
	

	virtual void Execute() ;
	
};

#endif