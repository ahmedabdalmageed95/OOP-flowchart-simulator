#ifndef GENERATE_H
#define GENERATE_H

#include "Action.h"
#include "../ApplicationManager.h"

class Generate : public Action
{
private:
	Point Position;
	Input* pIn;
	Output* pOut;
public:
	Generate(ApplicationManager *pAppManager);


	virtual void ReadActionParameters();
	

	virtual void Execute() ;
};

#endif