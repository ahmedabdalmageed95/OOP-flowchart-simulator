#ifndef CONNECTOR_H
#define CONNECTOR_H

#include "..\GUI\UI_Info.h"
#include "..\GUI\output.h"
class Statement;
class ApplicationManager;
class Connector	//a connector that connects two statements (Source & Destination)
{
private:
	Statement *SrcStat;	//The source statement of the connector
	Statement *DstStat;	//The destination statement of the connector
	Point start;	//Start point of the connector
	Point end;		//End point of the connector
	ApplicationManager* pManager;
	bool* CondValue;
public:
	Connector(Statement* Src, Statement* Dst, ApplicationManager* pAppManager, bool Cond=true);
	Connector(const Connector& Conn);
	~Connector();

	void		setSrcStat(Statement *Src);
	Statement*	getSrcStat();	
	void		setDstStat(Statement *Dst);
	Statement*	getDstStat();
	void setCondValue(bool Cond);
	bool* getCondValue();

	void setStartPoint(Point P);
	Point getStartPoint();

	void setEndPoint(Point P);
	Point getEndPoint();

	void Draw(Output* pOut);

	void Save(ofstream &OutFile);
	void Load(ifstream &Infile);

};

#endif