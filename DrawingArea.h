#ifndef Select_H
#define Select_H

#include "Action.h"
#include "../ApplicationManager.h"

class DrawingArea : public Action
{
private:
	Point Position;
public:
	DrawingArea(ApplicationManager *pAppManager);


	virtual void ReadActionParameters();
	

	virtual void Execute() ;
	void Select(Statement* stat);
	void Unselect();
	void MultipleUnselect();
};

#endif