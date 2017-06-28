#ifndef COND_H
#define COND_H

#include "Statement.h"

enum ConditionalType
{
	WHILE,
	WHILE_NOT,
	IF
};

class Conditional : public Statement
{
private:
	string LHS,op,RHS;
	Connector *pYesConn,*pNoConn;
	Point Inlet,YesOutlet,NoOutlet,LeftPoint;
	virtual void UpdateStatementText();
	Statement* CalculateFinishStat(Statement* pStat1, Statement* pStat2);
public:
	Conditional(Output* pOut, Point LP, string LeftHS="", string oprtr="==", string RightHS="");
	Conditional(const Conditional &old);
	Conditional(const Conditional &old,Point p);
	void setLHS(const string &L);
	void setop(const string &oprtr);
	void setRHS(const string &R);
	void setpConn(Connector* c);
	void makepYesConnNull();
	void makepNoConnNull();
	virtual Point GetPoint();
	Point GetInlet();
	Point getYesOutlet();
	Point getNoOutlet();
	Connector* getpConn(bool CondValue);
	int getWidth();
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