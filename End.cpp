#include "End.h"

End::End(Output* pOut, Point LP):Statement(pOut)
{
	Type=END;
	Text="End";
	LeftPoint=LP;
	pOut->GetEndPoints(LeftPoint,Text,Inlet);
}

End::End(const End &old):Statement(old.pOut)
{
	Text=old.Text;
	Type=old.Type;
	LeftPoint=old.LeftPoint;
	ID=old.numberofstatements;
	pOut=old.pOut;
	pOut->GetEndPoints(LeftPoint,Text,Inlet);
}

End::End(const End &old,Point p):Statement(old.pOut)
{
	Text=old.Text;
	Type=old.Type;
	LeftPoint=p;
	ID=old.numberofstatements;
	pOut=old.pOut;
	
}

void End::UpdateStatementText(){}

void End::setpConn(Connector *c){}

Point End::GetPoint()
{
	return LeftPoint;
}

Point End::GetInlet()
{
	return Inlet;
}

void End::Draw() const
{
	pOut->DrawStartEnd("End",LeftPoint,Selected);
}

void End::Save(ofstream &OutFile)
{
	OutFile<<"END\t"<<ID<<"\t"<<LeftPoint.x<<"\t"<<LeftPoint.y<<"\t\""<<Comment<<"\"\n";
}

void End::Load(ifstream &Infile)
{
	string str;
	getline(Infile,str);
	str+='\0';
	int LeftLimit,RightLimit=3;
	string StatInfo[4],tempstring="";
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
	pOut->GetEndPoints(LeftPoint,Text,Inlet);
}

void End::Move(Point P)
{
	LeftPoint=P;
	pOut->GetEndPoints(LeftPoint,Text,Inlet);
}

bool End::Edit(const string &str){return false;}

Statement* End::GenerateCode(ofstream &OutFile)
{
	if(!(OutFile.is_open()))
		OutFile.open("C++ code.txt",ios::out|ios::app);
	OutFile<<"\treturn 0;\n}";
	return NULL;
}

Statement* End::Simulate(bool StepByStep)
{
	for(int i=0;i<600;i++)
	{
		if(VariableList[i]!=NULL)
		{
			delete VariableList[i];
			VariableList[i]=NULL;
		}
		else
			break;
	}
	if(StepByStep==true)
		pOut->PrintMessage("Step by step run has ended.");
	return NULL;
}

void End::PrintInfo()
{
	if(Comment!="")
		pOut->PrintMessage("End Statement. \""+Comment+"\"");
	else
		pOut->PrintMessage("End Statement.");
}