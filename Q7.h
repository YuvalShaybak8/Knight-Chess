#ifndef __Q7_H
#define __Q7_H

#include "general.h"
#include "Q12.h"
#include "Q34.h"
#include "Q56.h"

//Q7
char* nameFile();
void printMenu();
void play();
bool vaildChoice(int choice);
bool vaildRowandCol(char row,int col);
void createFile(chessPosList* pathList);
void printReturnValue(int outcome);
void positionCheck(char* row, int* col);

#endif