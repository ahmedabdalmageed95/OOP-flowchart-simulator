#ifndef SNGL_OP_ASSIGN_H
#define SNGL_OP_ASSIGN_H

#include "Statement.h"

class SnglOpAssign : public Statement
{
private:
	string LHS;	//Left Handside of the assignment (name of a variable)
	string opLHS;	//Left Handside of operator
	string op;		//Operator
	string opRHS;	//Right Handside of operator
	
	Connector *pConn;	//Variable Assignment Stat. has one Connector to next statement

	Point Inlet;	//A point where connections enters this statement 
	Point Outlet;	//A point a connection leaves this statement

	Point LeftCorner;	//left corenr of the statement block.

	virtual void UpdateStatementText();
public:
	SnglOpAssign(Output* pOut, Point Lcorner, string LeftHS="", string opLeftHS="", string oprtr="", string opRightHS="");
	SnglOpAssign(const SnglOpAssign &old);
	SnglOpAssign(const SnglOpAssign &old,Point p);
	
	void setLHS(const string &L);
	void setopLHS(const string &opL);
	void setop(const string &oprtr);
	void setopRHS(const string &opR);
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