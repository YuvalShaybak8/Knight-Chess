#ifndef __Q12_H
#define __Q12_H

#include "general.h"

//Q2
void printFirstLine();
void printBoard(chessPosList lst);
void display(chessPosList* lst);
void printTable(int insertByOrder[][BOARD_SIZE]);
void resetIntBoard(int insertByOrder[][BOARD_SIZE]);
void deleteCell(chessPosList* lst, chessPosCell* delete);

#endif