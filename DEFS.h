#ifndef DEFS_H
#define DEFS_H

//This file contais some global constants and definitions to be used in the project.

#include <fstream>
#include <cmath>

enum ActionType //The actions supported (you can add more if needed)
{
	ADD_SMPL_ASSIGN,//Add simple assignment statement
	ADD_VAR_ASSIGN,	//Add variable assignment statement
	ADD_OP_ASSIGN,
	ADD_CONDITION, //Add a conditional statement (for if and while-loop statements)

	ADD_CONNECTOR, //Add a connector between two statements

	ADD_READ,
	ADD_WRITE,
	ADD_START,
	ADD_END,

	EDIT_STAT,	//Edit a statement
	COMMENT,	//Comment on a statement
	
	DRAW_AREA,
	SIM_AREA,

	DEL,		//Delete a figure(s)
	MOVE,		//Move a figure(s)
	RESIZE,		//Resize a figure(s)

	SAVE,		//Save the whole graph to a file
	LOAD,		//Load a graph from a file
	EXIT,		//Exit the application
	STATUS,		//A click on the status bar
	DSN_TOOL,	//A click on an empty place in the design tool bar
	SIM_TOOL,
	DSN_MODE,	//Switch to Design mode
	SIM_MODE,	//Switch to simulatiom mode

	MULTIPLE_SELECTION,
	COPY,
	CUT,
	PASTE,
	UNDO,
	REDO,

	VALIDATE,
	RUN,
	STP,
	GENERATE
};

enum  MODE	//Modes of operation
{
	DESIGN,
	SIMULATION
};

enum DsgnMenuItem //The items of the design menu (you should add more items)
{
	//Note: Items are ordered here as they appear in menu
	//If you change the menu items order, change the order here too
	ITM_EXIT,
	ITM_SAVE,
	ITM_LOAD,
	ITM_UNDO,
	ITM_SMPL_ASSIGN,//simple assignment statement
	ITM_VAR_ASSIGN,
	ITM_SNGL_OP_ASSIGN,
	ITM_COND,		//conditional statement
	ITM_READ,
	ITM_WRITE,
	ITM_START,
	ITM_END,
	ITM_CONN,
	ITM_MULTIPLE,
	ITM_EDIT,
	ITM_COMMENT,
	ITM_COPY,
	ITM_CUT,
	ITM_PASTE,
	ITM_DEL,
	ITM_SIM,
	
	ITM_DSN_CNT		//no. of design menu items ==> This should be the last line in this enum
	
};


enum SimMenuItem //The items of the simulation menu (you should add more items)
{
	//Note: Items are ordered here as they appear in menu
	ITM_VALIDATE,
	ITM_RUN,	//Run
	ITM_STP,	//Step by step
	ITM_GENERATE,
	
	ITM_SIM_CNT		//no. of simulation menu items ==> This should be the last line in this enum
	
};

enum StatementType
{
	SMPL_ASSIGN,
	VAR_ASSIGN,
	SNGL_OP_ASSIGN,
	COND,
	READ,
	WRITE,
	START,
	END
};

int round(double no);	//this function is used to remove the conversion from 'double' to 'int' graphics library warning

#ifndef NULL
#define NULL 0
#endif

#endif