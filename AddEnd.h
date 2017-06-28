#ifndef ADD_END_H
#define ADD_END_H

#include "Action.h"
#include "..\Statements\End.h"

//Add Start Statement Action
//This class is responsible for 
// 1 - Getting End stat. coordinates from the user
// 2 - Creating an object of End class and fill it parameters
// 3 - Adding the created object to the list of statements
class AddEnd  : public Action
{
private:
	Point Position;	//Position where the user clicks to add the stat.
public:
	AddEnd (ApplicationManager *pAppManager);

	//Read End statements position
	virtual void ReadActionParameters();
	
	//Create and add an End statement to the list of statements
	virtual void Execute() ;
	
};

#endif