#include "SmplAssign.h"
#include <sstream>

using namespace std;

SmplAssign::SmplAssign(Output* pOut, Point Lcorner, string LeftHS, double RightHS):Statement(pOut)
{
	Type=SMPL_ASSIGN;
	LeftCorner = Lcorner;
	LHS = LeftHS;
	RHS = RightHS;

	UpdateStatementText();

	pOut->GetAssignPoints(LeftCorner,Text,Inlet,Outlet);
	
	pConn = NULL;	//No connectors yet
}

SmplAssign::SmplAssign(const SmplAssign &old):Statement(old.pOut)
{
	Text=old.Text;
	Type=old.Type;
	LeftCorner=old.LeftCorner;
	LHS=old.LHS;
	RHS=old.RHS;
	pConn=old.pConn;
	ID=old.numberofstatements;
	pOut=old.pOut;
	UpdateStatementText();
}

SmplAssign::SmplAssign(const SmplAssign &old,Point p):Statement(old.pOut)
{
	Text=old.Text;
	Type=old.Type;
	LeftCorner=p;
	LHS=old.LHS;
	RHS=old.RHS;
	pConn=NULL;
	ID=old.numberofstatements;
	pOut=old.pOut;
}

void SmplAssign::setLHS(const string &L)
{
	LHS = L;
	UpdateStatementText();
}

void SmplAssign::setRHS(double R)
{
	RHS = R;
	UpdateStatementText();
}

void SmplAssign::setpConn(Connector* c)
{
	pConn=c;
}

Point SmplAssign::GetPoint()
{
	return LeftCorner;
}

string SmplAssign::GetLHS()
{
	return LHS;
}

Point SmplAssign::GetInlet()
{
	return Inlet;
}

Point SmplAssign::GetOutlet()
{
	return Outlet;
}

Connector* SmplAssign::getpConn()
{
	return pConn;
}

void SmplAssign::Draw() const
{
	//Call Output::DrawAssign function to draw assignment statement 	
	pOut->DrawAssign(LeftCorner, Text, Selected);
}


//This function should be called when LHS or RHS changes
void SmplAssign::UpdateStatementText()
{
	if(LHS=="")	//No left handside ==>statement have no valid text yet
		Text = " = ";
	else
	{
		//Build the statement text: Left handside then equals then right handside
		ostringstream T;
		T<<LHS<<" = "<<RHS;	
		Text = T.str();	 
	}
	pOut->GetAssignPoints(LeftCorner,Text,Inlet,Outlet);
}

void SmplAssign::Save(ofstream &OutFile)
{
	OutFile<<"SMPL\t"<<ID<<"\t"<<LeftCorner.x<<"\t"<<LeftCorner.y<<"\t"<<LHS<<"\t"<<RHS<<"\t\""<<Comment<<"\"\n";
}

void SmplAssign::Load(ifstream &Infile)
{
	string str;
	getline(Infile,str);
	str+='\0';
	int LeftLimit,RightLimit=4;
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
	RHS=stod(StatInfo[4]);
	Comment=StatInfo[5];
	UpdateStatementText();
}

void SmplAssign::Move(Point P)
{
	LeftCorner=P;
	pOut->GetAssignPoints(LeftCorner,Text,Inlet,Outlet);
}

bool SmplAssign::Edit(const string &str)
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
	bool LHSvalidation=ValidateName(L),RHSvalidation=ValidateNumber(R);
	if(LHSvalidation&&RHSvalidation)
	{
		LHS=L;
		RHS=stod(R);
		UpdateStatementText();
		return true;
	}
	else
		return false;
}



Statement* SmplAssign::GenerateCode(ofstream &OutFile)
{
	if(!(OutFile.is_open()))
		OutFile.open("C++ code.txt",ios::out|ios::app);
	OutFile<<"\t"<<LHS<<"="<<RHS<<";\n";
	return pConn->getDstStat();
}

Statement* SmplAssign::Simulate(bool StepByStep)
{
	for(int i=0;i<600;i++)
	{
		if(VariableList[i]==NULL)
		{
			VariableList[i]=new Variable(LHS);
			VariableList[i]->setvalue(RHS);
			if(StepByStep)
				pOut->PrintMessage(Text);
			return pConn->getDstStat();
		}
		else if(VariableList[i]->getname()==LHS)
		{
			VariableList[i]->setvalue(RHS);
			if(StepByStep)
				pOut->PrintMessage(Text);
			return pConn->getDstStat();
		}
	}
	return NULL;
}

void SmplAssign::PrintInfo()
{
	if(Comment!="")
		pOut->PrintMessage("Simple Assignment Statement. \""+Comment+"\"");
	else
		pOut->PrintMessage("Simple Assignment Statement.");
}