#ifndef __Q34_H
#define __Q34_H

#include "general.h"
#include "Q12.h"

//Q3
void freeValidKnight(chessPosArray*** knightMove);
pathTree findAllPossibleKnightPaths(chessPos* startingPosition);
treeNode* createNewTreeNode(chessPos* position, treeNodeListCell* next_posible_position);
treeNode* findAllPossibleKnightPathsHelper(bool knightMoveRecord[][BOARD_SIZE], chessPos* position, chessPosArray*** knightMove);

//Q4
chessPosList* findKnightPathCoveringAllBoard(pathTree* path_tree);
chessPosCell* createNewListNode(char row, char col, chessPosCell* next);
void insertDataToStartList(chessPos coordinate, chessPosCell* next, chessPosList* newList);
void findKnightPathCoveringAllBoardHelper(treeNode* root, int levelofTree, chessPosList* newList);

#endif