#ifndef SWITCH_TO_SIMULATION_H
#define SWITCH_TO_SIMULATION_H

#include "Action.h"


class SwitchToSimulation  : public Action
{
private:
	Point Position;
public:
	SwitchToSimulation (ApplicationManager *pAppManager);


	virtual void ReadActionParameters();
	

	virtual void Execute() ;
	
};

#endif