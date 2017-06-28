#ifndef VAR_ASSIGN_H
#define VAR_ASSIGN_H

#include "Statement.h"

//Variable Assignment statement class
//The variable assignment statement assigns a variable to the value of another variable
class VarAssign : public Statement
{
private:
	string LHS;	//Left Handside of the assignment (name of a variable)
	string RHS;	//Right Handside (name of a variable)
	
	Connector *pConn;	//Variable Assignment Stat. has one Connector to next statement

	Point Inlet;	//A point where connections enters this statement 
	Point Outlet;	//A point a connection leaves this statement

	Point LeftCorner;	//left corenr of the statement block.

	virtual void UpdateStatementText();
	
public:
	VarAssign(Output* pOut, Point Lcorner, string LeftHS="", string RightHS="");
	VarAssign(const VarAssign &old);
	VarAssign(const VarAssign &old,Point p);
	
	void setLHS(const string &L);
	void setRHS(const string &R);
	void setpConn(Connector* c);

	virtual Point GetPoint();
	string GetLHS();
	Point GetInlet();
	Point GetOutlet();
	Connector* getpConn();

	virtual void Draw() const;
	virtual void Save(ofstream &OutFile);
	virtual void Load(ifstream &Infile);
	virtual void Move(Point P);
	virtual bool Edit(const string &str);
	virtual Statement* GenerateCode(ofstream &OutFile);
	virtual Statement* Simulate(bool StepByStep=false);
	virtual void PrintInfo();
};

#endif