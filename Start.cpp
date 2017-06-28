#include "Start.h"

Start::Start(Output* pOut, Point LP):Statement(pOut)
{
	Type=START;
	Text="Start";
	LeftPoint=LP;
	pOut->GetStartPoints(LeftPoint,Text,Outlet);
	pConn=NULL;
}

Start::Start(const Start &old):Statement(old.pOut)
{
	Text=old.Text;
	Type=old.Type;
	ID=old.numberofstatements;
	pConn=old.pConn;
	LeftPoint=old.LeftPoint;
	pOut=old.pOut;
	pOut->GetStartPoints(LeftPoint,Text,Outlet);
}

Start::Start(const Start &old, Point p):Statement(old.pOut)
{
	Text=old.Text;
	Type=old.Type;
	ID=old.numberofstatements;
	pConn=NULL;
	LeftPoint=p;
	pOut=old.pOut;
}

void Start::UpdateStatementText(){}

void Start::setpConn(Connector* c)
{
	pConn=c;
}

Point Start::GetPoint()
{
	return LeftPoint;
}

Point Start::GetOutlet()
{
	return Outlet;
}

Connector* Start::getpConn()
{
	return pConn;
}

void Start::Draw() const
{
	pOut->DrawStartEnd("Start",LeftPoint,Selected);
}

void Start::Save(ofstream &OutFile)
{
	OutFile<<"STRT\t"<<ID<<"\t"<<LeftPoint.x<<"\t"<<LeftPoint.y<<"\t\""<<Comment<<"\"\n";
}

void Start::Load(ifstream &Infile)
{
	string str;
	getline(Infile,str);
	str+='\0';
	int LeftLimit,RightLimit=4;
	string StatInfo[4],tempstring;
	for(int i=0;i<4;i++)
	{
		tempstring="";
		LeftLimit=RightLimit;
		if(str[LeftLimit+1]=='\"')
			LeftLimit++;
		for(int j=LeftLimit+1;1;j++)
		{
			if(str[j]=='\t'||str[j]=='\0')
			{
				RightLimit=j;
				if(str[RightLimit-1]=='\"')
					RightLimit--;
				break;
			}
		}
		for(int j=LeftLimit+1;j<RightLimit;j++)
			tempstring+=str[j];
		StatInfo[i]=tempstring;
	}
	ID=(int) round(stod(StatInfo[0]));
	LeftPoint.x=(int) round(stod(StatInfo[1]));
	LeftPoint.y=(int) round(stod(StatInfo[2]));
	Comment=StatInfo[3];
	pOut->GetStartPoints(LeftPoint,Text,Outlet);
}

void Start::Move(Point P)
{
	LeftPoint=P;
	pOut->GetStartPoints(LeftPoint,Text,Outlet);
}

bool Start::Edit(const string &str){return false;}

Statement* Start::GenerateCode(ofstream &OutFile)
{
	return pConn->getDstStat();
}

Statement* Start::Simulate(bool StepByStep)
{
	return pConn->getDstStat();
}

void Start::PrintInfo()
{
	if(Comment!="")
		pOut->PrintMessage("Start Statement. \""+Comment+"\"");
	else
		pOut->PrintMessage("Start Statement.");
}