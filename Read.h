#ifndef READ_H
#define READ_H

#include "Statement.h"

class Read : public Statement
{
private:
	Input* pIn;
	string input;
	Connector *pConn;
	Point Inlet;
	Point Outlet;
	Point LeftCorner;
	virtual void UpdateStatementText();
public:
	Read(Input* pIn, Output* pOut, Point Lcorner, string in="");
	Read(const Read &old);
	Read(const Read &old,Point p);
	void setinput(const string &in);
	void setpConn(Connector* c);
	virtual Point GetPoint();
	string Getinput();
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