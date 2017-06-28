#ifndef UNDO_H
#define UNDO_H

#include "Action.h"
#include "../ApplicationManager.h"

class Undo : public Action
{
private:
	Point Position;
	Input* pIn;
	Output* pOut;
public:
	Undo(ApplicationManager *pAppManager);


	virtual void ReadActionParameters();
	

	virtual void Execute() ;
};

#endif