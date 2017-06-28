#include "Connector.h"
#include "..\ApplicationManager.h"
#include "Statement.h"
#include "SmplAssign.h"
#include "VarAssign.h"
#include "SnglOpAssign.h"
#include "Conditional.h"
#include "Read.h"
#include "Write.h"
#include "Start.h"
#include "End.h"

Connector::Connector(Statement* Src, Statement* Dst, ApplicationManager* pAppManager, bool Cond)	
//When a connector is created, it must have a source statement and a destination statement
//There are no free connectors in the folwchart
{
	SrcStat = Src;
	DstStat = Dst;
	pManager=pAppManager;
	CondValue=NULL;
	if(SrcStat->GetType()==COND)
	{
		CondValue=new bool;
		*CondValue=Cond;
	}
}

Connector::Connector(const Connector& Conn)
{
	if(Conn.SrcStat->GetType()==SMPL_ASSIGN)
		SrcStat=new SmplAssign(*(SmplAssign*)Conn.SrcStat);
	if(Conn.SrcStat->GetType()==VAR_ASSIGN)
		SrcStat=new VarAssign(*(VarAssign*)Conn.SrcStat);
	if(Conn.SrcStat->GetType()==SNGL_OP_ASSIGN)
		SrcStat=new SnglOpAssign(*(SnglOpAssign*)Conn.SrcStat);
	if(Conn.SrcStat->GetType()==COND)
		SrcStat=new Conditional(*(Conditional*)Conn.SrcStat);
	if(Conn.SrcStat->GetType()==READ)
		SrcStat=new Read(*(Read*)Conn.SrcStat);
	if(Conn.SrcStat->GetType()==WRITE)
		SrcStat=new Write(*(Write*)Conn.SrcStat);
	if(Conn.SrcStat->GetType()==START)
		SrcStat=new Start(*(Start*)Conn.SrcStat);
	if(Conn.DstStat->GetType()==SMPL_ASSIGN)
		DstStat=new SmplAssign(*(SmplAssign*)Conn.DstStat);
	if(Conn.DstStat->GetType()==VAR_ASSIGN)
		DstStat=new VarAssign(*(VarAssign*)Conn.DstStat);
	if(Conn.DstStat->GetType()==SNGL_OP_ASSIGN)
		DstStat=new SnglOpAssign(*(SnglOpAssign*)Conn.DstStat);
	if(Conn.DstStat->GetType()==COND)
		DstStat=new Conditional(*(Conditional*)Conn.DstStat);
	if(Conn.DstStat->GetType()==READ)
		DstStat=new Read(*(Read*)Conn.DstStat);
	if(Conn.DstStat->GetType()==WRITE)
		DstStat=new Write(*(Write*)Conn.DstStat);
	if(Conn.DstStat->GetType()==END)
		DstStat=new End(*(End*)Conn.DstStat);
	start=Conn.start;
	end=Conn.end;
	pManager=Conn.pManager;
	CondValue=new bool;
	if(Conn.CondValue!=NULL)
		*CondValue=*Conn.CondValue;
}

Connector::~Connector()
{
	if(SrcStat->GetType()==COND)
		delete CondValue;
}

void Connector::setSrcStat(Statement *Src)
{	SrcStat = Src;	}

Statement* Connector::getSrcStat()
{	return SrcStat;	}

void Connector::setDstStat(Statement *Dst)
{	DstStat = Dst;	}

Statement* Connector::getDstStat()
{	return DstStat;	}

void Connector::setCondValue(bool Cond)
{
	if(CondValue==NULL)
		CondValue=new bool;
	*CondValue=Cond;
}

bool* Connector::getCondValue()
{return CondValue;}


void Connector::setStartPoint(Point P)
{	start = P;	}

Point Connector::getStartPoint()
{	return start;	}

void Connector::setEndPoint(Point P)
{	end = P;	}

Point Connector::getEndPoint()
{	return end;	}

void Connector::Draw(Output* pOut)
{
	
	if (dynamic_cast <SmplAssign*>(SrcStat))
	{
	 start=dynamic_cast <SmplAssign*>(SrcStat)->GetOutlet();
	}

	else{
		if (dynamic_cast <SnglOpAssign*>(SrcStat))
		{
		start=dynamic_cast <SnglOpAssign*>(SrcStat)->GetOutlet();
		}
	

	else{
		if (dynamic_cast <VarAssign*>(SrcStat))
		{
		start=dynamic_cast <VarAssign*>(SrcStat)->GetOutlet();
		}
		else{
		if (dynamic_cast <Start*>(SrcStat))
		{
		start=dynamic_cast <Start*>(SrcStat)->GetOutlet();
		}
		else{
		if (dynamic_cast <Read*>(SrcStat))
		{
		start=dynamic_cast <Read*>(SrcStat)->GetOutlet();
		}
		else{
		if (dynamic_cast <Write*>(SrcStat))
		{
		start=dynamic_cast <Write*>(SrcStat)->GetOutlet();
		}

else{
		if (dynamic_cast <Conditional*>(SrcStat))
		{
			if(*CondValue==true)
				start=dynamic_cast <Conditional*>(SrcStat)->getYesOutlet();
			else
				start=dynamic_cast <Conditional*>(SrcStat)->getNoOutlet();
		}
	}

	}

	}

	}

	}

	}

	if (dynamic_cast <SmplAssign*>(DstStat))
	{
	 end=dynamic_cast <SmplAssign*>(DstStat)->GetInlet();
	}

	else{
		if (dynamic_cast <SnglOpAssign*>(DstStat))
		{
		end=dynamic_cast <SnglOpAssign*>(DstStat)->GetInlet();
		}
	

	else{
		if (dynamic_cast <VarAssign*>(DstStat))
		{
		end=dynamic_cast <VarAssign*>(DstStat)->GetInlet();
		}
		else{
		if (dynamic_cast <End*>(DstStat))
		{
		end=dynamic_cast <End*>(DstStat)->GetInlet();
		}
		else{
		if (dynamic_cast <Read*>(DstStat))
		{
		end=dynamic_cast <Read*>(DstStat)->GetInlet();
		}
		else{
		if (dynamic_cast <Write*>(DstStat))
		{
		end=dynamic_cast <Write*>(DstStat)->GetInlet();
		}
		
		
else{
		if (dynamic_cast <Conditional*>(DstStat))
		{
		end=dynamic_cast <Conditional*>(DstStat)->GetInlet();
		}
	}

	}

	}

	}

	}

	}
	pOut->DrawConnector(start,end);
	
}

void Connector::Save(ofstream &OutFile)
{
	OutFile<<SrcStat->getID()<<"\t"<<DstStat->getID()<<"\t";
	if (SrcStat->GetType()==COND)
	{
		if(*CondValue==true)
			OutFile<<"1";
		else
			OutFile<<"2";
	}
	else
		OutFile<<"0";
	OutFile<<"\n";
}

void Connector::Load(ifstream &Infile)
{
	string str;
	getline(Infile,str);
	str+='\0';
	int LeftLimit,RightLimit=-1;
	string ConnInfo[3],tempstring;
	for(int i=0;i<3;i++)
	{
		tempstring="";
		LeftLimit=RightLimit;
		for(int j=LeftLimit+1;1;j++)
		{
			if(str[j]=='\t'||str[j]=='\0')
			{
				RightLimit=j;
				break;
			}
		}
		for(int j=LeftLimit+1;j<RightLimit;j++)
			tempstring+=str[j];
		ConnInfo[i]=tempstring;
	}
	int SrcID=(int) round(stod(ConnInfo[0])),DstID=(int) round(stod(ConnInfo[1])),Cond=(int) round(stod(ConnInfo[2]));
	if(Cond==1)
	{
		if(CondValue==NULL)
			CondValue=new bool;
		*CondValue=true;
	}
	else if(Cond==2)
	{
		if(CondValue==NULL)
			CondValue=new bool;
		*CondValue=false;
	}
	for(int i=0;i<pManager->GetStatCount();i++)
	{
		if(pManager->GetStatList()[i]->getID()==SrcID)
		{
			SrcStat=pManager->GetStatList()[i];
			SrcStat->setpConn(this);
			break;
		}
	}
	for(int i=0;i<pManager->GetStatCount();i++)
	{
		if(pManager->GetStatList()[i]->getID()==DstID)
		{
			DstStat=pManager->GetStatList()[i];
			break;
		}
	}
}