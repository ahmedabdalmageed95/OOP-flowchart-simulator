#include "SnglOpAssign.h"
#include <sstream>

SnglOpAssign::SnglOpAssign(Output* pOut, Point Lcorner, string LeftHS, string opLeftHS, string oprtr, string opRightHS):Statement(pOut)
{
	Type=SNGL_OP_ASSIGN;
	LeftCorner = Lcorner;
	LHS = LeftHS;
	opLHS=opLeftHS;
	op=oprtr;
	opRHS=opRightHS;

	UpdateStatementText();
	
	pConn = NULL;	//No connectors yet
}

SnglOpAssign::SnglOpAssign(const SnglOpAssign &old):Statement(old.pOut)
{
	Text=old.Text;
	Type=old.Type;
	LeftCorner= old.LeftCorner;
	LHS=old.LHS;
	op=old.op;
	opRHS=old.opRHS;
	pConn=old.pConn;
	ID=old.numberofstatements;
	pOut=old.pOut;
	UpdateStatementText();
}

SnglOpAssign::SnglOpAssign(const SnglOpAssign &old,Point p):Statement(old.pOut)
{
	Text=old.Text;
	Type=old.Type;
	LeftCorner= p;
	LHS=old.LHS;
	op=old.op;
	opRHS=old.opRHS;
	pConn=NULL;
	ID=old.numberofstatements;
	pOut=old.pOut;
}

void SnglOpAssign::UpdateStatementText()
{
	if(LHS==""||opLHS==""||opRHS==""||!(op=="+"||op=="-"||op=="*"||op=="/"))
		Text=" = ";
	else
		Text=LHS+" = "+opLHS+" "+op+" "+opRHS;
	pOut->GetAssignPoints(LeftCorner,Text,Inlet,Outlet);
}

void SnglOpAssign::setLHS(const string &L)
{
	LHS = L;
	UpdateStatementText();
}

void SnglOpAssign::setopLHS(const string &opL)
{
	opLHS = opL;
	UpdateStatementText();
}

void SnglOpAssign::setop(const string &oprtr)
{
	op = oprtr;
	UpdateStatementText();
}

void SnglOpAssign::setopRHS(const string &opR)
{
	opRHS = opR;
	UpdateStatementText();
}

void SnglOpAssign::setpConn(Connector* c)
{
	pConn=c;
}

Point SnglOpAssign::GetPoint()
{
	return LeftCorner;
}

string SnglOpAssign::GetLHS()
{
	return LHS;
}

Point SnglOpAssign::GetInlet()
{
	return Inlet;
}

Point SnglOpAssign::GetOutlet()
{
	return Outlet;
}

Connector* SnglOpAssign::getpConn()
{
	return pConn;
}

void SnglOpAssign::Draw() const
{
	pOut->DrawAssign(LeftCorner,Text,Selected);
}

void SnglOpAssign::Save(ofstream &OutFile)
{
	OutFile<<"SNGLOP\t"<<ID<<"\t"<<LeftCorner.x<<"\t"<<LeftCorner.y<<"\t"<<LHS<<"\t"<<opLHS<<"\t"<<op<<"\t"<<opRHS<<"\t\""<<Comment<<"\"\n";
}

void SnglOpAssign::Load(ifstream &Infile)
{
	string str;
	getline(Infile,str);
	str+='\0';
	int LeftLimit,RightLimit=6;
	string StatInfo[8],tempstring="";
	for(int i=0;i<8;i++)
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
	opLHS=StatInfo[4];
	op=StatInfo[5];
	opRHS=StatInfo[6];
	Comment=StatInfo[7];
	UpdateStatementText();
}

void SnglOpAssign::Move(Point P)
{
	LeftCorner=P;
	pOut->GetAssignPoints(LeftCorner,Text,Inlet,Outlet);
}

bool SnglOpAssign::Edit(const string &str)
{
	if(str[0]=='+'||str[0]=='-'||str[0]=='*'||str[0]=='/'||str[0]=='='||str[0]=='\0')	//if the string is empty or the first character is an operator or the equal sign
		return false;
	int numberofequalsigns=0,numberofoperators=0,i=0,equalsignposition,operatorposition,stringsize;
	while(1)
	{
		if(str[i]=='=')
		{
			numberofequalsigns++;
			equalsignposition=i;
			if(str[i+1]=='\0')	//no RHS
				return false;
			if(str[i+1]=='+'||str[i+1]=='-'||str[i+1]=='*'||str[i+1]=='/') //no operator LHS
				return false;
		}
		if(str[i]=='+'||str[i]=='-'||str[i]=='*'||str[i]=='/')
		{
			numberofoperators++;
			operatorposition=i;
			if(str[i+1]=='\0')	//no operator RHS
				return false;
		}
		if(numberofequalsigns>1||numberofoperators>1)
			return false;
		if(str[i]=='\0')
		{
			stringsize=i;
			break;
		}
		i++;
	}
	if(numberofequalsigns==0||numberofoperators==0)
		return false;
	string L="",opL="",opR="";
	for(i=0;i<equalsignposition;i++)
		L+=str[i];
	for(i=equalsignposition+1;i<operatorposition;i++)
		opL+=str[i];
	for(i=operatorposition+1;i<stringsize;i++)
		opR+=str[i];
	bool LHSvalidation=ValidateName(L),opLHSnamevalidation=ValidateName(opL),opLHSnumvalidation=ValidateNumber(opL),opRHSnamevalidation=ValidateName(opR),opRHSnumvalidation=ValidateNumber(opR);
	if(LHSvalidation&&(opLHSnamevalidation||opLHSnumvalidation)&&(opRHSnamevalidation||opRHSnumvalidation))
	{
		LHS=L; opLHS=opL; op=str[operatorposition]; opRHS=opR;
		UpdateStatementText();
		return true;
	}
	else
		return false;
}

Statement* SnglOpAssign::GenerateCode(ofstream &OutFile)
{
	if(!(OutFile.is_open()))
		OutFile.open("C++ code.txt",ios::out|ios::app);
	OutFile<<"\t"<<LHS<<"="<<opLHS<<op<<opRHS<<";\n";
	return pConn->getDstStat();
}

Statement* SnglOpAssign::Simulate(bool StepByStep)
{
	string temp1[2]={opLHS,opRHS};
	double temp2[2];
	for(int i=0;i<2;i++)
	{
		if(ValidateName(temp1[i]))
		{
			for(int j=0;j<600;j++)
			{
				if(VariableList[j]!=NULL)
				{
					if(VariableList[j]->getname()==temp1[i])
					{
						if(!(VariableList[j]->hasvalue()))
							return NULL;
						else
						{
							temp2[i]=VariableList[j]->getvalue();
							break;
						}
					}
				}
				else
					return NULL;
			}
		}
		else if(ValidateNumber(temp1[i]))
			temp2[i]=stod(temp1[i]);
		else
			return NULL;
	}
	double result;
	if(op=="+")
		result=temp2[0]+temp2[1];
	else if(op=="-")
		result=temp2[0]+temp2[1];
	else if(op=="*")
		result=temp2[0]*temp2[1];
	else if(op=="/")
		result=temp2[0]/temp2[1];
	else
		return NULL;
	for(int i=0;i<600;i++)
	{
		if(VariableList[i]==NULL)
		{
			VariableList[i]=new Variable(LHS);
			VariableList[i]->setvalue(result);
			if(StepByStep)
			{
				ostringstream T;
				T<<LHS<<" = "<<result;
				pOut->PrintMessage(T.str());
			}
			return pConn->getDstStat();
		}
		else if(VariableList[i]->getname()==LHS)
		{
			VariableList[i]->setvalue(result);
			if(StepByStep)
			{
				ostringstream T;
				T<<LHS<<" = "<<result;
				pOut->PrintMessage(T.str());
			}
			return pConn->getDstStat();
		}
	}
	return NULL;
}

void SnglOpAssign::PrintInfo()
{
	if(Comment!="")
		pOut->PrintMessage("Single Operator Assignment Statement. \""+Comment+"\"");
	else
		pOut->PrintMessage("Single Operator Assignment Statement.");
}