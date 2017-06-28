#ifndef VALIDATE_H
#define VALIDATE_H

#include "Action.h"
#include "..\ApplicationManager.h"


//Chart Validation: For the simulation to start, The following should be valid
//a. Chart have exactly one Start and one End statements
//b. Chart is fully connected
class Validate : public Action
{
private:
	Input *pIn;
	Output* pOut;
public:
	Validate(ApplicationManager *pAppManager);
	virtual void ReadActionParameters();
    virtual void Execute() ;

};

#endif