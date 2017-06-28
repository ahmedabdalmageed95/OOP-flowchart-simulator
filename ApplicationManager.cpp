#include "ApplicationManager.h"
#include "Actions\AddSmplAssign.h"
#include "Actions\AddVarAssign.h"
#include "Actions\AddSnglOpAssign.h"
#include "Actions\AddConditional.h"
#include "Actions\AddRead.h"
#include "Actions\AddWrite.h"
#include "Actions\AddStart.h"
#include "Actions\AddEnd.h"
#include "Actions\AddConnector.h"
#include "Actions\Save.h"
#include "Actions\Load.h"
#include "Actions\SwitchToSimulation.h"
#include "Actions\SwitchToDesign.h"
#include "Actions\DrawingArea.h"
#include "Actions\Comment.h"
#include "Actions\Edit.h"
#include "Actions\Delete.h"
#include "Actions\Move.h"
#include "Actions\Copy.h"
#include "Actions\Cut.h"
#include "Actions\Paste.h"
#include "Actions\MultipleSelection.h"
#include "Actions\Undo.h"
#include "Actions\Validate.h"
#include "Actions\Run.h"
#include "Actions\StepByStep.h"
#include "Actions\Generate.h"
#include "GUI\Input.h"
#include "GUI\Output.h"

//Constructor
ApplicationManager::ApplicationManager()
{
	//Create Input and output
	pOut = new Output;
	pIn = pOut->CreateInput(this);
	
	StatCount = 0;
	ConnCount = 0;
	pSelectedStat = NULL;	//no Statement is selected yet
	pCpdStat=NULL;
	
	//Create an array of Statement pointers and set them to NULL		
	for(int i=0; i<MaxCount; i++)
	{
		StatList[i] = NULL;	
		ConnList[i] = NULL;
		SelectedStat[i]=NULL;
		CpdStat[i]=NULL;
	}
	for(int i=0;i<10;i++)
	{
		for(int j=0;j<MaxCount;j++)
		{
			UndoStatArray[i][j]=NULL;
			UndoConnArray[i][j]=NULL;
		}
		UndoStatArrayStatCount[i]=0;
		UndoConnArrayConnCount[i]=0;
	}
	UndoStatListsUsed=0;
	UndoConnListsUsed=0;

	Statement::InitializeVariableList();
}

//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//
ActionType ApplicationManager::GetUserAction() const
{
	//Ask the input to get the action from the user.
	return pIn->GetUserAction();		
}
////////////////////////////////////////////////////////////////////////////////////
//Creates an action and executes it
void ApplicationManager::ExecuteAction(ActionType ActType) 
{
	Action* pAct = NULL;
	
	//According to ActioType, create the corresponding action object
	switch (ActType)
	{
		case ADD_SMPL_ASSIGN:
			pAct = new AddSmplAssign(this);
			break;

		case ADD_VAR_ASSIGN:
			pAct=new AddVarAssign(this);
			break;

		case ADD_OP_ASSIGN:
			pAct=new AddSnglOpAssign(this);
			break;

		case ADD_CONDITION:
			pAct=new AddConditional(this);
			break;

		case ADD_READ:
			pAct=new AddRead(this);
			break;

		case ADD_WRITE:
			pAct=new AddWrite(this);
			break;

		case ADD_START:
			pAct=new AddStart(this);
			break;

		case ADD_END:
			pAct=new AddEnd(this);
			break;

		case ADD_CONNECTOR:
			pAct=new AddConnector(this);
			break;

		case SAVE:
			pAct=new Save(this);
			break;

		case LOAD:
			pAct=new Load(this);
			break;

		case SIM_MODE:
			pAct=new SwitchToSimulation(this);
			break;

		case DSN_MODE:
			pAct=new SwitchToDesign(this);
			break;

		case DRAW_AREA:
			pAct=new DrawingArea(this);
			break;

		case COMMENT:
			pAct=new Comment(this);
			break;

		case EDIT_STAT:
			pAct=new Edit(this);
			break;

		case DEL:
			pAct=new Delete(this);
			break;

		case MOVE:
			pAct=new Move(this);
			break;

		case COPY:
			pAct=new Copy(this);
			break;

		case CUT:
			pAct=new Cut(this);
			break;

		case PASTE:
			pAct=new Paste(this);
			break;

		case MULTIPLE_SELECTION:
			pAct=new MultipleSelection(this);
			break;

		case UNDO:
			pAct=new Undo(this);
			break;

		case VALIDATE:
			pAct=new Validate(this);
			break;

		case RUN:
			pAct=new Run(this);
			break;

		case STP:
			pAct=new StepByStep(this);
			break;

		case GENERATE:
			pAct=new Generate(this);
			break;

		case EXIT:
			///create Exit Action here
			break;
		
		case STATUS:
			return;
	}
	if(ActType==ADD_SMPL_ASSIGN||ActType==ADD_VAR_ASSIGN||ActType==ADD_OP_ASSIGN||ActType==ADD_CONDITION||ActType==ADD_READ||ActType==ADD_WRITE||ActType==ADD_START||ActType==ADD_END||ActType==ADD_CONNECTOR||ActType==COMMENT||ActType==DELETE||ActType==MOVE||ActType==EDIT_STAT||ActType==CUT||ActType==PASTE)
	{
		PushStatListInUndoStatArray();
		PushConnListInUndoConnArray();
	}
	//undo will be on adds, comment, edit, delete, move, cut, paste
	//Execute the created action
	if(pAct != NULL)
	{
		pAct->Execute();//Execute
		delete pAct;	//Action is not needed any more ==> delete it
	}
}



//==================================================================================//
//						Statements Management Functions								//
//==================================================================================//
//Add a statement to the list of statements
void ApplicationManager::AddStatement(Statement *pStat)
{
	if(StatCount < MaxCount)
		StatList[StatCount++] = pStat;
	
}

void ApplicationManager::AddConn(Connector* pConn)
{
	if(ConnCount < MaxCount)
		ConnList[ConnCount++] = pConn;
}

////////////////////////////////////////////////////////////////////////////////////
Statement *ApplicationManager::GetStatement(Point P) const
{
	//If this point P(x,y) belongs to a statement return a pointer to it.
	//otherwise, return NULL


	///Add your code here to search for a statement given a point P(x,y)

	for(int i=0;i<StatCount;i++)
	{
		if(StatList[i]->GetType()==SMPL_ASSIGN||StatList[i]->GetType()==VAR_ASSIGN||StatList[i]->GetType()==SNGL_OP_ASSIGN)
		{
			int width=0,height=0;
			pIn->GetAssignDimensions(StatList[i]->GetText(),width,height);
			if(P.x>StatList[i]->GetPoint().x&&P.x<StatList[i]->GetPoint().x+width&&P.y>StatList[i]->GetPoint().y&&P.y<StatList[i]->GetPoint().y+height)
				return StatList[i];
		}
		if(StatList[i]->GetType()==COND)
		{
			int diagonallength=0;
			pIn->GetConditionalDimensions(StatList[i]->GetText(),diagonallength);
			if(P.x>StatList[i]->GetPoint().x&&P.x<StatList[i]->GetPoint().x+diagonallength&&P.y>StatList[i]->GetPoint().y-0.5*diagonallength&&P.y<StatList[i]->GetPoint().y+0.5*diagonallength)
				return StatList[i];
		}
		if(StatList[i]->GetType()==READ||StatList[i]->GetType()==WRITE)
		{
			int width=0,height=0;
			pIn->GetIODimensions(StatList[i]->GetText(),width,height);
			if(P.x>StatList[i]->GetPoint().x-height/tan(3.1415/3)&&P.x<StatList[i]->GetPoint().x+width&&P.y>StatList[i]->GetPoint().y&&P.y<StatList[i]->GetPoint().y+height)
				return StatList[i];
		}
		if(StatList[i]->GetType()==START||StatList[i]->GetType()==END)
		{
			int width=0,height=0;
			pIn->GetStartEndDimensions(StatList[i]->GetText(),width,height);
			if(P.x>StatList[i]->GetPoint().x&&P.x<StatList[i]->GetPoint().x+width&&P.y>StatList[i]->GetPoint().y&&P.y<StatList[i]->GetPoint().y+height)
				return StatList[i];
		}
	}

	return NULL;
}

Connector *ApplicationManager::GetConnector(Point P) const
{
	for(int i=0;i<ConnCount;i++)
	{
		if (ConnList[i]->getStartPoint().x == ConnList[i]->getEndPoint().x && ConnList[i]->getStartPoint().y<ConnList[i]->getEndPoint().y)
		{
			if(P.y>=ConnList[i]->getStartPoint().y&&P.y<=ConnList[i]->getEndPoint().y&&P.x>=ConnList[i]->getStartPoint().x-2&&P.x<=ConnList[i]->getEndPoint().x+2)
				return ConnList[i];
		}
		else if (abs(ConnList[i]->getStartPoint().x-ConnList[i]->getEndPoint().x)<=20&&ConnList[i]->getStartPoint().y>ConnList[i]->getEndPoint().y)
		{
			if(P.x>=ConnList[i]->getStartPoint().x-2&&P.x<=ConnList[i]->getStartPoint().x+2&&P.y>=ConnList[i]->getStartPoint().y&&P.y<=ConnList[i]->getStartPoint().y+20)
				return ConnList[i];
			if(P.x>=ConnList[i]->getStartPoint().x-50&&P.x<=ConnList[i]->getStartPoint().x&&P.y>=ConnList[i]->getStartPoint().y+20-2&&P.y<=ConnList[i]->getStartPoint().y+20+2)
				return ConnList[i];
			if(P.x>=ConnList[i]->getStartPoint().x-50-2&&P.x<=ConnList[i]->getStartPoint().x-50+2&&P.y>=ConnList[i]->getEndPoint().y-20&&P.y<=ConnList[i]->getStartPoint().y+20)
				return ConnList[i];
			if(P.x>=ConnList[i]->getStartPoint().x-50&&P.x<=ConnList[i]->getEndPoint().x&&P.y>=ConnList[i]->getEndPoint().y-20-2&&P.y<=ConnList[i]->getEndPoint().y-20+2)
				return ConnList[i];
			if(P.x>=ConnList[i]->getEndPoint().x-2&&P.x<=ConnList[i]->getEndPoint().x+2&&P.y>=ConnList[i]->getEndPoint().y-20&&P.y<=ConnList[i]->getEndPoint().y)
				return ConnList[i];
		}
		else if(ConnList[i]->getStartPoint().x<ConnList[i]->getEndPoint().x&&ConnList[i]->getStartPoint().y>ConnList[i]->getEndPoint().y-30||ConnList[i]->getStartPoint().x>ConnList[i]->getEndPoint().x&&ConnList[i]->getStartPoint().y>ConnList[i]->getEndPoint().y-30)
		{
			if(P.x>=ConnList[i]->getStartPoint().x-2&&P.x<=ConnList[i]->getStartPoint().x+2&&P.y>=ConnList[i]->getStartPoint().y&&P.y<=ConnList[i]->getStartPoint().y+20)
				return ConnList[i];
			if(ConnList[i]->getStartPoint().x<ConnList[i]->getEndPoint().x)
			{
				if(P.x>=ConnList[i]->getStartPoint().x&&P.x<=(ConnList[i]->getStartPoint().x+ConnList[i]->getEndPoint().x)/2&&P.y>=ConnList[i]->getStartPoint().y+20-2&&P.y<=ConnList[i]->getStartPoint().y+20+2)
					return ConnList[i];
				if(P.x>=((ConnList[i]->getStartPoint().x+ConnList[i]->getEndPoint().x)/2)-2&&P.x<=((ConnList[i]->getStartPoint().x+ConnList[i]->getEndPoint().x)/2)+2&&P.y>=ConnList[i]->getEndPoint().y-20&&P.y<=ConnList[i]->getStartPoint().y+20)
					return ConnList[i];
				if(P.x>=(ConnList[i]->getStartPoint().x+ConnList[i]->getEndPoint().x)/2&&P.x<=ConnList[i]->getEndPoint().x&&P.y>=ConnList[i]->getEndPoint().y-20-2&&P.y<=ConnList[i]->getEndPoint().y-20+2)
					return ConnList[i];
				if(P.x>=ConnList[i]->getEndPoint().x-2&&P.x<=ConnList[i]->getEndPoint().x+2&&P.y>=ConnList[i]->getEndPoint().y-20&&P.y<=ConnList[i]->getEndPoint().y)
					return ConnList[i];
			}
			if(ConnList[i]->getStartPoint().x>ConnList[i]->getEndPoint().x)
			{
				if(P.x<=ConnList[i]->getStartPoint().x&&P.x>=(ConnList[i]->getStartPoint().x+ConnList[i]->getEndPoint().x)/2&&P.y>=ConnList[i]->getStartPoint().y+20-2&&P.y<=ConnList[i]->getStartPoint().y+20+2)
					return ConnList[i];
				if(P.x>=((ConnList[i]->getStartPoint().x+ConnList[i]->getEndPoint().x)/2)-2&&P.x<=((ConnList[i]->getStartPoint().x+ConnList[i]->getEndPoint().x)/2)+2&&P.y>=ConnList[i]->getEndPoint().y-20&&P.y<=ConnList[i]->getStartPoint().y+20)
					return ConnList[i];
				if(P.x<=(ConnList[i]->getStartPoint().x+ConnList[i]->getEndPoint().x)/2&&P.x>=ConnList[i]->getEndPoint().x&&P.y>=ConnList[i]->getEndPoint().y-20-2&&P.y<=ConnList[i]->getEndPoint().y-20+2)
					return ConnList[i];
				if(P.x>=ConnList[i]->getEndPoint().x-2&&P.x<=ConnList[i]->getEndPoint().x+2&&P.y>=ConnList[i]->getEndPoint().y-20&&P.y<=ConnList[i]->getEndPoint().y)
					return ConnList[i];
			}
		}
		else if(ConnList[i]->getStartPoint().x<ConnList[i]->getEndPoint().x&&ConnList[i]->getStartPoint().y<ConnList[i]->getEndPoint().y||ConnList[i]->getStartPoint().x>ConnList[i]->getEndPoint().x&&ConnList[i]->getStartPoint().y<ConnList[i]->getEndPoint().y)
		{
			if(P.x>=ConnList[i]->getStartPoint().x-2&&P.x<=ConnList[i]->getStartPoint().x+2&&P.y>=ConnList[i]->getStartPoint().y&&P.y<=(ConnList[i]->getStartPoint().y+ConnList[i]->getEndPoint().y)/2)
				return ConnList[i];
			if(ConnList[i]->getStartPoint().x<ConnList[i]->getEndPoint().x)
			{
				if(P.x>=ConnList[i]->getStartPoint().x&&P.x<=ConnList[i]->getEndPoint().x&&P.y>=((ConnList[i]->getStartPoint().y+ConnList[i]->getEndPoint().y)/2)-2&&P.y<=((ConnList[i]->getStartPoint().y+ConnList[i]->getEndPoint().y)/2)+2)
					return ConnList[i];
				if(P.x>=ConnList[i]->getEndPoint().x-2&&P.x<=ConnList[i]->getEndPoint().x+2&&P.y>=(ConnList[i]->getStartPoint().y+ConnList[i]->getEndPoint().y)/2&&P.y<=ConnList[i]->getEndPoint().y)
					return ConnList[i];
			}
			if(ConnList[i]->getStartPoint().x>ConnList[i]->getEndPoint().x)
			{
				if(P.x<=ConnList[i]->getStartPoint().x&&P.x>=ConnList[i]->getEndPoint().x&&P.y>=((ConnList[i]->getStartPoint().y+ConnList[i]->getEndPoint().y)/2)-2&&P.y<=((ConnList[i]->getStartPoint().y+ConnList[i]->getEndPoint().y)/2)+2)
					return ConnList[i];
				if(P.x>=ConnList[i]->getEndPoint().x-2&&P.x<=ConnList[i]->getEndPoint().x+2&&P.y>=(ConnList[i]->getStartPoint().y+ConnList[i]->getEndPoint().y)/2&&P.y<=ConnList[i]->getEndPoint().y)
					return ConnList[i];
			}
		}
	}
	return NULL;
}

void ApplicationManager::PushStatListInUndoStatArray()
{
	if(UndoStatListsUsed==10)
	{
		ShiftUndoStatListsLeft();
		CopyOfStatListInUndoStatArray(9);
		UndoStatArrayStatCount[9]=StatCount;
	}
	else
	{
		CopyOfStatListInUndoStatArray(UndoStatListsUsed);
		UndoStatArrayStatCount[UndoStatListsUsed]=StatCount;
		UndoStatListsUsed++;
	}
}

void ApplicationManager::ShiftUndoStatListsLeft()
{
	for(int i=0;i<9;i++)
	{
		for(int j=0;j<MaxCount;j++)
		{
			if(i==0)
				delete UndoStatArray[i][j];
			UndoStatArray[i][j]=UndoStatArray[i+1][j];
		}
	}
	for(int i=0;i<MaxCount;i++)
		UndoStatArray[9][i]=NULL;
	for(int i=0;i<9;i++)
	{
		UndoStatArrayStatCount[i]=UndoStatArrayStatCount[i+1];
		UndoStatArrayStatCount[i+1]=0;
	}
}

void ApplicationManager::CopyOfStatListInUndoStatArray(int i)
{
	for(int j=0;j<MaxCount;j++)
	{
		if(StatList[j]==NULL)
			UndoStatArray[i][j]=NULL;
		else
		{
			if(StatList[j]->GetType()==SMPL_ASSIGN)
				UndoStatArray[i][j]=new SmplAssign(*(SmplAssign*)StatList[j]);
			if(StatList[j]->GetType()==VAR_ASSIGN)
				UndoStatArray[i][j]=new VarAssign(*(VarAssign*)StatList[j]);
			if(StatList[j]->GetType()==SNGL_OP_ASSIGN)
				UndoStatArray[i][j]=new SnglOpAssign(*(SnglOpAssign*)StatList[j]);
			if(StatList[j]->GetType()==COND)
				UndoStatArray[i][j]=new Conditional(*(Conditional*)StatList[j]);
			if(StatList[j]->GetType()==READ)
				UndoStatArray[i][j]=new Read(*(Read*)StatList[j]);
			if(StatList[j]->GetType()==WRITE)
				UndoStatArray[i][j]=new Write(*(Write*)StatList[j]);
			if(StatList[j]->GetType()==START)
				UndoStatArray[i][j]=new Start(*(Start*)StatList[j]);
			if(StatList[j]->GetType()==END)
				UndoStatArray[i][j]=new End(*(End*)StatList[j]);
		}
	}
}

void ApplicationManager::RecoverStatListFromUndoStatArray(int i)
{
	for(int j=0;j<StatCount;j++)
		delete StatList[j];
	for(int j=0;j<MaxCount;j++)
	{
		if(UndoStatArray[i][j]==NULL)
			StatList[j]=NULL;
		else
		{
			if(UndoStatArray[i][j]->GetType()==SMPL_ASSIGN)
				StatList[j]=new SmplAssign(*(SmplAssign*)UndoStatArray[i][j]);
			if(UndoStatArray[i][j]->GetType()==VAR_ASSIGN)
				StatList[j]=new VarAssign(*(VarAssign*)UndoStatArray[i][j]);
			if(UndoStatArray[i][j]->GetType()==SNGL_OP_ASSIGN)
				StatList[j]=new SnglOpAssign(*(SnglOpAssign*)UndoStatArray[i][j]);
			if(UndoStatArray[i][j]->GetType()==COND)
				StatList[j]=new Conditional(*(Conditional*)UndoStatArray[i][j]);
			if(UndoStatArray[i][j]->GetType()==READ)
				StatList[j]=new Read(*(Read*)UndoStatArray[i][j]);
			if(UndoStatArray[i][j]->GetType()==WRITE)
				StatList[j]=new Write(*(Write*)UndoStatArray[i][j]);
			if(UndoStatArray[i][j]->GetType()==START)
				StatList[j]=new Start(*(Start*)UndoStatArray[i][j]);
			if(UndoStatArray[i][j]->GetType()==END)
				StatList[j]=new End(*(End*)UndoStatArray[i][j]);
			delete UndoStatArray[i][j];
			UndoStatArray[i][j]=NULL;
		}
	}
	UndoStatListsUsed--;
	StatCount=UndoStatArrayStatCount[i];
}

void ApplicationManager::PushConnListInUndoConnArray()
{
	if(UndoConnListsUsed==10)
	{
		ShiftUndoConnListsLeft();
		CopyOfConnListInUndoConnArray(9);
		UndoConnArrayConnCount[9]=ConnCount;
	}
	else
	{
		CopyOfConnListInUndoConnArray(UndoConnListsUsed);
		UndoConnArrayConnCount[UndoConnListsUsed]=ConnCount;
		UndoConnListsUsed++;
	}
}

void ApplicationManager::ShiftUndoConnListsLeft()
{
	for(int i=0;i<9;i++)
	{
		for(int j=0;j<MaxCount;j++)
		{
			if(i==0)
				delete UndoConnArray[i][j];
			UndoConnArray[i][j]=UndoConnArray[i+1][j];
		}
	}
	for(int i=0;i<MaxCount;i++)
		UndoConnArray[9][i]=NULL;
	for(int i=0;i<9;i++)
	{
		UndoConnArrayConnCount[i]=UndoConnArrayConnCount[i+1];
		UndoConnArrayConnCount[i+1]=0;
	}
}

void ApplicationManager::CopyOfConnListInUndoConnArray(int i)
{
	for(int j=0;j<MaxCount;j++)
	{
		if(ConnList[j]==NULL)
			UndoConnArray[i][j]=NULL;
		else
			UndoConnArray[i][j]=new Connector(*ConnList[j]);
	}
}

void ApplicationManager::RecoverConnListFromUndoConnArray(int i)
{
	for(int j=0;j<ConnCount;j++)
		delete ConnList[j];
	for(int j=0;j<MaxCount;j++)
	{
		if(UndoConnArray[i][j]==NULL)
			ConnList[j]=NULL;
		else
		{
			ConnList[j]=new Connector(*UndoConnArray[i][j]);
			delete UndoConnArray[i][j];
			UndoConnArray[i][j]=NULL;
		}
	}
	UndoConnListsUsed--;
	ConnCount=UndoConnArrayConnCount[i];
}

bool ApplicationManager::MultiplySelected()
{
	if (SelectedStat[0]!=NULL)
		return true;
	else
		return false;
}
////////////////////////////////////////////////////////////////////////////////////
//Returns the selected statement
Statement *ApplicationManager::GetSelectedStatement() const
{	return pSelectedStat;	}

////////////////////////////////////////////////////////////////////////////////////
//Set the statement selected by the user
void ApplicationManager::SetSelectedStatement(Statement *pStat)
{
		if(pSelectedStat!=NULL)
			pSelectedStat->SetSelected(false);
		pSelectedStat=pStat;
		if(pStat!=NULL)
			pStat->SetSelected(true);
}

Statement* ApplicationManager::GetCopiedStatement() const
{return pCpdStat;}

void ApplicationManager::SetCopiedStatement(Statement *pStat)
{pCpdStat=pStat;}

Statement** const ApplicationManager::GetStatList()
{return StatList;}

Connector** const ApplicationManager::GetConnList()
{return ConnList;}

Statement** const ApplicationManager:: GetSelectedStat()
{return SelectedStat;}

Statement**  ApplicationManager:: GetCpdStat()
{return CpdStat;}

Statement** ApplicationManager::GetUndoStatArray(int i)
{return UndoStatArray[i];}

int ApplicationManager::GetUndoStatListsUsed()
{return UndoStatListsUsed;}

int ApplicationManager::GetUndoConnListsUsed()
{return UndoConnListsUsed;}

int ApplicationManager::GetStatCount()
{return StatCount;}

int ApplicationManager::GetConnCount()
{return ConnCount;}

void ApplicationManager::IncrementStatCount()
{StatCount++;}

void ApplicationManager::DecrementStatCount()
{StatCount--;}

void ApplicationManager::IncrementConnCount()
{ConnCount++;}

void ApplicationManager::DecrementConnCount()
{ConnCount--;}

void ApplicationManager::SaveFlowchart(ofstream &OutFile)
{
	OutFile<<StatCount<<endl;
	for (int i=0;i<StatCount;i++)
		StatList[i]->Save(OutFile);
	OutFile<<ConnCount<<endl;
	for (int i=0;i<ConnCount;i++)
		ConnList[i]->Save(OutFile);
	pOut->PrintMessage("Flowchart saved to \"Saved Flowchart.txt\"");
}

void ApplicationManager::LoadFlowchart(ifstream &Infile)
{
	string str,temp;
	int statements;
	getline(Infile,str);
	str+='\0';
	if(str[1]=='\0')
		temp=str[0];
	else if(str[2]=='\0')
		temp=str[0]+str[1];
	else if(str[3]=='\0')
		temp=str[0]+str[1]+str[2];
	statements=(int) round(stod(temp));
	Statement* Stat;
	Point P;
	P.x=0;
	P.y=0;
	Statement** LoadedStatements=new Statement*[statements];
	for(int i=0;i<statements;i++)
	{
		getline(Infile,str);
		if(str[0]=='S'&&str[1]=='M'&&str[2]=='P'&&str[3]=='L')
		{
			Stat=new SmplAssign(pOut,P);
			LoadedStatements[i]=Stat;
			AddStatement(Stat);
		}
		else if(str[0]=='V'&&str[1]=='A'&&str[2]=='R')
		{
			Stat=new VarAssign(pOut,P);
			LoadedStatements[i]=Stat;
			AddStatement(Stat);
		}
		else if(str[0]=='S'&&str[1]=='N'&&str[2]=='G'&&str[3]=='L'&&str[4]=='O'&&str[5]=='P')
		{
			Stat=new SnglOpAssign(pOut,P);
			LoadedStatements[i]=Stat;
			AddStatement(Stat);
		}
		else if(str[0]=='C'&&str[1]=='O'&&str[2]=='N'&&str[3]=='D')
		{
			Stat=new Conditional(pOut,P);
			LoadedStatements[i]=Stat;
			AddStatement(Stat);
		}
		else if(str[0]=='R'&&str[1]=='E'&&str[2]=='A'&&str[3]=='D')
		{
			Stat=new Read(pIn,pOut,P);
			LoadedStatements[i]=Stat;
			AddStatement(Stat);
		}
		else if(str[0]=='W'&&str[1]=='R'&&str[2]=='I'&&str[3]=='T'&&str[4]=='E')
		{
			Stat=new Write(pOut,P);
			LoadedStatements[i]=Stat;
			AddStatement(Stat);
		}
		else if(str[0]=='S'&&str[1]=='T'&&str[2]=='R'&&str[3]=='T')
		{
			Stat=new Start(pOut,P);
			LoadedStatements[i]=Stat;
			AddStatement(Stat);
		}
		else if(str[0]=='E'&&str[1]=='N'&&str[2]=='D')
		{
			Stat=new End(pOut,P);
			LoadedStatements[i]=Stat;
			AddStatement(Stat);
		}
	}
	Infile.close();
	Infile.open("Saved Flowchart.txt");
	getline(Infile,str);
	for(int i=0;i<statements;i++)
		LoadedStatements[i]->Load(Infile);
	int connectors;
	getline(Infile,str);
	str+='\0';
	if(str[1]=='\0')
		temp=str[0];
	else if(str[2]=='\0')
		temp=str[0]+str[1];
	else if(str[3]=='\0')
		temp=str[0]+str[1]+str[2];
	connectors=(int) round(stod(temp));
	Connector* Conn;
	for(int i=0;i<connectors;i++)
	{
		Conn=new Connector(Stat,Stat,this);
		Conn->Load(Infile);
		AddConn(Conn);
	}
}

bool ApplicationManager::ValidateFlowchart()
{
	int index=-1;
	for(int i=0; i<StatCount; i++)
	{
		if(StatList[i]->GetType()==START)
		{
			index=i;
			break;
		}
	}
	if(index==-1)
	{
		pOut->PrintMessage("Simulation cannot start; there are no Start statements");
		return false;
	}
	else
	{
		for(int j=index+1; j<StatCount; j++)
		{
			if(StatList[j]->GetType()==START)
			{
				pOut->PrintMessage("Simulation cannot start; more than one Start statement present");
				return false;
			}
		}
	}
	int Index=-1;
	for(int i=0; i<StatCount; i++)
	{
		if(StatList[i]->GetType()==END)
		{
			Index=i;
			break;
		}
	}
	if(Index==-1)
	{
		pOut->PrintMessage("Simulation cannot start; there are no End statements");
		return false;
	}
	else
	{
		for(int j=Index+1; j<StatCount; j++)
		{
			if(StatList[j]->GetType()==END)
			{
				pOut->PrintMessage("Simulation cannot start; more than one End statement present");
				return false;
			}
		}
	}
	bool NULLconnectors=false;
	for(int i=0; i<StatCount; i++)
	{
		Connector* pConn;
		if(StatList[i]->GetType()==SMPL_ASSIGN)
			pConn=((SmplAssign*)StatList[i])->getpConn();
		else if(StatList[i]->GetType()==VAR_ASSIGN)
			pConn=((VarAssign*)StatList[i])->getpConn();
		else if(StatList[i]->GetType()==SNGL_OP_ASSIGN)
			pConn=((SnglOpAssign*)StatList[i])->getpConn();
		else if(StatList[i]->GetType()==COND)
		{
			pConn=((Conditional*)StatList[i])->getpConn(true);
			Connector* pConn2=((Conditional*)StatList[i])->getpConn(false);
			if(pConn==NULL||pConn2==NULL)
			{
				pOut->PrintMessage("Simulation cannot start; chart is not fully connected");
				return false;
			}
		}
		else if(StatList[i]->GetType()==READ)
			pConn=((Read*)StatList[i])->getpConn();
		else if(StatList[i]->GetType()==WRITE)
			pConn=((Write*)StatList[i])->getpConn();
		else if(StatList[i]->GetType()==START)
			pConn=((Start*)StatList[i])->getpConn();
		if(StatList[i]->GetType()!=END)
		{
			if(pConn==NULL)
			{
				NULLconnectors=true;
				break;
			}
		}
	}
	if(NULLconnectors)
	{
		pOut->PrintMessage("Simulation cannot start; chart is not fully connected");
		return false;
	}
	else
	{
		pOut->PrintMessage("The flowchart is OK. Simulation can start");
		return true;
	}
}

//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//

//Draw all figures on the user interface
void ApplicationManager::UpdateInterface() const
{
	pOut->ClearDrawArea();
	//Draw all statements
	for(int i=0; i<StatCount; i++)
		StatList[i]->Draw();
	
	//Draw all connections
	for(int i=0; i<ConnCount; i++)
		ConnList[i]->Draw(pOut);

}
////////////////////////////////////////////////////////////////////////////////////
//Return a pointer to the input
Input *ApplicationManager::GetInput() const
{	return pIn; }
//Return a pointer to the output
Output *ApplicationManager::GetOutput() const
{	return pOut; }
////////////////////////////////////////////////////////////////////////////////////


//Destructor
ApplicationManager::~ApplicationManager()
{
	for(int i=0; i<StatCount; i++)
		delete StatList[i];
	for(int i=0; i<ConnCount; i++)
		delete ConnList[i];
	for(int i=0; i<MaxCount; i++)
	{
		if(SelectedStat[i]!=NULL)
			delete SelectedStat[i];
		else
			break;
	}
	for(int i=0; i<MaxCount; i++)
	{
		if(CpdStat[i]!=NULL)
			delete CpdStat[i];
		else
			break;
	}
	for(int i=0;i<10;i++)
	{
		for(int j=0;j<MaxCount;j++)
		{
			if(UndoStatArray[i][j]!=NULL)
				delete UndoStatArray[i][j];
		}
	}
	delete pIn;
	delete pOut;
}