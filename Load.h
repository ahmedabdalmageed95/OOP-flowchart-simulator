#ifndef LOAD_H
#define LOAD_H

#include "Action.h"
#include "../ApplicationManager.h"

class Load : public Action
{
public:
	Load(ApplicationManager *pAppManager);

	virtual void ReadActionParameters();
	
	virtual void Execute() ;
	
};

#endif