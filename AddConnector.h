#ifndef ADD_CONN_H
#define ADD_CONN_H

#include "Action.h"
#include "..\Statements\Connector.h"

class AddConnector : public Action
{
private:
	Point Position1,Position2;
	Statement *SrcStat,*DstStat;
	string str;
	char cond;
public:
	AddConnector(ApplicationManager *pAppManager);


	virtual void ReadActionParameters();
	

	virtual void Execute() ;
	
};

#endif