#ifndef SWITCH_TO_DESIGN_H
#define SWITCH_TO_DESIGN_H

#include "Action.h"


class SwitchToDesign  : public Action
{
private:
	Point Position;
public:
	SwitchToDesign (ApplicationManager *pAppManager);


	virtual void ReadActionParameters();
	

	virtual void Execute() ;
	
};

#endif