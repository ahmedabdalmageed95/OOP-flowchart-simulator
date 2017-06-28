#ifndef RUN_H
#define RUN_H

#include "Action.h"
#include "../ApplicationManager.h"

class Run : public Action
{
private:
	Point Position;
	Input* pIn;
	Output* pOut;
public:
	Run(ApplicationManager *pAppManager);


	virtual void ReadActionParameters();
	

	virtual void Execute() ;
};

#endif