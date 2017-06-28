#include "Write.h"

Write::Write(Output* pOut, Point Lcorner, string out):Statement(pOut)
{
	Type=WRITE;
	pConn=NULL;
	LeftCorner=Lcorner;
	output=out;
	UpdateStatementText();
}

Write::Write(const Write &old):Statement(old.pOut)
{
	Text=old.Text;
	Type=old.Type;
	Selected=old.Selected;
	ID=old.numberofstatements;
	pConn=old.pConn;
	LeftCorner=old.LeftCorner;
	output=old.output;
	pOut=old.pOut;
	UpdateStatementText();
}

Write::Write(const Write &old,Point p):Statement(old.pOut)
{
	Text=old.Text;
	Type=old.Type;
	Selected=old.Selected;
	ID=old.numberofstatements;
	pConn=NULL;
	LeftCorner=p;
	output=old.output;
	pOut=old.pOut;
}

void Write::setoutput(const string &out)
{
	output=out;
	UpdateStatementText();
}

void Write::setpConn(Connector* c)
{
	pConn=c;
}

Point Write::GetInlet()
{
	return Inlet;
}

Point Write::GetOutlet()
{
	return Outlet;
}

Connector* Write::getpConn()
{
	return pConn;
}

void Write::Move(Point P)
{
	LeftCorner=P;
	pOut->GetIOPoints(LeftCorner,Text,Inlet,Outlet);
}

bool Write::Edit(const string &str)
{
	if(ValidateName(str)||ValidateNumber(str))
	{
		output=str;
		UpdateStatementText();
		return true;
	}
	else
		return false;
}

void Write::UpdateStatementText()
{
	Text="Write "+output;
	pOut->GetIOPoints(LeftCorner,Text,Inlet,Outlet);
}

Point Write::GetPoint()
{
	return LeftCorner;
}

void Write::Draw() const
{
	pOut->DrawIO(LeftCorner,"Write",output,Selected);
}

void Write::Save(ofstream &OutFile)
{
	OutFile<<"WRITE\t"<<ID<<"\t"<<LeftCorner.x<<"\t"<<LeftCorner.y<<"\t"<<output<<"\t\""<<Comment<<"\"\n";
}

void Write::Load(ifstream &Infile)
{
	string str;
	getline(Infile,str);
	str+='\0';
	int LeftLimit,RightLimit=5;
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
	output=StatInfo[3];
	Comment=StatInfo[4];
	UpdateStatementText();
}

Statement* Write::GenerateCode(ofstream &OutFile)
{
	if(!(OutFile.is_open()))
		OutFile.open("C++ code.txt",ios::out|ios::app);
	OutFile<<"\t"<<"cout<<"<<output<<";\n";
	return pConn->getDstStat();
}

Statement* Write::Simulate(bool StepByStep)
{
	if(ValidateNumber(output))
	{
		pOut->PrintMessage(output);
		return pConn->getDstStat();
	}
	else if(ValidateName(output))
	{
		for(int i=0;i<600;i++)
		{
			if(VariableList[i]!=NULL)
			{
				if(VariableList[i]->getname()==output)
				{
					if(!(VariableList[i]->hasvalue()))
						return NULL;
					else
					{
						pOut->ClearStatusBar();
						pOut->PrintDouble(VariableList[i]->getvalue());
						return pConn->getDstStat();
					}
				}
			}
			else
				return NULL;
		}
	}
	else
		return NULL;
	return NULL;
}

void Write::PrintInfo()
{
	if(Comment!="")
		pOut->PrintMessage("Write Statement. \""+Comment+"\"");
	else
		pOut->PrintMessage("Write Statement.");
}