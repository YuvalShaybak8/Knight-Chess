#ifndef __GENERAL_H
#define __GENERAL_H

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define BOARD_SIZE 5

#define EXIT 6
#define STOP 1
#define NOT_EXIST -1
#define FULL_BOARD 2
#define INVALID_LIST 1
#define LESS_THAN_FULL_BOARD 3
#define MAX_OPTION 8

typedef char chessPos[2];

//Q1
typedef struct _chessPosArray
{
	unsigned int size;
	chessPos* positions;
} chessPosArray;

//Q1
chessPosArray*** validKnightMoves();
chessPosArray* checkMoves(int row, int col);

//Q2
typedef struct _chessPosCell
{
	chessPos position;
	struct _chessPosCell* next;
} chessPosCell;

typedef struct _chessPosList
{
	chessPosCell* head;
	chessPosCell* tail;
} chessPosList;

//Q3

//forward decler
typedef struct _treeNodeListCell treeNodeListCell;
typedef struct _treeNode treeNode;

typedef struct _treeNode
{
	chessPos position;
	treeNodeListCell* next_possible_positions;
}treeNode;

typedef struct _treeNodeListCell
{
	treeNode* node;
	struct _treeNodeListCell* next;
} treeNodeListCell;

typedef struct _pathTree
{
	treeNode* root;
}pathTree;

typedef unsigned char BYTE;

//general
void checkMemoryAllocation(void* arr);
void checkFile(FILE* file);
void freeList(chessPosList* lst);
void freeTree(pathTree tr);
void freeTreeHelper(treeNode* root);

#endif