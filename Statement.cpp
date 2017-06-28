#include "Statement.h"

int Statement::numberofstatements=0;
Variable* Statement::VariableList[600];

Variable::Variable(string n)
{
	setname(n);
	hasavalue=false;
}

void Variable::setname(string n)
{
	name=n;
}

void Variable::setvalue(double v)
{
	value=v;
	if(hasavalue==false)
		hasavalue=true;
}

string Variable::getname()
{
	return name;
}

double Variable::getvalue()
{
	if(hasavalue==true)
		return value;
	else
		return 0;
}

bool Variable::hasvalue()
{
	return hasavalue;
}

Statement::Statement(Output *pOut)	
{
	numberofstatements++;
	ID=numberofstatements;
	this->pOut=pOut;
	Text=Comment="";
	Selected = false;
}

Statement::~Statement()
{
	for(int i=0;i<600;i++)
	{
		if(VariableList[i]!=NULL)
			delete VariableList[i];
		else
			break;
	}
	numberofstatements--;
}

void Statement::SetSelected(bool s)
{	Selected = s; }

bool Statement::IsSelected() const
{	return Selected; }

void Statement::SetComment(string c)
{Comment=c;}

int Statement::getID()
{return ID;}

string Statement::GetText()
{return Text;}

StatementType Statement::GetType()
{return Type;}

void Statement::InitializeVariableList()
{
	for(int i=0;i<600;i++)
		VariableList[i]=NULL;
}

void Statement::ResetVariableList()
{
	//kamel
}

bool Statement::ValidateName(const string &str)
{
	if(!(str[0]>64&&str[0]<91||str[0]>96&&str[0]<123)&&str[0]!='_')	//if the first character is not a letter or an underscore
		return false;
	int i=1;
	while(1)
	{
		if(!(str[i]>47&&str[i]<58)&&!(str[i]>64&&str[i]<91)&&!(str[i]>96&&str[i]<123)&&str[i]!='_'&&str[i]!='='&&str[i]!='\0') //if the variable name contains an illegal character
			return false;
		if(str[i]=='\0')
			break;
		i++;
	}
	return true;
}

bool Statement::ValidateNumber(const string &str)
{
	int i=0;
	bool decimalpointreached=false;
	while(1)
	{
		if(!(str[i]>47&&str[i]<58)&&str[i]!='.'&&str[i]!='-'&&str[i]!='\0')	//there is a character that is not a number
			return false;
		if(decimalpointreached==true&&str[i]=='.')	//there is more than one decimal point
			return false;
		if(str[i]=='-'&&i>0)	//the negative sign is not at the beginning of the RHS
			return false;
		if(str[i]=='.')	//decimal point reached
			decimalpointreached=true;
		if(str[i]=='\0')	//end of string reached
			break;
		i++;
	}
	return true;
}