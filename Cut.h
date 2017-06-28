#ifndef Cut_H
#define Cut_H

#include "Action.h"
#include "../ApplicationManager.h"

class Cut : public Action
{
private:
	Point Position;
	Input* pIn;
	Output* pOut;
	 Statement*CpdStat;
public:
	Cut(ApplicationManager *pAppManager);


	virtual void ReadActionParameters();
	

	virtual void Execute() ;
};
#endif