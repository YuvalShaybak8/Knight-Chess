#include "Q34.h"

/*Q3*/

/*build a tree with all the possible different paths which start in the startingPosition*/
pathTree findAllPossibleKnightPaths(chessPos* startingPosition)
{
	pathTree tree;

	bool knightsDatabase[BOARD_SIZE][BOARD_SIZE] = { false };/*rest boolean board to false*/

	chessPosArray*** knightMove = validKnightMoves();

	tree.root = findAllPossibleKnightPathsHelper(knightsDatabase, startingPosition, knightMove);/*helper*/

	freeValidKnight(knightMove);

	return tree;
}

/*freeing the valid knight*/
void freeValidKnight(chessPosArray*** knightMove)
{
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			free(knightMove[i][j]->positions);
			free(knightMove[i][j]);
		}
		free(knightMove[i]);
	}
	free(knightMove);
}

/*helper to findAllPossibleKnightPaths function*/
treeNode* findAllPossibleKnightPathsHelper(bool knightsDatabase[][BOARD_SIZE], chessPos* startPosition, chessPosArray*** knightMove)
{
	int startRow = startPosition[0][0] - 'A';/*Local variable*/
	int startCol = startPosition[0][1] - '1';/*Local variable*/

	if (knightsDatabase[startRow][startCol] == true)/*if the position is allready in the list*/
	{
		return NULL;
	}

	chessPosArray* NumbersOfMoves = knightMove[startRow][startCol];/*check current position next available positions*/

	treeNode* newNode = createNewTreeNode(startPosition, NULL);

	if (NumbersOfMoves->size == 0)/*if there is no more moves to go to*/
	{
		knightsDatabase[startRow][startCol] = false;
		return newNode;
	}

	int sizeMoves = NumbersOfMoves->size;/*Local variable*/
	knightsDatabase[startRow][startCol] = true;

	treeNodeListCell* prev = NULL;

	/*puts into the tree any movement that did not appear before in the list itself*/
	/*and this action is repeated in recursion until the stopping conditions are no longer possible movements*/
	for (int i = 0; i < sizeMoves; i++)
	{
		int chessPosRow = NumbersOfMoves->positions[i][0] - 'A';
		int chessPosCol = NumbersOfMoves->positions[i][1] - '1';

		if (knightsDatabase[chessPosRow][chessPosCol] == false)
		{
			treeNodeListCell* nextCell = (treeNodeListCell*)malloc(sizeof(treeNodeListCell));
			checkMemoryAllocation(nextCell);

			chessPos* nextCellPosition = (chessPos*)malloc(sizeof(chessPos));
			checkMemoryAllocation(nextCellPosition);

			nextCellPosition[0][0] = NumbersOfMoves->positions[i][0];
			nextCellPosition[0][1] = NumbersOfMoves->positions[i][1];

			nextCell->node = findAllPossibleKnightPathsHelper(knightsDatabase, nextCellPosition, knightMove);
			nextCell->next = NULL;

			free(nextCellPosition);

			if (newNode->next_possible_positions == NULL)
			{
				newNode->next_possible_positions = nextCell;
			}
			else
			{
				prev->next = nextCell;
			}
			prev = nextCell;
		}
	}
	knightsDatabase[startRow][startCol] = false;

	return newNode;
}

/*create new tree node with the position and the next possible positions*/
treeNode* createNewTreeNode(chessPos* position, treeNodeListCell* next_posible_position)
{
	treeNode* newNode = (treeNode*)malloc(sizeof(treeNode));
	checkMemoryAllocation(newNode);

	newNode->position[0] = position[0][0];/*We enter to the new node the nextMovement of the prev*/
	newNode->position[1] = position[0][1];/*We enter to the new node the nextMovement of the prev*/
	newNode->next_possible_positions = next_posible_position;

	return newNode;
}

/*Q4*/

/*finds a path that cover all the positions on the board*/
chessPosList* findKnightPathCoveringAllBoard(pathTree* path_tree)
{
	chessPosList* newList;
	newList = (chessPosList*)malloc(sizeof(chessPosList));
	checkMemoryAllocation(newList);

	newList->head = newList->tail = NULL;

	int levelofTree = 1;

	findKnightPathCoveringAllBoardHelper(path_tree->root, levelofTree, newList);/*helper*/

	return newList;
}

/*helper to findKnightPathCoveringAllBoard function */
void findKnightPathCoveringAllBoardHelper(treeNode* root, int levelofTree, chessPosList* newList)
{
	if (root == NULL)
	{
		return;
	}

	treeNodeListCell* ptr = root->next_possible_positions;

	if (root->next_possible_positions == NULL && levelofTree != (BOARD_SIZE * BOARD_SIZE))/*the path is not covering all the board- return*/
	{
		return;
	}

	if (levelofTree == BOARD_SIZE * BOARD_SIZE)/*if there is path with BOARD * BOARD*/
	{
		insertDataToStartList(root->position, NULL, newList);/*root position is the new location in board, null is next position*/
		newList->tail = newList->head;
		return;
	}

	while (ptr != NULL)
	{
		findKnightPathCoveringAllBoardHelper(ptr->node, levelofTree + 1, newList);/*recursive call*/
		if (newList->head != NULL)
		{
			insertDataToStartList(root->position, newList->head, newList);/*root position is the new location in board, null is next position*/
			return;
		}
		ptr = ptr->next;
	}
}

/*insert new data to start list*/
void insertDataToStartList(chessPos coordinate, chessPosCell* next, chessPosList* newList)
{
	chessPosCell* newHead;
	newHead = createNewListNode(coordinate[0], coordinate[1], next);/*create new list function*/
	newList->head = newHead;
}

/*create new chessPos Cell*/
chessPosCell* createNewListNode(char row, char col, chessPosCell* next)
{
	chessPosCell* res = (chessPosCell*)malloc(sizeof(chessPosCell));
	checkMemoryAllocation(res);

	res->position[0] = row;
	res->position[1] = col;
	res->next = next;

	return res;
}