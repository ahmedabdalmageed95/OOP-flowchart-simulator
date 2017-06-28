#include "Read.h"
#include <sstream>

Read::Read(Input* pIn, Output* pOut, Point Lcorner, string in):Statement(pOut)
{
	this->pIn=pIn;
	Type=READ;
	pConn=NULL;
	LeftCorner=Lcorner;
	input=in;
	UpdateStatementText();
}

Read::Read(const Read &old):Statement(old.pOut)
{
	Text=old.Text;
	Type=old.Type;
	LeftCorner=old.LeftCorner;
	input=old.input;
	ID=old.numberofstatements;
	pConn=old.pConn;
	pOut=old.pOut;
	UpdateStatementText();
}

Read::Read(const Read &old,Point p):Statement(old.pOut)
{
	Text=old.Text;
	Type=old.Type;
	LeftCorner=p;
	input=old.input;
	ID=old.numberofstatements;
	pConn=NULL;
	pOut=old.pOut;
}

void Read::setinput(const string &in)
{
	input=in;
	UpdateStatementText();
}

void Read::setpConn(Connector* c)
{
	pConn=c;
}

Point Read::GetInlet()
{
	return Inlet;
}

Point Read::GetOutlet()
{
	return Outlet;
}

Connector* Read::getpConn()
{
	return pConn;
}

void Read::Move(Point P)
{
	LeftCorner=P;
	pOut->GetIOPoints(LeftCorner,Text,Inlet,Outlet);
}

bool Read::Edit(const string &str)
{
	if(ValidateName(str))
	{
		input=str;
		UpdateStatementText();
		return true;
	}
	else
		return false;
}

void Read::UpdateStatementText()
{
	Text="Read "+input;
	pOut->GetIOPoints(LeftCorner,Text,Inlet,Outlet);
}

Point Read::GetPoint()
{
	return LeftCorner;
}

string Read::Getinput()
{
	return input;
}

void Read::Draw() const
{
	pOut->DrawIO(LeftCorner,"Read",input,Selected);
}

void Read::Save(ofstream &OutFile)
{
	OutFile<<"READ\t"<<ID<<"\t"<<LeftCorner.x<<"\t"<<LeftCorner.y<<"\t"<<input<<"\t\""<<Comment<<"\"\n";
}

void Read::Load(ifstream &Infile)
{
	string str;
	getline(Infile,str);
	str+='\0';
	int LeftLimit,RightLimit=4;
	string StatInfo[5],tempstring="";
	for(int i=0;i<5;i++)
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
	LeftCorner.x=(int) round(stod(StatInfo[1]));
	LeftCorner.y=(int) round(stod(StatInfo[2]));
	input=StatInfo[3];
	Comment=StatInfo[4];
	UpdateStatementText();
}

Statement* Read::GenerateCode(ofstream &OutFile)
{
	if(!(OutFile.is_open()))
		OutFile.open("C++ code.txt",ios::out|ios::app);
	OutFile<<"\t"<<"cin>>"<<input<<";\n";
	return pConn->getDstStat();
}

Statement* Read::Simulate(bool StepByStep)
{
	int position=-1;
	for(int i=0;i<600;i++)
	{
		if(VariableList[i]==NULL)
		{
			VariableList[i]=new Variable(input);
			position=i;
			break;
		}
		else if(VariableList[i]->getname()==input)
		{
			position=i;
			break;
		}
	}
	if(position<0)
		return NULL;
	pOut->PrintMessage("Enter the value of "+input);
	double value=pIn->GetValue(pOut);
	if(pIn->GetCancelDoubleValue())
	{
		pIn->InitializeCancelDoubleValue();
		return NULL;
	}
	VariableList[position]->setvalue(value);
	if(StepByStep)
	{
		ostringstream T;
		T<<input<<'='<<value;
		pOut->PrintMessage(T.str());
	}
	return pConn->getDstStat();
}

void Read::PrintInfo()
{
	if(Comment!="")
		pOut->PrintMessage("Read Statement. \""+Comment+"\"");
	else
		pOut->PrintMessage("Read Statement.");
}