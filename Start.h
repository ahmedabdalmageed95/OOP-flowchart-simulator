#ifndef START_H
#define START_H

#include "Statement.h"

class Start : public Statement
{
private:
	Connector *pConn;
	Point Outlet;
	Point LeftPoint;
	virtual void UpdateStatementText();
public:
	Start(Output* pOut, Point LP);
	Start(const Start &old);
	Start(const Start &old, Point p);
	void setpConn(Connector* c);
	virtual Point GetPoint();
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