#include "Conditional.h"
#include "SmplAssign.h"
#include "VarAssign.h"
#include "SnglOpAssign.h"
#include "Conditional.h"
#include "Read.h"
#include "Write.h"
#include "Start.h"
#include "End.h"

Conditional::Conditional(Output* pOut, Point LP, string LeftHS, string oprtr, string RightHS):Statement(pOut)
{
	Type=COND;
	LeftPoint=LP;
	LHS=LeftHS;
	op=oprtr;
	RHS=RightHS;
	UpdateStatementText();
	
	pYesConn=pNoConn=NULL;	//No connectors yet
}

Conditional::Conditional(const Conditional &old):Statement(old.pOut)
{
	Text=old.Text;
	Type=old.Type;
	LeftPoint=old.LeftPoint;
	LHS=old.LHS;
	op=old.op;
	RHS=old.RHS;
	pYesConn=old.pYesConn;
	pNoConn=old.pNoConn;
	pOut=old.pOut;
	ID=old.numberofstatements;
	UpdateStatementText();
}

Conditional::Conditional(const Conditional &old,Point p):Statement(old.pOut)
{
	Text=old.Text;
	Type=old.Type;
	LeftPoint=p;
	LHS=old.LHS;
	op=old.op;
	RHS=old.RHS;
	pYesConn=pNoConn=NULL;
	pOut=old.pOut;
	ID=old.numberofstatements;
}

void Conditional::setLHS(const string &L)
{
	LHS=L;
	UpdateStatementText();
}

void Conditional::setop(const string &oprtr)
{
	op=oprtr;
	UpdateStatementText();
}

void Conditional::setRHS(const string &R)
{
	RHS=R;
	UpdateStatementText();
}

void Conditional::setpConn(Connector* c)
{
	if(c==NULL)
		pYesConn=pNoConn=NULL;
	else
	{
		if(*c->getCondValue()==true)
			pYesConn=c;
		else
			pNoConn=c;
	}
}

void Conditional::makepYesConnNull()
{
	pYesConn=NULL;
}

void Conditional::makepNoConnNull()
{
	pNoConn=NULL;
}

Point Conditional::GetPoint()
{
	return LeftPoint;
}

Point Conditional::GetInlet()
{
	return Inlet;
}

Point Conditional::getYesOutlet()
{return YesOutlet;}

Point Conditional::getNoOutlet()
{return NoOutlet;}

Connector* Conditional::getpConn(bool CondValue)
{
	if(CondValue)
		return pYesConn;
	else
		return pNoConn;
}

int Conditional::getWidth()
{
	return NoOutlet.x-YesOutlet.x;
}

void Conditional::Move(Point P)
{
	LeftPoint=P;
	pOut->GetConditionalPoints(LeftPoint,Text,Inlet,YesOutlet,NoOutlet);
}

bool Conditional::Edit(const string &str)
{

	if(str[0]=='<'||str[0]=='>'||str[0]=='='||str[0]=='!'||str[0]=='\0')	//if the string is empty or the first character is the operator
		return false;
	int numberofoperators=0,i=0,operatorposition,stringsize;
	while(1)
	{
		if(str[i]=='\0')
		{
			stringsize=i-1;
			break;
		}
		if(str[i]=='<'||str[i]=='>'||str[i+1]=='='&&(str[i]=='<'||str[i]=='>'||str[i]=='='||str[i]=='!'))
		{
			numberofoperators++;
			operatorposition=i;
			if(str[i+1]=='\0'||str[i+1]=='='&&str[i+2]=='\0')	//no RHS
				return false;
			if(str[i+1]=='=')
			{
				i++;
			}
		}
		if(numberofoperators>1)
			return false;
		i++;
	}
	if(numberofoperators==0)
		return false;
	string L="",R="";
	for(i=0;i<operatorposition;i++)
		L+=str[i];
	if(str[operatorposition+1]=='=')
	{
		for(i=operatorposition+2;i<=stringsize;i++)
			R+=str[i];
	}
	else
	{
		for(i=operatorposition+1;i<=stringsize;i++)
			R+=str[i];
	}
	bool LHSvalidation=ValidateName(L),RHSnamevalidation=ValidateName(R),RHSnumvalidation=ValidateNumber(R);
	if(LHSvalidation&&(RHSnamevalidation||RHSnumvalidation))
	{
		LHS=L; op=str[operatorposition]; RHS=R;
		if(str[operatorposition+1]=='=')
			op+='=';
		UpdateStatementText();
		return true;
	}
	else
		return false;
}

void Conditional::UpdateStatementText()
{
	if(LHS==""||RHS==""||!(op=="=="||op=="!="||op==">"||op=="<"||op==">="||op=="<="))
		Text=" == ";
	else
		Text=LHS+" "+op+" "+RHS;
	pOut->GetConditionalPoints(LeftPoint, Text, Inlet, YesOutlet, NoOutlet);
}

void Conditional::Draw() const
{
	pOut->DrawConditional(LeftPoint,Text,Selected);
}

void Conditional::Save(ofstream &OutFile)
{
	OutFile<<"COND\t"<<ID<<"\t"<<LeftPoint.x<<"\t"<<LeftPoint.y<<"\t"<<LHS<<"\t"<<op<<"\t"<<RHS<<"\t\""<<Comment<<"\"\n";
}

void Conditional::Load(ifstream &Infile)
{
	string str;
	getline(Infile,str);
	str+='\0';
	int LeftLimit,RightLimit=4;
	string StatInfo[7],tempstring="";
	for(int i=0;i<7;i++)
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
	LHS=StatInfo[3];
	op=StatInfo[4];
	RHS=StatInfo[5];
	Comment=StatInfo[6];
	UpdateStatementText();
}

Statement* Conditional::GenerateCode(ofstream &OutFile)
{
	Statement* pStat=pYesConn->getDstStat();
	ConditionalType CondType;
	if(pStat->GetType()==END)
		CondType=IF;
	while(pStat->GetType()!=END)
	{
		if(pStat->GetType()==COND)
			pStat=CalculateFinishStat(((Conditional*)pStat)->getpConn(true)->getDstStat(),((Conditional*)pStat)->getpConn(false)->getDstStat()); 
		else if(pStat->GetType()==SMPL_ASSIGN)
			pStat=((SmplAssign*)pStat)->getpConn()->getDstStat();
		else if(pStat->GetType()==VAR_ASSIGN)
			pStat=((VarAssign*)pStat)->getpConn()->getDstStat();
		else if(pStat->GetType()==SNGL_OP_ASSIGN)
			pStat=((SnglOpAssign*)pStat)->getpConn()->getDstStat();
		else if(pStat->GetType()==READ)
			pStat=((Read*)pStat)->getpConn()->getDstStat();
		else if(pStat->GetType()==WRITE)
			pStat=((Write*)pStat)->getpConn()->getDstStat();
		else if(pStat->GetType()==START)
			pStat=((Start*)pStat)->getpConn()->getDstStat();
		if(pStat->GetType()==END)
			CondType=IF;
		if(pStat==this)
			CondType=WHILE;
	}
	if(CondType!=WHILE)
	{
		pStat=pNoConn->getDstStat();
		while(pStat->GetType()!=END)
		{
			if(pStat->GetType()==COND)
				pStat=CalculateFinishStat(((Conditional*)pStat)->getpConn(true)->getDstStat(),((Conditional*)pStat)->getpConn(false)->getDstStat()); 
			else if(pStat->GetType()==SMPL_ASSIGN)
				pStat=((SmplAssign*)pStat)->getpConn()->getDstStat();
			else if(pStat->GetType()==VAR_ASSIGN)
				pStat=((VarAssign*)pStat)->getpConn()->getDstStat();
			else if(pStat->GetType()==SNGL_OP_ASSIGN)
				pStat=((SnglOpAssign*)pStat)->getpConn()->getDstStat();
			else if(pStat->GetType()==READ)
				pStat=((Read*)pStat)->getpConn()->getDstStat();
			else if(pStat->GetType()==WRITE)
				pStat=((Write*)pStat)->getpConn()->getDstStat();
			else if(pStat->GetType()==START)
				pStat=((Start*)pStat)->getpConn()->getDstStat();
			if(pStat->GetType()==END)
				CondType=IF;
			if(pStat==this)
				CondType=WHILE_NOT;
		}
	}
	if(!(OutFile.is_open()))
		OutFile.open("C++ code.txt",ios::out|ios::app);
	if(CondType==IF)
	{
		OutFile<<"\t"<<"if("<<LHS<<op<<RHS<<")"<<"\n";
		Statement *pStat1,*pStat2,*FinishStat;
		pStat1=pYesConn->getDstStat();
		pStat2=pNoConn->getDstStat();
		FinishStat=CalculateFinishStat(pStat1,pStat2);
		OutFile<<"\t{\n";
		if(pStat1==FinishStat)
			OutFile<<";\n";
		else
			while(pStat1!=FinishStat)
				pStat1=pStat1->GenerateCode(OutFile);
		if(!(OutFile.is_open()))
			OutFile.open("C++ code.txt",ios::out|ios::app);
		OutFile<<"\t}\n\telse\n\t{\n";
		if(pStat2==FinishStat)
			OutFile<<";\n";
		else
			while(pStat2!=FinishStat)
				pStat2=pStat2->GenerateCode(OutFile);
		if(!(OutFile.is_open()))
			OutFile.open("C++ code.txt",ios::out|ios::app);
		OutFile<<"\t}\n";
		return FinishStat;
	}
	else if(CondType==WHILE)
	{
		OutFile<<"While("<<LHS<<op<<RHS<<")\n\t{\n";
		pStat=pYesConn->getDstStat();
		while(pStat!=this)
			pStat=pStat->GenerateCode(OutFile);
		OutFile<<"\t}\n";
		return pNoConn->getDstStat();
	}
	else if(CondType==WHILE_NOT)
	{
		OutFile<<"While(!("<<LHS<<op<<RHS<<"))\n\t{\n";
		pStat=pNoConn->getDstStat();
		while(pStat!=this)
			pStat=pStat->GenerateCode(OutFile);
		OutFile<<"\t}\n";
		return pYesConn->getDstStat();
	}
	return NULL;
}

Statement* Conditional::CalculateFinishStat(Statement* pStat1, Statement* pStat2)
{
	if(pStat1==pStat2||pStat1->GetType()==END||pStat2->GetType()==END)
		return pStat1;
	Statement* initialpStat2=pStat2;
	while(pStat1->GetType()!=END)
	{
		pStat2=initialpStat2;
		while(pStat2->GetType()!=END)
		{
			if(pStat1==pStat2)
				return pStat1;
			if(pStat2->GetType()==COND)
				pStat2=CalculateFinishStat(((Conditional*)pStat2)->getpConn(true)->getDstStat(),((Conditional*)pStat2)->getpConn(false)->getDstStat()); 
			else if(pStat2->GetType()==SMPL_ASSIGN)
				pStat2=((SmplAssign*)pStat2)->getpConn()->getDstStat();
			else if(pStat2->GetType()==VAR_ASSIGN)
				pStat2=((VarAssign*)pStat2)->getpConn()->getDstStat();
			else if(pStat2->GetType()==SNGL_OP_ASSIGN)
				pStat2=((SnglOpAssign*)pStat2)->getpConn()->getDstStat();
			else if(pStat2->GetType()==READ)
				pStat2=((Read*)pStat2)->getpConn()->getDstStat();
			else if(pStat2->GetType()==WRITE)
				pStat2=((Write*)pStat2)->getpConn()->getDstStat();
			else if(pStat2->GetType()==START)
				pStat2=((Start*)pStat2)->getpConn()->getDstStat();
		}
		if(pStat1->GetType()==COND)
			pStat1=CalculateFinishStat(((Conditional*)pStat1)->getpConn(true)->getDstStat(),((Conditional*)pStat1)->getpConn(false)->getDstStat()); 
		else if(pStat1->GetType()==SMPL_ASSIGN)
			pStat1=((SmplAssign*)pStat1)->getpConn()->getDstStat();
		else if(pStat1->GetType()==VAR_ASSIGN)
			pStat1=((VarAssign*)pStat1)->getpConn()->getDstStat();
		else if(pStat1->GetType()==SNGL_OP_ASSIGN)
			pStat1=((SnglOpAssign*)pStat1)->getpConn()->getDstStat();
		else if(pStat1->GetType()==READ)
			pStat1=((Read*)pStat1)->getpConn()->getDstStat();
		else if(pStat1->GetType()==WRITE)
			pStat1=((Write*)pStat1)->getpConn()->getDstStat();
		else if(pStat1->GetType()==START)
			pStat1=((Start*)pStat1)->getpConn()->getDstStat();
	}
	//if the program exits both while loops then both pStat1 and pStat2 point to an end statement
	return pStat1; //which is an end statement
}

Statement* Conditional::Simulate(bool StepByStep)
{
	string temp1[2]={LHS,RHS};
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
	bool result;
	if(op==">")
		result=temp2[0]>temp2[1];
	else if(op=="<")
		result=temp2[0]<temp2[1];
	else if(op==">=")
		result=temp2[0]>=temp2[1];
	else if(op=="<=")
		result=temp2[0]<=temp2[1];
	else if(op=="==")
		result=temp2[0]==temp2[1];
	else if(op=="!=")
		result=temp2[0]!=temp2[1];
	else
		return NULL;
	if(result)
	{
		if(StepByStep)
			pOut->PrintMessage(Text+" returned Yes");
		return pYesConn->getDstStat();
	}
	else
	{
		if(StepByStep)
			pOut->PrintMessage(Text+" returned No");
		return pNoConn->getDstStat();
	}
}

void Conditional::PrintInfo()
{
	if(Comment!="")
		pOut->PrintMessage("Conditional Statement. \""+Comment+"\"");
	else
		pOut->PrintMessage("Conditional Statement.");
}