#ifndef GUI_H
#define GUI_H

//****************************************************************************************************
//функции для работы с элементами графического интерфейса Photon
//****************************************************************************************************


//****************************************************************************************************
//подключаемые библиотеки
//****************************************************************************************************
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <sys/syspage.h>
#include <inttypes.h>
#include <sys/neutrino.h>
#include <fcntl.h>

/* Local headers */
#include "ablibs.h"
#include "abimport.h"
#include "proto.h"

//****************************************************************************************************
//настройки компиляции
//****************************************************************************************************
#pragma pack(1)

//****************************************************************************************************
//функции для работы с элементами графического интерфейса Photon
//****************************************************************************************************
void AddStringInList(PtWidget_t *pt_widget,char *string);//добавить строку в список
unsigned short GetListSize(PtWidget_t *pt_widget);//получить количество элементов в списке
unsigned short GetTopItemPosInList(PtWidget_t *pt_widget);//получить позицию верхнего отображаемого элемента в списке
void SetTopItemPosInList(PtWidget_t *pt_widget,unsigned short pos);//задать позицию верхнего отображаемого элемента в списке
void SelectListElement(PtWidget_t *pt_widget,unsigned short index);//выделить элемент списка
void UnselectListElement(PtWidget_t *pt_widget,unsigned short index);//отменить выделение элемента списка
bool IsSelectedListElement(PtWidget_t *pt_widget,char *name);//узнать, выделен ли элемент списка
void ClearList(PtWidget_t *pt_widget);//очистить список
void SetBlocked(PtWidget_t *pt_widget,bool blocking);//установить/снять блокировку
unsigned short GetSelectedItemInComboBox(PtWidget_t *pt_widget);//получить номер выбранной строки в ComboBox
void ClearComboBox(PtWidget_t *pt_widget);//очистить выпадающий список
void AddStringInComboBox(PtWidget_t *pt_widget,char *string);//добавить строку в выпадающий список
void SetSelectedItemInComboBox(PtWidget_t *pt_widget,unsigned short index);//установить выбранную строку в выпадающем списке
void SetNumbericFloatValue(PtWidget_t *pt_widget,double value);//записать в числовое поле значение
double GetNumbericFloatValue(PtWidget_t *pt_widget);//считать из числового поля значение
void SetWidgetText(PtWidget_t *pt_widget,char *text);//задать текст компонента
char* GetWidgetText(PtWidget_t *pt_widget);//считать текст виджета
bool GetButtonOnOffState(PtWidget_t *pt_widget);//получить состояние кнопки OnOff


#endif