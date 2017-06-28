#ifndef ADD_WRITE_H
#define ADD_WRITE_H

#include "Action.h"
#include "..\Statements\Write.h"

//Add Write Statement Action
//This class is responsible for 
// 1 - Getting Writet stat. coordinates from the user
// 2 - Creating an object of Write class and fill it parameters
// 3 - Adding the created object to the list of statements
class AddWrite : public Action
{
private:
	Point Position;	//Position where the user clicks to add the stat.
	Input* pIn;
	Output* pOut;
	string str;
public:
	AddWrite(ApplicationManager *pAppManager);

	//Write statement's position
	virtual void ReadActionParameters();
	
	//Create and add a Write statement to the list of statements
	virtual void Execute() ;
	
};

#endif