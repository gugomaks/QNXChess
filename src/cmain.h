#ifndef CMAIN_H
#define CMAIN_H

/* Standard headers */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/* Local headers */
#include "ablibs.h"
#include "abimport.h"
#include "proto.h"

#include "engine.h"
#include "tga.h"
#include "gui.h"

class CMain
{
 protected:
  //-Переменные класса-------------------------------------------------------
  unsigned char *Figure[27];//картинки фигур
  unsigned char *Horizontal;//картинка горизонтали
  unsigned char *Vertical;//картинка вертикали
  unsigned char *VerticalInvert;//инверсная картинка вертикали
  unsigned char *HorizontalInvert;//инверсная картинка горизонтали
  //координаты курсоров
  long X1;
  long Y1;
  long X2;
  long Y2;

  long SelectX1;
  long SelectY1;
  long SelectX2;
  long SelectY2;
  
  SMove sMove;
  
  long HumanColor;//цвет игрока
  long ComputerColor;//цвет компьютера

  bool InversionBoard;//инвертирована ли доска

  //-Функции класса----------------------------------------------------------
  //-Прочее------------------------------------------------------------------
 public:
  //-Конструктор класса------------------------------------------------------
  CMain();
  //-Деструктор класса-------------------------------------------------------
  ~CMain();
  //-Переменные класса-------------------------------------------------------
  //-Замещённые функции предка-----------------------------------------------
  //-Новые функции класса----------------------------------------------------
  bool OpenWindow(void);//открытие окна
  bool CloseWindow(void);//закрытие окна
  void OnPaint(void);//отрисовать доску
  
  //-Функции обработки сообщений класса--------------------------------------
  void OnActivate_Button_Move(void);//нажали "сделать ход"
  void OnActivate_Button_SaveState(void);//нажали "сохранить состояние"
  void OnActivate_Button_LoadState(void);//нажали "загрузить состояние"
  void OnActivate_Button_InitWhite(void);//нажали "начать игру за белых"
  void OnActivate_Button_InitBlack(void);//нажали "начать игру за чёрных"
  void OnActivate_Button_RotateBoard(void);//нажали "перевернуть доску"
  void OnActivate_MouseButtonLeft(long x,long y);//нажали левой кнопкой мыши на форме
  void OnActivate_MouseButtonRight(long x,long y);//нажали правой кнопкой мыши на форме
  //-Новые функции класса----------------------------------------------------
  int LoadBitmap(char *FileName,unsigned char *Bitmap);//загрузить изображение
  void AddMoveToList(char *text,long x1,long y1,long x2,long y2);//добавить ход в список ходов
  void AddMoveToPrincipalList(long x1,long y1,long x2,long y2);//добавить ход в список основного варианта
  void ComputerAnswer(void);//вычислить ответный ход компьютера
  void AddText(char *string);//добавить текст в список
  void DrawSprite(long x,long y,long s_width,long s_height,unsigned char *s_ptr,long width,long height,unsigned char *i_ptr,long select);//отрисовать спрайт
  bool Move(long x1,long y1,long x2,long y2);//сделать ход
  void AddLog(char *string);//добавить в лог-файл текст
  //-Прочее------------------------------------------------------------------
};

#endif