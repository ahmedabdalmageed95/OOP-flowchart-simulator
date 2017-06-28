#ifndef SAVE_H
#define SAVE_H

#include "Action.h"
#include "../ApplicationManager.h"

class Save : public Action
{
public:
	Save(ApplicationManager *pAppManager);

	virtual void ReadActionParameters();
	
	virtual void Execute() ;
	
};

#endif