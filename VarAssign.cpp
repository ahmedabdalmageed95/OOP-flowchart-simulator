#include "VarAssign.h"
#include <sstream>

VarAssign::VarAssign(Output* pOut, Point Lcorner, string LeftHS, string RightHS):Statement(pOut)
{
	Type=VAR_ASSIGN;
	LeftCorner = Lcorner;
	LHS = LeftHS;
	RHS = RightHS;

	UpdateStatementText();
	
	pConn = NULL;	//No connectors yet
}

VarAssign::VarAssign(const VarAssign &old):Statement(old.pOut)
{
	Text=old.Text;
	Type=old.Type;
	Selected=old.Selected;
	ID=old.numberofstatements;
	LHS=old.LHS;
	LeftCorner=old.LeftCorner;
	pConn = old.pConn;
	pOut=old.pOut;
	UpdateStatementText();
}

VarAssign::VarAssign(const VarAssign &old,Point p):Statement(old.pOut)
{
	Text=old.Text;
	Type=old.Type;
	Selected=old.Selected;
	ID=old.numberofstatements;
	LHS=old.LHS;
	LeftCorner=p;
	pConn = NULL;
	pOut=old.pOut;
}

void VarAssign::UpdateStatementText()
{
	if(LHS==""||RHS=="")
		Text=" = ";
	else
		Text=LHS+" = "+RHS;
	pOut->GetAssignPoints(LeftCorner,Text,Inlet,Outlet);
}

void VarAssign::setLHS(const string &L)
{
	LHS = L;
	UpdateStatementText();
}

void VarAssign::setRHS(const string &R)
{
	RHS = R;
	UpdateStatementText();
}

void VarAssign::setpConn(Connector* c)
{
	pConn=c;
}

Point VarAssign::GetPoint()
{
	return LeftCorner;
}

string VarAssign::GetLHS()
{
	return LHS;
}

Point VarAssign::GetInlet()
{
	return Inlet;
}

Point VarAssign::GetOutlet()
{
	return Outlet;
}

Connector* VarAssign::getpConn()
{
	return pConn;
}

void VarAssign::Draw() const
{
	pOut->DrawAssign(LeftCorner,Text,Selected);
}

void VarAssign::Save(ofstream &OutFile)
{
	OutFile<<"VAR\t"<<ID<<"\t"<<LeftCorner.x<<"\t"<<LeftCorner.y<<"\t"<<LHS<<"\t"<<RHS<<"\t\""<<Comment<<"\"\n";
}

void VarAssign::Load(ifstream &Infile)
{
	string str;
	getline(Infile,str);
	str+='\0';
	int LeftLimit,RightLimit=3;
	string StatInfo[6],tempstring="";
	for(int i=0;i<6;i++)
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
	LHS=StatInfo[3];
	RHS=StatInfo[4];
	Comment=StatInfo[5];
	UpdateStatementText();
}

void VarAssign::Move(Point P)
{
	LeftCorner=P;
	pOut->GetAssignPoints(LeftCorner,Text,Inlet,Outlet);
}

bool VarAssign::Edit(const string &str)
{
	if(str[0]=='='||str[0]=='\0')	//if the string is empty or the first character is the equal sign
		return false;
	int numberofequalsigns=0,i=0,equalsignposition,stringsize;
	while(1)
	{
		if(str[i]=='=')
		{
			numberofequalsigns++;
			equalsignposition=i;
			if(str[i+1]=='\0')	//no RHS
				return false;
		}
		if(numberofequalsigns>1)
			return false;
		if(str[i]=='\0')
		{
			stringsize=i-1;
			break;
		}
		i++;
	}
	if(numberofequalsigns==0)
		return false;
	string L="",R="";
	for(i=0;i<equalsignposition;i++)
		L+=str[i];
	for(i=equalsignposition+1;i<=stringsize;i++)
		R+=str[i];
	bool LHSvalidation=ValidateName(L),RHSvalidation=ValidateName(R);
	if(LHSvalidation&&RHSvalidation)
	{
		LHS=L;
		RHS=R;
		UpdateStatementText();
		return true;
	}
	else
		return false;
}

Statement* VarAssign::GenerateCode(ofstream &OutFile)
{
	if(!(OutFile.is_open()))
		OutFile.open("C++ code.txt",ios::out|ios::app);
	OutFile<<"\t"<<LHS<<"="<<RHS<<";\n";
	return pConn->getDstStat();
}

Statement* VarAssign::Simulate(bool StepByStep)
{
	double temp;
	for(int i=0;i<600;i++)
	{
		if(VariableList[i]!=NULL)
		{
			if(VariableList[i]->getname()==RHS)
			{
				if(!(VariableList[i]->hasvalue()))
					return NULL;
				else
				{
					temp=VariableList[i]->getvalue();
					break;
				}
			}
		}
		else
			return NULL;
	}
	for(int i=0;i<600;i++)
	{
		if(VariableList[i]==NULL)
		{
			VariableList[i]=new Variable(LHS);
			VariableList[i]->setvalue(temp);
			if(StepByStep)
			{
				ostringstream T;
				T<<LHS<<" = "<<temp;
				pOut->PrintMessage(T.str());
			}
			return pConn->getDstStat();
		}
		else if(VariableList[i]->getname()==LHS)
		{
			VariableList[i]->setvalue(temp);
			if(StepByStep)
			{
				ostringstream T;
				T<<LHS<<" = "<<temp;
				pOut->PrintMessage(T.str());
			}
			return pConn->getDstStat();
		}
	}
	return NULL;
}

void VarAssign::PrintInfo()
{
	if(Comment!="")
		pOut->PrintMessage("Variable Assignment Statement. \""+Comment+"\"");
	else
		pOut->PrintMessage("Variable Assignment Statement.");
}