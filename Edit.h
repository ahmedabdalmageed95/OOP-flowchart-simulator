#ifndef EDIT_H
#define EDIT_H

#include "Action.h"
#include "../ApplicationManager.h"

class Edit : public Action
{
private:
	Point Position;
	Input* pIn;
	Output* pOut;
public:
	Edit(ApplicationManager *pAppManager);


	virtual void ReadActionParameters();
	

	virtual void Execute() ;
};

#endif