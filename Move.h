#ifndef MOVE_H
#define MOVE_H

#include "Action.h"
#include "../ApplicationManager.h"

class Move : public Action
{
private:
	Point OldPosition,NewPosition;
	Input* pIn;
	Output* pOut;
public:
	Move(ApplicationManager *pAppManager);


	virtual void ReadActionParameters();
	

	virtual void Execute() ;
};

#endif