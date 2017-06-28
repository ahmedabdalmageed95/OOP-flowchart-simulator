#ifndef ADD_SNGLOP_ASSIGN_H
#define ADD_SNGLOP_ASSIGN_H

#include "Action.h"
#include "..\Statements\SnglOpAssign.h"

//Add Single Operator Assignment Statement Action
//This class is responsible for 
// 1 - Getting Single Operator Assignment stat. coordinates from the user
// 2 - Creating an object of  Single Operator Assignment class and fill it parameters
// 3 - Adding the created object to the list of statements
class AddSnglOpAssign : public Action
{
private:
	Point Position;	//Position where the user clicks to add the stat.
	string str;
	Input *pIn;
	Output* pOut;

public:
	AddSnglOpAssign(ApplicationManager *pAppManager);

	//Read Single Operator Assignemt statements position
	virtual void ReadActionParameters();
	
	//Create and add a Single Operator assignemnt statement to the list of statements
	virtual void Execute() ;
	
};

#endif