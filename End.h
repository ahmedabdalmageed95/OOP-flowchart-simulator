#ifndef END_H
#define END_H

#include "Statement.h"

class End : public Statement
{
private:
	Point Inlet;
	Point LeftPoint;
	virtual void UpdateStatementText();
public:
	End(Output* pOut, Point LP);
	End(const End &old);
	End(const End &old, Point p);
	void setpConn(Connector* c);
	virtual Point GetPoint();
	Point GetInlet();
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