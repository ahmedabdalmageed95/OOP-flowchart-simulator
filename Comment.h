#ifndef COMMENT_H
#define COMMENT_H

#include "Action.h"
#include "../ApplicationManager.h"

class Comment : public Action
{
private:
	Point Position;
	Input* pIn;
	Output* pOut;
public:
	Comment(ApplicationManager *pAppManager);


	virtual void ReadActionParameters();
	

	virtual void Execute() ;
};

#endif