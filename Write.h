#ifndef WRITE_H
#define WRITE_H

#include "Statement.h"

class Write : public Statement
{
private:
	string output;
	Connector *pConn;
	Point Inlet;
	Point Outlet;
	Point LeftCorner;
	virtual void UpdateStatementText();
public:
	Write(Output* pOut, Point Lcorner, string out="");
	Write(const Write &old);
	Write(const Write &old,Point p);
	void setoutput(const string &out);
	void setpConn(Connector* c);
	virtual Point GetPoint();
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