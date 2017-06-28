#ifndef Paste_H
#define Paste_H

#include "Action.h"
#include "../ApplicationManager.h"

class Paste : public Action
{
private:
	Point Position;
public:
	Paste(ApplicationManager *pAppManager);


	virtual void ReadActionParameters();
	

	virtual void Execute() ;
	
};

#endif