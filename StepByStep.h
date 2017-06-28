#ifndef STEPBYSTEP_H
#define STEPBYSTEP_H

#include "Action.h"
#include "../ApplicationManager.h"

class StepByStep : public Action
{
private:
	Point Position;
	Input* pIn;
	Output* pOut;
	string s;
public:
	StepByStep(ApplicationManager *pAppManager);


	virtual void ReadActionParameters();
	

	virtual void Execute() ;
};

#endif