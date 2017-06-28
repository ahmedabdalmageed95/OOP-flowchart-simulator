#include "Output.h"
#include "..\ApplicationManager.h"
#include "..\CMUgraphicsLib\auxil.h"

Output::Output()
{
	//Initialize user interface parameters
	UI.width = 900;
	UI.height = 700;
	UI.wx = 15;
	UI.wy =15;

	UI.AppMode = DESIGN;	//Design Mode is the default mode

	UI.StBrWdth = 50;
	UI.TlBrWdth = 50;
	UI.MnItWdth = 80;

	UI.DrawClr = CYAN;
	UI.HiClr = color(255,75,75);
	UI.MsgClr = RED;

	//Create the output window
	pWind = CreateWind(UI.width, UI.height, UI.wx, UI.wy);
	//Change the title
	pWind->ChangeTitle("Programming Techniques Project");
	pWind->SetPen(RED,3);

	CreateDesignToolBar();
	CreateStatusBar();
	ClearDrawArea();
}

void Output::WindowPause()
{
	Pause(100);
}


Input* Output::CreateInput(ApplicationManager* pManager)
{
	Input* pIn = new Input(pWind,pManager);
	return pIn;
}

//======================================================================================//
//								Interface Functions										//
//======================================================================================//

window* Output::CreateWind(int wd, int h, int x, int y)
{
	return new window(wd, h, x, y);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::CreateStatusBar()
{
	pWind->SetPen(BLACK,2);
	pWind->DrawLine(0, UI.height-UI.StBrWdth, UI.width, UI.height-UI.StBrWdth);
}
//////////////////////////////////////////////////////////////////////////////////////////
//Draws the Design Menu
void Output::CreateDesignToolBar()
{
	UI.AppMode = DESIGN;
	UI.TlBrWdth=(int) round(2*UI.width/15);
	UI.MnItWdth=(int) round(UI.width/15);
	pWind->DrawImage("images\\Exit.jpg",0,0,UI.width/15,UI.width/15);
	pWind->DrawImage("images\\Save.jpg",1*UI.MnItWdth,0,UI.MnItWdth,UI.MnItWdth);
	pWind->DrawImage("images\\Load.jpg",2*UI.MnItWdth,0,UI.MnItWdth,UI.MnItWdth);
	pWind->DrawImage("images\\Undo.jpg",3*UI.MnItWdth,0,UI.MnItWdth,UI.MnItWdth);
	pWind->DrawImage("images\\SimpleAssign.jpg",4*UI.MnItWdth,0,UI.MnItWdth,UI.MnItWdth);
	pWind->DrawImage("images\\VariableAssign.jpg",5*UI.MnItWdth,0,UI.MnItWdth,UI.MnItWdth);
	pWind->DrawImage("images\\OperatorAssign.jpg",6*UI.MnItWdth,0,UI.MnItWdth,UI.MnItWdth);
	pWind->DrawImage("images\\Condition.jpg",7*UI.MnItWdth,0,UI.MnItWdth,UI.MnItWdth);
	pWind->DrawImage("images\\Read.jpg",8*UI.MnItWdth,0,UI.MnItWdth,UI.MnItWdth);
	pWind->DrawImage("images\\Write.jpg",9*UI.MnItWdth,0,UI.MnItWdth,UI.MnItWdth);
	pWind->DrawImage("images\\Start.jpg",10*UI.MnItWdth,0,UI.MnItWdth,UI.MnItWdth);
	pWind->DrawImage("images\\End.jpg",11*UI.MnItWdth,0,UI.MnItWdth,UI.MnItWdth);
	pWind->DrawImage("images\\Connector.jpg",12*UI.MnItWdth,0,UI.MnItWdth,UI.MnItWdth);
	pWind->DrawImage("images\\Multiple.jpg",13*UI.MnItWdth,0,UI.MnItWdth,UI.MnItWdth);
	pWind->DrawImage("images\\Edit.jpg",14*UI.MnItWdth,0,UI.MnItWdth,UI.MnItWdth);
	pWind->DrawImage("images\\Comment.jpg",0*UI.MnItWdth,UI.MnItWdth,UI.MnItWdth,UI.MnItWdth);
	pWind->DrawImage("images\\Copy.jpg",1*UI.MnItWdth,UI.MnItWdth,UI.MnItWdth,UI.MnItWdth);
	pWind->DrawImage("images\\Cut.jpg",2*UI.MnItWdth,UI.MnItWdth,UI.MnItWdth,UI.MnItWdth);
	pWind->DrawImage("images\\Paste.jpg",3*UI.MnItWdth,UI.MnItWdth,UI.MnItWdth,UI.MnItWdth);
	pWind->DrawImage("images\\Del.jpg",4*UI.MnItWdth,UI.MnItWdth,UI.MnItWdth,UI.MnItWdth);
	pWind->DrawImage("images\\Simulation.jpg",5*UI.MnItWdth,UI.MnItWdth,UI.MnItWdth,UI.MnItWdth);
	pWind->SetPen(BLACK,2);
	for(int i=1;i<=14;i++)
		pWind->DrawLine(i*UI.MnItWdth,0,i*UI.MnItWdth,(int) round(0.5*UI.TlBrWdth));
	pWind->DrawLine(0, (int) round(0.5*UI.TlBrWdth), UI.width, (int) round(0.5*UI.TlBrWdth));
	for(int i=1;i<=6;i++)
		pWind->DrawLine(i*UI.MnItWdth,(int) round(0.5*UI.TlBrWdth),i*UI.MnItWdth,UI.TlBrWdth);
	pWind->DrawLine(0, UI.TlBrWdth, UI.width, UI.TlBrWdth);
}


void Output::CreateSimulationToolBar()
{
	UI.AppMode = SIMULATION;
	pWind->SetPen(WHITE);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0,0,UI.width,UI.TlBrWdth+2);
	UI.TlBrWdth=UI.width/15;
	UI.MnItWdth=UI.TlBrWdth;
	pWind->DrawImage("images\\Exit.jpg",0,0,UI.MnItWdth,UI.TlBrWdth);
	pWind->DrawImage("images\\simulation_mode\\Validate.jpg",1*UI.MnItWdth,0,UI.MnItWdth,UI.TlBrWdth);
	pWind->DrawImage("images\\simulation_mode\\Run.jpg",2*UI.MnItWdth,0,UI.MnItWdth,UI.TlBrWdth);
	pWind->DrawImage("images\\simulation_mode\\StepByStep.jpg",3*UI.MnItWdth,0,UI.MnItWdth,UI.TlBrWdth);
	pWind->DrawImage("images\\simulation_mode\\Generate.jpg",4*UI.MnItWdth,0,UI.MnItWdth,UI.TlBrWdth);
	pWind->DrawImage("images\\simulation_mode\\Design.jpg",5*UI.MnItWdth,0,UI.MnItWdth,UI.TlBrWdth);
	pWind->SetPen(BLACK,2);
	for(int i=1;i<=6;i++)
		pWind->DrawLine(i*UI.MnItWdth,0,i*UI.MnItWdth,UI.TlBrWdth);
	pWind->DrawLine(0, UI.TlBrWdth, UI.width, UI.TlBrWdth);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::ClearStatusBar()
{
	//Clear Status bar by drawing a filled white rectangle
	pWind->SetPen(BLACK,2);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, UI.height - UI.StBrWdth, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::ClearDrawArea()
{
	pWind->SetPen(LIGHTGRAY, 1);
	pWind->SetBrush(LIGHTGRAY);
	pWind->DrawRectangle(0, UI.TlBrWdth+1, UI.width, UI.height - UI.StBrWdth);	
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::PrintMessage(string msg)	//Prints a message on status bar
{
	ClearStatusBar();	//First clear the status bar
	
	pWind->SetPen(UI.MsgClr, 50);
	pWind->SetFont(20, BOLD , BY_NAME, "Arial");   
	pWind->DrawString(10, UI.height - (int) (UI.StBrWdth/1.5), msg);
}

void Output::PrintDouble(double d, string str, int x, int y)
{
	pWind->SetPen(UI.MsgClr, 50);
	pWind->SetFont(20, BOLD , BY_NAME, "Arial");
	int strwidth,strheight;
	pWind->GetStringSize(strwidth,strheight,str);
	pWind->DrawDouble(x+strwidth,y,d);
}

//======================================================================================//
//								Statements Drawing Functions								//
//======================================================================================//

//Draw assignment statement and write the "Text" on it
void Output::DrawAssign(Point Left, string Text, bool Selected)
{
	int textwidth,textheight;
	pWind->SetPen(BLACK,1);
	if(Selected)	//if stat is selected, it should be highlighted
		pWind->SetBrush(UI.HiClr);	//use highlighting color
	else
		pWind->SetBrush(UI.DrawClr);	//use normal color
	pWind->GetStringSize(textwidth,textheight,Text);
	//Draw the statement block rectangle
	pWind->DrawRectangle(Left.x, Left.y, Left.x+textwidth+20, Left.y+textheight+20);
		
	//Write statement text
	pWind->SetPen(BLACK, 2);
	pWind->DrawString(Left.x+10, Left.y+10, Text);
}

void Output::DrawStartEnd(string type, Point Left, bool Selected)
{
	pWind->SetPen(BLACK,1);
	if(Selected)	//if stat is selected, it should be highlighted
		pWind->SetBrush(UI.HiClr);	//use highlighting color
	else
		pWind->SetBrush(UI.DrawClr);	//use normal color
	int textwidth,textheight;
	pWind->GetStringSize(textwidth,textheight,type);
	pWind->DrawEllipse(Left.x,Left.y,Left.x+textwidth+80,Left.y+textheight+40);
	pWind->SetPen(BLACK, 2);
	pWind->DrawString(Left.x+40,Left.y+20,type);
}

void Output::DrawConditional(Point Left, string Text, bool Selected)
{
	int textwidth,textheight;
	pWind->GetStringSize(textwidth,textheight,Text);
	pWind->SetPen(BLACK,1);
	if(Selected)	//if stat is selected, it should be highlighted
		pWind->SetBrush(UI.HiClr);	//use highlighting color
	else
		pWind->SetBrush(UI.DrawClr);	//use normal color
	Point P1,P2,P3,P4;
	P1=Left;
	P3.x=P1.x+textwidth+40; P3.y=P1.y;
	P2.x=P4.x=(P3.x+P1.x)/2;
	P2.y=P1.y-(P3.x-P1.x)/2;
	P4.y=P2.y+(P3.x-P1.x);
	int xpoints[]={P1.x,P2.x,P3.x,P4.x};
	int ypoints[]={P1.y,P2.y,P3.y,P4.y};
	pWind->DrawPolygon(xpoints,ypoints,4,FILLED);
	pWind->DrawLine(P1.x-50,P1.y,P1.x,P1.y);
	pWind->DrawLine(P3.x,P3.y,P3.x+50,P3.y);
	pWind->DrawString(P1.x-30,P1.y-20,"Yes");
	pWind->DrawString(P3.x+30,P3.y-20,"No");
	pWind->SetPen(BLACK, 2);
	pWind->DrawString(Left.x+20,(int) round(Left.y-0.5*textheight),Text);
}

void Output::DrawIO(Point Left, string type, string Text, bool Selected)
{
	Point P1=Left;
	Point P2,P3,P4;
	int width,height;
	pWind->GetStringSize(width,height,type+" "+Text);
	pWind->SetPen(BLACK,1);
	if(Selected)	//if stat is selected, it should be highlighted
		pWind->SetBrush(UI.HiClr);	//use highlighting color
	else
		pWind->SetBrush(UI.DrawClr);	//use normal color
	P3.x=(int) round(P1.x-height/tan(3.1415/3)); P3.y=P1.y+height+20;
	P2.x=P1.x+P1.x-P3.x+width; P2.y=P1.y;
	P4.x=P3.x+P2.x-P1.x; P4.y=P3.y;
	int xpoints[]={P1.x,P2.x,P4.x,P3.x};
	int ypoints[]={P1.y,P2.y,P4.y,P3.y};
	pWind->DrawPolygon(xpoints,ypoints,4,FILLED);
	pWind->SetPen(BLACK, 2);
	pWind->DrawString(P1.x,P1.y+10,type+" "+Text);
}

void Output:: DrawConnector(Point a, Point b, bool selected)
{
	if (selected)	//if stat is selected, it should be highlighted
		pWind->SetPen(UI.HiClr, 3);	//use highlighting color
	else
		pWind->SetPen(BLACK, 1);	//use normal color
	if (a.x == b.x && a.y<b.y)
	{
		pWind->DrawLine(a.x, a.y, b.x, b.y);
		pWind->DrawLine(b.x - 5, b.y- 10, b.x, b.y);
		pWind->DrawLine(b.x + 5, b.y - 10, b.x, b.y);
    }
	else if (abs(a.x-b.x)<=20&&a.y>b.y)
	{
		pWind->DrawLine(a.x,a.y,a.x,a.y+20);
		pWind->DrawLine(a.x,a.y+20,a.x-50,a.y+20);
		pWind->DrawLine(a.x-50,a.y+20,a.x-50,b.y-20);
		pWind->DrawLine(a.x-50,b.y-20,b.x,b.y-20);
		pWind->DrawLine(b.x,b.y-20,b.x,b.y);
		pWind->DrawLine(b.x-5,b.y-10,b.x,b.y);
		pWind->DrawLine(b.x+5,b.y-10,b.x,b.y);
	}
	else if(a.x<b.x&&a.y>b.y-30||a.x>b.x&&a.y>b.y-30)
	{
		pWind->DrawLine(a.x,a.y,a.x,a.y+20);
		pWind->DrawLine(a.x,a.y+20,(a.x+b.x)/2,a.y+20);
		pWind->DrawLine((a.x+b.x)/2,a.y+20,(a.x+b.x)/2,b.y-20);
		pWind->DrawLine((a.x+b.x)/2,b.y-20,b.x,b.y-20);
		pWind->DrawLine(b.x,b.y-20,b.x,b.y);
		pWind->DrawLine(b.x-5,b.y-10,b.x,b.y);
		pWind->DrawLine(b.x+5,b.y-10,b.x,b.y);
	}
	else if(a.x<b.x&&a.y<b.y||a.x>b.x&&a.y<b.y)
	{
		pWind->DrawLine(a.x,a.y,a.x,(a.y+b.y)/2);
		pWind->DrawLine(a.x,(a.y+b.y)/2,b.x,(a.y+b.y)/2);
		pWind->DrawLine(b.x,(a.y+b.y)/2,b.x,b.y);
		pWind->DrawLine(b.x-5,b.y-10,b.x,b.y);
		pWind->DrawLine(b.x+5,b.y-10,b.x,b.y);
	}
}

void Output::GetAssignPoints(Point left, string text, Point &in, Point &out)
{
	int textwidth,textheight;
	pWind->GetStringSize(textwidth,textheight,text);
	in.x=out.x=left.x+(textwidth+20)/2;
	in.y=left.y;
	out.y=left.y+textheight+20;
}

void Output::GetConditionalPoints(Point left, string text, Point &in, Point &yesOut, Point &noOut)
{
	int textwidth,textheight;
	pWind->GetStringSize(textwidth,textheight,text);
	in.x=(int) round(left.x+0.5*(textwidth+20*2));
	in.y=(int) round(left.y-0.5*(textwidth+20*2));
	yesOut.x=left.x-50;
	yesOut.y=left.y;
	noOut.x=left.x+2*(in.x-left.x)+50;
	noOut.y=left.y;
}

void Output::GetIOPoints(Point left, string text, Point &in, Point &out)
{
	int textwidth,textheight;
	pWind->GetStringSize(textwidth,textheight,text);
	in.x=(int) round(left.x-textheight/tan(3.1415/3)+(2*textheight/tan(3.1415/3)+textwidth)/2);
	in.y=left.y;
	out.x=in.x;
	out.y=left.y+textheight+20;
}

void Output::GetStartPoints(Point left, string text, Point &out)
{
	int textwidth,textheight;
	pWind->GetStringSize(textwidth,textheight,text);
	out.x=left.x+(textwidth+80)/2;
	out.y=left.y+textheight+40;
}

void Output::GetEndPoints(Point left, string text, Point &in)
{
	int textwidth,textheight;
	pWind->GetStringSize(textwidth,textheight,text);
	in.x=left.x+(textwidth+80)/2;
	in.y=left.y;
}
//////////////////////////////////////////////////////////////////////////////////////////
Output::~Output()
{
	delete pWind;
}