#include "cmain.h"

extern CELL Board[256];//шахматная доска
extern COORD Coord256to64[256];
extern COORD Coord64to256[64];
extern SMove sMove_PrincipalVariation[MAX_PLY+5];//главная линия ходов

CMain cMain;

//-Конструктор класса--------------------------------------------------------
CMain::CMain()
{
 int width;
 int height;
 for(long n=1;n<=26;n++)
 {
  char name[255];
  sprintf(name,"/usr/share/QNXChess/Picture/%ld.tga",n);
  Figure[n]=LoadTGAFromFile(name,width,height);
  if (width!=36 || height!=36)
  {
   if (Figure[n]!=NULL) delete[](Figure[n]);
   Figure[n]=NULL;
  }
 }
 Horizontal=LoadTGAFromFile("/usr/share/QNXChess/Picture/horizontal.tga",width,height);
 Vertical=LoadTGAFromFile("/usr/share/QNXChess/Picture/vertical.tga",width,height);
 VerticalInvert=LoadTGAFromFile("/usr/share/QNXChess/Picture/vertical_invert.tga",width,height);
 HorizontalInvert=LoadTGAFromFile("/usr/share/QNXChess/Picture/horizontal_invert.tga",width,height);

 HumanColor=WHITE;
 ComputerColor=BLACK;
 char string[255];
 AddLog("--------------------------------------------------");
 AddLog("Новая игра за белых");
 time_t time_main=time(NULL);
 tm *tm_main=localtime(&time_main);
 sprintf(string,"%02i.%02i.%04i %02i:%02i:%02i",tm_main->tm_mday,tm_main->tm_mon+1,tm_main->tm_year+1900,tm_main->tm_hour,tm_main->tm_min,tm_main->tm_sec);
 AddLog(string); 
 AddLog("--------------------------------------------------");
 InversionBoard=false;
 EngineRun();
}
//-Деструктор класса---------------------------------------------------------
CMain::~CMain()
{  
 EngineStop();
 for(long n=1;n<=26;n++)
 {
  if (Figure[n]!=NULL) delete[](Figure[n]);
 }
 if (Horizontal!=NULL) delete[](Horizontal);
 if (Vertical!=NULL) delete[](Vertical);
 if (VerticalInvert!=NULL) delete[](VerticalInvert);
 if (HorizontalInvert!=NULL) delete[](HorizontalInvert);
}
//-Замещённые функции предка-----------------------------------------------
//-Новые функции класса------------------------------------------------------

//----------------------------------------------------------------------------------------------------
//открытие окна
//----------------------------------------------------------------------------------------------------
bool CMain::OpenWindow(void)
{
 SetWidgetText(ABW_PtText_Main_Move,"");
 Initialize();
 sMove.Coord256_PassedPawn=0;
 X1=-1;
 X2=-1;
 Y1=-1;
 Y2=-1;

 SelectX1=-1;
 SelectY1=-1;
 SelectX2=-1;
 SelectY2=-1;

 char string[255];
 AddText("Centurion Engine by da-nie");
 AddText("Версия движка от 30.04.2015");
 AddText("Используемые эвристики и настройки:");
 AddText("  Альфа-бета с амортизацией отказов");
 AddText("  Late Move Reduction");
 AddText("  Продление взятий");
 AddText("  Продление шахов");
 AddText("  Эвристика убийцы");
 AddText("  Итеративное углубление");
 AddText("  Сортировка фигур MVV/LVA");
 //AddText("  + стоимость пешки за своего ферзя");
 AddText("  Таблица поле-фигура");
 AddText("  Функция оценки 2.1");
 AddText("  Нулевой ход с редукцией 4");
 AddText("  Futility pruning");
 AddText("  Razoring"); 
 AddText("  Хэш таблица");
 sprintf(string,"  Глубина анализа, полуходов %i",MAX_DEPTH);
 AddText(string);
 sprintf(string,"  Глубина продлений, полуходов %i",MAX_LEVEL);
 AddText(string);
 AddText("--------------------------------------------------");
 AddText("Рокировка задаётся ходом короля.");
 AddText("Взятие проходной пешки - ");
 AddText("указанием битого поля.");
 AddText("Ходы выполняются правой и левой");
 AddText("кнопками мыши,либо с клавиатуры");
 AddText("(например, E2-E4).");
 AddText("--------------------------------------------------");
 AddText("");
 AddText("");
 AddText("");
 
 ClearComboBox(ABW_PtComboBox_Main_ChangeType);
 AddStringInComboBox(ABW_PtComboBox_Main_ChangeType,"Поменять пешку на коня");
 AddStringInComboBox(ABW_PtComboBox_Main_ChangeType,"Поменять пешку на слона");
 AddStringInComboBox(ABW_PtComboBox_Main_ChangeType,"Поменять пешку на ладью");
 AddStringInComboBox(ABW_PtComboBox_Main_ChangeType,"Поменять пешку на ферзя");
 SetSelectedItemInComboBox(ABW_PtComboBox_Main_ChangeType,4);
 return(true);
}
//----------------------------------------------------------------------------------------------------
//закрытие окна
//----------------------------------------------------------------------------------------------------
bool CMain::CloseWindow(void)
{
 return(true);	
}
//-Функции обработки сообщений класса----------------------------------------
//----------------------------------------------------------------------------------------------------
//нажали левой кнопкой мыши на форме
//----------------------------------------------------------------------------------------------------
void CMain::OnActivate_MouseButtonLeft(long x,long y)
{
 x-=20;
 y-=20;	 

 float sizex=(360)/10.0f;
 float sizey=(360)/10.0f;

 SelectX1=(long)(x/sizex);
 SelectY1=(long)(y/sizey);
 SelectX1=SelectX1-1;
 SelectY1=9-SelectY1-1;
 SelectX2=-1;
 SelectY2=-1;

 if (InversionBoard==true) 
 {
  SelectY1=7-SelectY1;
  SelectX1=7-SelectX1;
 }
 OnPaint();
}
//----------------------------------------------------------------------------------------------------
//нажали правой кнопкой мыши на форме
//----------------------------------------------------------------------------------------------------
void CMain::OnActivate_MouseButtonRight(long x,long y)
{
 x-=20;
 y-=20;	 
 float sizex=(360)/10.0f;
 float sizey=(360)/10.0f;

 SelectX2=(long)(x/sizex);
 SelectY2=(long)(y/sizey);
 SelectX2=SelectX2-1;
 SelectY2=9-SelectY2-1;

 if (InversionBoard==true) 
 {
  SelectY2=7-SelectY2;
  SelectX2=7-SelectX2;
 }

 if (SelectX1>=0 && SelectX1<=7 && SelectY1>=0 && SelectY1<=7) 
 {
  if (SelectX2>=0 && SelectX2<=7 && SelectY2>=0 && SelectY2<=7) 
  {
   OnPaint();  	
   if (Move(SelectX1,SelectY1,SelectX2,SelectY2)==true) ComputerAnswer();
  }
 } 
}
//----------------------------------------------------------------------------------------------------
//перерисовать картинку
//----------------------------------------------------------------------------------------------------
void CMain::OnPaint(void)
{
 long x;
 long y; 
 unsigned char *ImageBuffer=new unsigned char[(10*36)*(10*36)*3+1];
 memset(ImageBuffer,192,(10*36)*(10*36)*3+1);
 //рисуем шахматную доску
 for(x=0;x<8;x++)
 {
  for(y=0;y<8;y++)
  {
   long sprite=25;
   if (x%2==0 && y%2!=0 || x%2!=0 && y%2==0) sprite=25;
                                        else sprite=26;
   long type=Board[Coord64to256[(y<<3)|x]]&MASK_TYPE;
   long color=Board[Coord64to256[(y<<3)|x]]&MASK_COLOR;
   if (color==BLACK)
   {
    if (type==FIGURE_TYPE_PAWN)
	{
     if (x%2==0 && y%2!=0 || x%2!=0 && y%2==0) sprite=13;
                                          else sprite=19;
	}
    if (type==FIGURE_TYPE_KNIGHT)
	{
     if (x%2==0 && y%2!=0 || x%2!=0 && y%2==0) sprite=14;
                                          else sprite=20;
	}
    if (type==FIGURE_TYPE_BISHOP)
	{
     if (x%2==0 && y%2!=0 || x%2!=0 && y%2==0) sprite=15;
                                          else sprite=21;
	}
    if (type==FIGURE_TYPE_ROOK)
	{
     if (x%2==0 && y%2!=0 || x%2!=0 && y%2==0) sprite=16;
                                          else sprite=22;
	}
    if (type==FIGURE_TYPE_QUEEN)
	{
     if (x%2==0 && y%2!=0 || x%2!=0 && y%2==0) sprite=17;
                                          else sprite=23;
	}
    if (type==FIGURE_TYPE_KING)
	{
     if (x%2==0 && y%2!=0 || x%2!=0 && y%2==0) sprite=18;
                                          else sprite=24;
	}
   }
   if (color==WHITE)
   {
    if (type==FIGURE_TYPE_PAWN)
	{
     if (x%2==0 && y%2!=0 || x%2!=0 && y%2==0) sprite=1;
                                          else sprite=7;
	}
    if (type==FIGURE_TYPE_KNIGHT)
	{
     if (x%2==0 && y%2!=0 || x%2!=0 && y%2==0) sprite=2;
                                          else sprite=8;
	}
    if (type==FIGURE_TYPE_BISHOP)
	{
     if (x%2==0 && y%2!=0 || x%2!=0 && y%2==0) sprite=3;
                                          else sprite=9;
	}
    if (type==FIGURE_TYPE_ROOK)
	{
     if (x%2==0 && y%2!=0 || x%2!=0 && y%2==0) sprite=4;
                                          else sprite=10;
	}
    if (type==FIGURE_TYPE_QUEEN)
	{
     if (x%2==0 && y%2!=0 || x%2!=0 && y%2==0) sprite=5;
                                          else sprite=11;
	}
    if (type==FIGURE_TYPE_KING)
	{
     if (x%2==0 && y%2!=0 || x%2!=0 && y%2==0) sprite=6;
                                          else sprite=12;
	}
   }
   long select=0;
   if (x==X1 && y==Y1) select=1;
   if (x==X2 && y==Y2) select=1;

   if (x==SelectX1 && y==SelectY1) select=1;
   if (x==SelectX2 && y==SelectY2) select=1;
   long yb=7-y;
   long xb=x;
   if (InversionBoard==true) 
   {
	yb=y;
	xb=7-x;
   }
   if (Figure[sprite]!=NULL) DrawSprite((xb+1)*36,(yb+1)*36,36,36,Figure[sprite],10*36,10*36,ImageBuffer,select);
  }
 }
 if (InversionBoard==false)
 {
  if (Horizontal!=NULL) DrawSprite(1*36,0*36,36*8,36,Horizontal,10*36,10*36,ImageBuffer,false);
  if (Horizontal!=NULL) DrawSprite(1*36,9*36,36*8,36,Horizontal,10*36,10*36,ImageBuffer,false);
  if (Vertical!=NULL) DrawSprite(0*36,1*36,36,36*8,Vertical,10*36,10*36,ImageBuffer,false);
  if (Vertical!=NULL) DrawSprite(9*36,1*36,36,36*8,Vertical,10*36,10*36,ImageBuffer,false);
 }
 else
 {
  if (HorizontalInvert!=NULL) DrawSprite(1*36,0*36,36*8,36,HorizontalInvert,10*36,10*36,ImageBuffer,false);
  if (HorizontalInvert!=NULL) DrawSprite(1*36,9*36,36*8,36,HorizontalInvert,10*36,10*36,ImageBuffer,false);
  if (VerticalInvert!=NULL) DrawSprite(0*36,1*36,36,36*8,VerticalInvert,10*36,10*36,ImageBuffer,false);
  if (VerticalInvert!=NULL) DrawSprite(9*36,1*36,36,36*8,VerticalInvert,10*36,10*36,ImageBuffer,false);
 }
 PhDim_t ImageSize;
 int ImageBPL=3*36*10;
 ImageSize.w=36*10;
 ImageSize.h=36*10; 
 PhPoint_t pos;
 pos.x=20;
 pos.y=20;
 PgDrawImage(ImageBuffer,Pg_IMAGE_DIRECT_888,&pos,&ImageSize,ImageBPL,0);

 delete(ImageBuffer);
}
//----------------------------------------------------------------------------------------------------
//нажали "сделать ход"
//----------------------------------------------------------------------------------------------------
void CMain::OnActivate_Button_Move(void)
{
 char string[255];
 char *text=GetWidgetText(ABW_PtText_Main_Move);
 if (strlen(text)!=5) return;
 strcpy(string,text);
 if (string[2]!='-') return;
 long x1=-1;
 long y1=-1;
 if (string[0]>='a' && string[0]<='h') x1=string[0]-'a';
 if (string[0]>='A' && string[0]<='H') x1=string[0]-'A';
 if (string[1]>='1' && string[1]<='8') y1=string[1]-'1';
 long x2=-1;
 long y2=-1;
 if (string[3]>='a' && string[3]<='h') x2=string[3]-'a';
 if (string[3]>='A' && string[3]<='H') x2=string[3]-'A';
 if (string[4]>='1' && string[4]<='8') y2=string[4]-'1';
 if (x1<0 || y1<0 || x2<0 || y2<0) return;
 bool res=Move(x1,y1,x2,y2);
 if (res==true) ComputerAnswer();
}
//----------------------------------------------------------------------------------------------------
//нажали "сохранить состояние"
//----------------------------------------------------------------------------------------------------
void CMain::OnActivate_Button_SaveState(void)
{
 SaveState();
}
//----------------------------------------------------------------------------------------------------
//нажали "загрузить состояние"
//----------------------------------------------------------------------------------------------------
void CMain::OnActivate_Button_LoadState(void)
{
 LoadState();
 OnPaint();
}
//----------------------------------------------------------------------------------------------------
//нажали "начать за чёрных"
//----------------------------------------------------------------------------------------------------
void CMain::OnActivate_Button_InitBlack(void)
{
 char string[255];
 AddLog("--------------------------------------------------");
 AddLog("Новая игра за чёрных");
 time_t time_main=time(NULL);
 tm *tm_main=localtime(&time_main);
 sprintf(string,"%02i.%02i.%04i %02i:%02i:%02i",tm_main->tm_mday,tm_main->tm_mon+1,tm_main->tm_year+1900,tm_main->tm_hour,tm_main->tm_min,tm_main->tm_sec);
 AddLog(string); 
 AddLog("--------------------------------------------------");

 HumanColor=BLACK;
 ComputerColor=WHITE;
 Initialize();
 sMove.Coord256_PassedPawn=0;
 X1=-1;
 X2=-1;
 Y1=-1;
 Y2=-1;

 SelectX1=-1;
 SelectY1=-1;
 SelectX2=-1;
 SelectY2=-1;
 OnPaint();
 //вызываем расчёт хода компьютером 
 ComputerAnswer();
 OnPaint();
}
//----------------------------------------------------------------------------------------------------
//нажали "начать за белых"
//----------------------------------------------------------------------------------------------------
void CMain::OnActivate_Button_InitWhite(void)
{
 char string[255];
 AddLog("--------------------------------------------------");
 AddLog("Новая игра за белых");
 time_t time_main=time(NULL);
 tm *tm_main=localtime(&time_main);
 sprintf(string,"%02i.%02i.%04i %02i:%02i:%02i",tm_main->tm_mday,tm_main->tm_mon+1,tm_main->tm_year+1900,tm_main->tm_hour,tm_main->tm_min,tm_main->tm_sec);
 AddLog(string); 
 AddLog("--------------------------------------------------");

 HumanColor=WHITE;
 ComputerColor=BLACK;
 Initialize();
 sMove.Coord256_PassedPawn=0;
 X1=-1;
 X2=-1;
 Y1=-1;
 Y2=-1;

 SelectX1=-1;
 SelectY1=-1;
 SelectX2=-1;
 SelectY2=-1;

 OnPaint();
}
//----------------------------------------------------------------------------------------------------
//нажали "повернуть доску"
//----------------------------------------------------------------------------------------------------
void CMain::OnActivate_Button_RotateBoard(void)
{
 if (InversionBoard==true) InversionBoard=false;
                      else InversionBoard=true;
 OnPaint();
}
//-Новые функции класса------------------------------------------------------

//----------------------------------------------------------------------------------------------------
//добавить ход в список ходов
//----------------------------------------------------------------------------------------------------
void CMain::AddMoveToList(char *text,long x1,long y1,long x2,long y2)
{
 char fname[255];
 char string[255];
 sprintf(fname," ");
 CELL type=Board[Coord64to256[x2|(y2<<3)]]&MASK_TYPE;
 if (type==FIGURE_TYPE_PAWN) sprintf(fname,"Пешка ");
 if (type==FIGURE_TYPE_KING) sprintf(fname,"Король ");
 if (type==FIGURE_TYPE_QUEEN) sprintf(fname,"Ферзь ");
 if (type==FIGURE_TYPE_ROOK) sprintf(fname,"Ладья ");
 if (type==FIGURE_TYPE_KNIGHT) sprintf(fname,"Конь ");   
 if (type==FIGURE_TYPE_BISHOP) sprintf(fname,"Слон ");
 sprintf(string,"%s %s%c%c-%c%c",text,fname,'A'+x1,'1'+y1,'A'+x2,'1'+y2);
 AddLog(string);
 AddText(string);
}
//----------------------------------------------------------------------------------------------------
//добавить ход в список ходов основного варианта
//----------------------------------------------------------------------------------------------------
void CMain::AddMoveToPrincipalList(long x1,long y1,long x2,long y2)
{
 char string[255];
 sprintf(string,"%c%c-%c%c",'A'+x1,'1'+y1,'A'+x2,'1'+y2);
 AddStringInList(ABW_PtList_Main_PrincipalMove,string);
 SetTopItemPosInList(ABW_PtList_Main_PrincipalMove,0);
}
//----------------------------------------------------------------------------------------------------
//вычислить ответный ход компьютера
//----------------------------------------------------------------------------------------------------
void CMain::ComputerAnswer(void)
{
 char string[255];
 //вызываем рассчёт хода компьютером
 uint64_t cps=SYSPAGE_ENTRY(qtime)->cycles_per_sec;
 uint64_t begin=ClockCycles();
 
 long positions;
 long levels;
 long score;
 SMove sMove_Computer=Search(ComputerColor,sMove.Coord256_PassedPawn,positions,levels,score,MAX_DEPTH);//поиск лучшего хода
 sMove_Computer.Coord256_PassedPawn=sMove.Coord256_PassedPawn;
 sMove=sMove_Computer;
 COORD coord64_1=Coord256to64[sMove.Coord256_1];
 COORD coord64_2=Coord256to64[sMove.Coord256_2];
 long x1=coord64_1&7;
 long x2=coord64_2&7;
 long y1=coord64_1>>3;
 long y2=coord64_2>>3;
 
 double delta=((double)(ClockCycles()-begin))/(double)(cps);
 sprintf(string,"Анализировалось: %ld позиций",positions);
 AddText(string);
 sprintf(string,"Глубина продлений,полуходов: %ld",levels);
 AddText(string);
 sprintf(string,"Потрачено: %.2f секунд",delta);
 AddText(string);
 float speed=((float)positions)/(float)(delta);
 sprintf(string,"Скорость: %.0f поз./сек.",speed);
 AddText(string);  
 ClearList(ABW_PtList_Main_PrincipalMove);
 AddStringInList(ABW_PtList_Main_PrincipalMove,"PVS");
 for(long n=0;n<MAX_DEPTH;n++)
 {
  COORD coord64_1p=Coord256to64[sMove_PrincipalVariation[n].Coord256_1];
  COORD coord64_2p=Coord256to64[sMove_PrincipalVariation[n].Coord256_2];
  long xp1=coord64_1p&7;
  long xp2=coord64_2p&7;
  long yp1=coord64_1p>>3;
  long yp2=coord64_2p>>3;
  if (xp1==xp2 && yp1==yp2) break;
  AddMoveToPrincipalList(xp1,yp1,xp2,yp2);
 }

 X1=x1;
 Y1=y1;
 X2=x2;
 Y2=y2;
 SelectX1=-1;
 SelectY1=-1;
 SelectX2=-1;
 SelectY2=-1;
 if (Move_MoveOn(ComputerColor,(COORD)x1,(COORD)y1,(COORD)x2,(COORD)y2,sMove.Coord256_PassedPawn,sMove.NewFigureType)==ENGINE_FALSE)
 {
  if (Move_CheckKing(ComputerColor)==ENGINE_FALSE)
  {
   AddText("ПАТ.");
   AddLog("ПАТ.");
  }
 } 
 else AddMoveToList("C:",x1,y1,x2,y2);
 float scoref=-static_cast<float>(score)/static_cast<float>(WEIGHT_PAWN);
 sprintf(string,"Оценка ситуации:%.2f",scoref);
 AddText(string);
 if (ComputerColor==WHITE) score=-score;
 if (score>WEIGHT_INFINITY-MAX_LEVEL) 
 {
  long depth=WEIGHT_INFINITY-score-1;
  if (depth>0) 
  {
   sprintf(string,"МАТ белым через %ld полухода!",depth);
   AddText(string);
   AddLog(string);
  }
  else
  {
   AddText("МАТ белым!");
   AddLog("МАТ белым!");
  }
 }
 if (score<-WEIGHT_INFINITY+MAX_LEVEL) 
 {
  long depth=WEIGHT_INFINITY+score-1;
  if (depth>0)
  {
   sprintf(string,"МАТ чёрным через %ld полухода!",depth);
   AddText(string);
   AddLog(string);
  }
  else
  {
   AddText("МАТ чёрным!");
   AddLog("МАТ чёрным!");
  }
 }
 AddText("--------------------------------------------------");
 OnPaint();
}

//-Новые функции класса------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//сделать ход
//----------------------------------------------------------------------------------------------------
bool CMain::Move(long x1,long y1,long x2,long y2)
{
 //сделать ход
 COORD coord64=x1|(y1<<3);
 CELL cell=Board[Coord64to256[coord64]];
 FIGURE_TYPE type=cell&MASK_TYPE;
 if (Move_MoveOn(HumanColor,(COORD)x1,(COORD)y1,(COORD)x2,(COORD)y2,sMove.Coord256_PassedPawn,FIGURE_TYPE_QUEEN)==ENGINE_TRUE)
 {
  COORD coord64_2=x2|(y2<<3);
  COORD coord256_2=Coord64to256[coord64_2];
  CELL b=Board[coord256_2];
  if ((HumanColor==WHITE && type==FIGURE_TYPE_PAWN && y2==7) || (HumanColor==BLACK && type==FIGURE_TYPE_PAWN && y2==0))
  {
   CELL new_type=FIGURE_TYPE_KNIGHT;
   //считаем тип новой фигуры из списка
   int selected=GetSelectedItemInComboBox(ABW_PtComboBox_Main_ChangeType);
   if (selected==1) new_type=FIGURE_TYPE_KNIGHT;
   if (selected==2) new_type=FIGURE_TYPE_BISHOP;
   if (selected==3) new_type=FIGURE_TYPE_ROOK;
   if (selected==4) new_type=FIGURE_TYPE_QUEEN;
   b=(b&(CELL_FULL_VALUE^MASK_TYPE))|new_type;
   Board[coord256_2]=b;
  }
  long EvaluateValue=Score_Evaluate(WHITE);  
  AddMoveToList("H:",x1,y1,x2,y2);
  SetWidgetText(ABW_PtText_Main_Move,"");
  X1=-1;
  Y1=-1;
  X2=-1;
  Y2=-1;
  OnPaint();
  return(true);
 }
 else AddMoveToList("Ошибочный ход:",x1,y1,x2,y2);  
 OnPaint();
 return(false);
}

//-Прочее--------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
//добавить текст в список
//----------------------------------------------------------------------------------------------------
void CMain::AddText(char *string)
{
 AddStringInList(ABW_PtList_Main_Log,string);
 unsigned short size=GetListSize(ABW_PtList_Main_Log);
 SetTopItemPosInList(ABW_PtList_Main_Log,size);   
}
//----------------------------------------------------------------------------------------------------
//отрисовать спрайт
//----------------------------------------------------------------------------------------------------
void CMain::DrawSprite(long x,long y,long s_width,long s_height,unsigned char *s_ptr,long width,long height,unsigned char *i_ptr,long select)
{
 for(long xp=0;xp<s_width;xp++)
 {
  for(long yp=0;yp<s_height;yp++)
  {
   long offsetb=(x+xp+(y+yp)*width)*3;
   long offsetp=(xp+yp*s_width)*3;   
   unsigned char b=s_ptr[offsetp];
   unsigned char g=s_ptr[offsetp+1];
   unsigned char r=s_ptr[offsetp+2];
   if (select==1)
   {
    if (xp<3 || xp>s_width-3 || yp<3 || yp>=s_height-3)
	{
     r=64;
	 g=0;
	 b=255;
	}
   }
   if (select==2)
   {
    if (xp<3 || xp>s_width-3 || yp<3 || yp>=s_height-3)
	{
     r=127;
	 g=127;
	 b=255;
	}
   }
   i_ptr[offsetb]=b;
   i_ptr[offsetb+1]=g;
   i_ptr[offsetb+2]=r;
  }
 }
}
//----------------------------------------------------------------------------------------------------
//добавить в лог-файл текст
//----------------------------------------------------------------------------------------------------
void CMain::AddLog(char *string)
{
 FILE *file=fopen("/var/log/qnxchess_log.txt","ab");
 if (file==NULL) return;
 fprintf(file,"%s\r\n",string);
 fclose(file);
}
