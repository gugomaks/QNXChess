#ifndef ENGINE_HASH_H
#define ENGINE_HASH_H
 
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <stdint.h>
 
#include "engine_common.h"
#include "engine_move.h"
 
using namespace std;
 
//----------------------------------------------------------------------------------------------------
//ХЭШ-таблица
//----------------------------------------------------------------------------------------------------
 
//размер таблицы
#define MAX_HASH_TABLE_SIZE (1UL<<21UL)
//типы отсечений
 
//поле пустое
#define HASH_TABLE_TYPE_EMPTY 0
//оценка точная
#define HASH_TABLE_TYPE_EXACT 1
//отсечение по альфа
#define HASH_TABLE_TYPE_ALPHA 2
//отсечение по бета
#define HASH_TABLE_TYPE_BETA  3
//поле устарело, но содержит ход
#define HASH_TABLE_TYPE_OLD   4
//описатель таблицы
struct SHTable
{
 uint64_t HKey;//хэш-ключ
 long Level;//глубина узла
 long HashType;//тип узла
 long Score;//оценка узла
 SMove sMove;//лучший ход (если он есть)
};
//----------------------------------------------------------------------------------------------------
//Прототипы функций
//----------------------------------------------------------------------------------------------------
void Hash_Init(void);//инициализация хэш-таблицы
void Hash_Release(void);//деинициализация хэш-таблицы
uint64_t Hash_Randomize64UI(void);//генератор 64-х битного случайного числа
uint64_t Hash_GetHKey(void);//получить хэш-ключ
void Hash_RecordHash(long level,long score,long flag,uint64_t hkey,SMove *sMove_Ptr);//записать в хэш-таблицу
 
#endif
 