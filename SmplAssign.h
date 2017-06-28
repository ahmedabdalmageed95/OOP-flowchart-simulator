#ifndef SMPL_ASSIGN_H
#define SMPL_ASSIGN_H

#include "Statement.h"

//Simple Assignment statement class
//The simple assignment statement assigns a variable to a value 
class SmplAssign : public Statement
{
private:
	string LHS;	//Left Handside of the assignment (name of a variable)
	double RHS;	//Right Handside (Value)
	
	Connector *pConn;	//Simple Assignment Stat. has one Connector to next statement

	Point Inlet;	//A point where connections enters this statement 
	Point Outlet;	//A point a connection leaves this statement

	Point LeftCorner;	//left corenr of the statement block.

	virtual void UpdateStatementText();
	
public:
	SmplAssign(Output* pOut, Point Lcorner, string LeftHS="", double RightHS=0);
	SmplAssign(const SmplAssign &old);
	SmplAssign(const SmplAssign &old, Point p);
	
	void setLHS(const string &L);
	void setRHS(double R);
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