#ifndef __Q56_H
#define __Q56_H

#include "general.h"
#include "Q12.h"
#include "Q34.h"

//Q5

void saveListToBinFile(char* file_name, chessPosList* pos_list);
short int sizeOfList(chessPosList* pos_list);
void updateArr(BYTE* arr, short int size, chessPosList* pos_list);
void writeDivSizeChars(FILE* listFile, BYTE* arr, short int DivSize);
void writeModSizeChars(FILE* listFile, BYTE* arr, short int ModSize);

//Q6
void readDivSizeChars(FILE* listFile, BYTE* arr, short int DivSize);
void readModSizeChars(FILE* listFile, BYTE* arr, short int ModSize);
int checkAndDisplayPathFromFile(char* file_name);
void updateList(chessPosList* list, BYTE* arr, short int size);
bool checkVaildNext(chessPosCell* curr, chessPosCell* next);
bool checkVaildList(chessPosList list);

#endif