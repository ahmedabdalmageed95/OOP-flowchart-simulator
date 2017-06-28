#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include "DEFS.h"

#include "Statements\Statement.h"
class Input;
class Output;


//Main class that manages everything in the application.
class ApplicationManager
{
	enum { MaxCount = 200 };	//Max no of statements/connectors in a single flowchart

private:
	int StatCount;		//Actual number of statements
	int ConnCount;		//Actual number of connectors
	Statement* StatList[MaxCount];	//List of all statements (Array of pointers)
	Connector* ConnList[MaxCount];	//List of all connectors (Array of pointers)
	Statement* SelectedStat[MaxCount]; //List of all selected statements in multiple selection
	Statement* CpdStat[MaxCount];	//List of all copied statements in multiple copy
	Statement* UndoStatArray[10][MaxCount];	 //Undo array of 10 elements. Each element is an array of pointers to statements
	Connector* UndoConnArray[10][MaxCount];	//Undo array of 10 elements. Each element is an array of pointers to connectors
	int UndoStatListsUsed;	//Number of statement arrays used in Undo array
	int UndoConnListsUsed;	//Number of connector arrays used in Undo array
	int UndoStatArrayStatCount[10];	//Number of statements in each statement array in the Undo array
	int UndoConnArrayConnCount[10];	//Number of connectors in each connector array in the Undo array

	Statement *pSelectedStat; //a pointer to the last selected statement
	Statement *pCpdStat;	//a pointer to the last copied statement

	//Pointers to Input and Output classes
	Input *pIn;
	Output *pOut;

public:	
	ApplicationManager(); 
	~ApplicationManager();
	
	// -- Actions Related Functions
	//Reads the input command from the user and returns the corresponding action type
	ActionType GetUserAction() const;
	void ExecuteAction(ActionType) ; //Creates an action and executes it
	
	// -- Statements/Connector Management Functions
	void AddStatement(Statement* pStat); //Adds a new Statement to the Flowchart
	Statement *GetStatement(Point P) const;	//search for a statement where point P belongs

	void AddConn(Connector* pConn); //Adds a new Connector to the Flowchart
	Connector *GetConnector(Point P) const;	//search for a Connector where point P belongs

	//Undo Functions
	void PushStatListInUndoStatArray(); //Saves current StatList in the Undo array
	void ShiftUndoStatListsLeft();	//Is called when the Undo array is full. Deletes first element and frees last element
	void CopyOfStatListInUndoStatArray(int i);
	void RecoverStatListFromUndoStatArray(int i); //Makes the ith element of the Undo array become the StatList
	void PushConnListInUndoConnArray();	//Saves current ConnList in the Undo array
	void ShiftUndoConnListsLeft();	//Is called when the Undo array is full. Deletes first element and frees last element
	void CopyOfConnListInUndoConnArray(int i);
	void RecoverConnListFromUndoConnArray(int i);	//Makes the ith element of the Undo array become the ConnList
	//

	Statement *GetSelectedStatement() const;	//Returns the selected Statement
	void SetSelectedStatement(Statement *pStat); //Set the Statement selected by the user
	Statement *GetCopiedStatement() const;
	void SetCopiedStatement(Statement *pStat);
	
	Statement** const GetStatList();
	Connector** const GetConnList();
	Statement** const GetSelectedStat();
	Statement**  GetCpdStat();
	Statement** GetUndoStatArray(int i);
	int GetUndoStatListsUsed();
	int GetUndoConnListsUsed();
	int GetStatCount();
	int GetConnCount();
	void IncrementStatCount();
	void DecrementStatCount();
	void IncrementConnCount();
	void DecrementConnCount();

	bool MultiplySelected(); //Is true when the first element in the SelectedStat array is not NULL

	void SaveFlowchart(ofstream &OutFile);
	void LoadFlowchart(ifstream &Infile);

	bool ValidateFlowchart(); //Is true when the flowchart is ready for simulation

	// -- Interface Management Functions
	Input *GetInput() const; //Return pointer to the input
	Output *GetOutput() const; //Return pointer to the output
	void UpdateInterface() const;	//Redraws all the drawing window
	
};

#endif