#ifndef STATEMENT_H
#define STATEMENT_H

#include "..\defs.h"
#include "Connector.h"
//class Output;
#include "..\GUI\Output.h"

class Variable	//The variable in a program (type double)
{
	string name;	//Variable name
	double value;	//Variable value
	bool hasavalue;	//True when the variable is initialized
public:
	Variable(string n);
	void setname(string n);
	void setvalue(double v);
	string getname();
	double getvalue();
	bool hasvalue();
};

//Base class for all Statements
class Statement
{
protected:
	int ID;			//Each Statement has an ID
	string Text;	//Statement text (e.g.  "X = 5" OR "if(salary > 3000)" and so on )
	string Comment; //Statement comment
	bool Selected;	//true if the statement is selected on the folwchart
	Output* pOut;	//pointer to Output
	StatementType Type;	//Statement type

	static int numberofstatements;
	static Variable* VariableList[600];	//Used in simulation

	virtual void UpdateStatementText() = 0;	//is called when any part of the stat. is edited	
	bool ValidateName(const string &str);	//Returns true if the passed string is a legal variable name
	bool ValidateNumber(const string &str);	//Returns true if the passed string is a double number

public:
	Statement(Output *pOut);
	~Statement();
	void SetSelected(bool s);
	bool IsSelected() const;
	void SetComment(string c);
	int getID();
	string GetText();
	StatementType GetType();
	virtual void setpConn(Connector* c)=0;
	virtual Point GetPoint()=0;
	static void InitializeVariableList();
	void ResetVariableList();


	virtual void Draw() const  = 0 ;	//Draw the statement
	virtual void Save(ofstream &OutFile) = 0;	//Save the Statement parameters to a file
	virtual void Load(ifstream &Infile) = 0;	//Load the Statement parameters from a file
	virtual void Move(Point P) = 0;		//Move the Statement on the flowchart
	virtual bool Edit(const string &str) = 0;		//Edit the Statement parameter
	virtual Statement* GenerateCode(ofstream &OutFile) = 0;	//write the statement code to a file
	virtual Statement* Simulate(bool StepByStep=false) = 0;	//Execute the statement in the simulation mode
	virtual void PrintInfo() = 0;	//print all Statement info on the status bar
};

#endif