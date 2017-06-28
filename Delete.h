#ifndef DELETE_H
#define DELETE_H

#include "Action.h"
#include "../ApplicationManager.h"

class Delete : public Action
{
private:
	Point Position;
	Input* pIn;
	Output* pOut;
public:
	Delete(ApplicationManager *pAppManager);


	virtual void ReadActionParameters();
	

	virtual void Execute() ;
};

#endif