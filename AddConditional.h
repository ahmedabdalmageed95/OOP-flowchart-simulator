#ifndef ADD_COND_H
#define ADD_COND_H

#include "Action.h"
#include "..\Statements\Conditional.h"

//Add Conditional Statement Action
//This class is responsible for 
// 1 - Getting Conditional stat. coordinates from the user
// 2 - Creating an object of Conditional class and fill it parameters
// 3 - Adding the created object to the list of statements
class AddConditional : public Action
{
private:
	Point Position;	//Position where the user clicks to add the stat.
	string str;
	Input *pIn;
	Output* pOut;

public:
	AddConditional(ApplicationManager *pAppManager);

	//Read Conditional statement's position
	virtual void ReadActionParameters();
	
	//Create and add a Conditional statement to the list of statements
	virtual void Execute() ;
	
};

#endif