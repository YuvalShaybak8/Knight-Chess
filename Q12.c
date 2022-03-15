#include "Q12.h"

/*Q1*/

/*check how many available moves have to the knight in every position*/
chessPosArray*** validKnightMoves()
{
	chessPosArray*** knightMoves = (chessPosArray***)malloc(sizeof(chessPosArray**) * BOARD_SIZE);
	checkMemoryAllocation(knightMoves);
	
	for (int i = 0; i < BOARD_SIZE; i++)/*for each row we allocate "BOARD_SIZE" positions*/
	{
		knightMoves[i] = (chessPosArray**)malloc(sizeof(chessPosArray*) * BOARD_SIZE);
		checkMemoryAllocation(knightMoves[i]);

		for (int j = 0; j < BOARD_SIZE; j++)/*check how many moves are available and create array of chessPos with size*/
		{
			knightMoves[i][j] = checkMoves(i,j);
		}

	}
	return knightMoves;
}

/*gets row and col and return array with relevant move of current position*/
chessPosArray* checkMoves(int row, int col)
{
	int counter = 0;
	chessPosArray* knights = (chessPosArray*) malloc(sizeof(chessPosArray));
	checkMemoryAllocation(knights);

	knights->positions = (chessPos*)malloc(sizeof(chessPos) * MAX_OPTION);/*allocate max size of options in chess game for a knight*/
	checkMemoryAllocation(knights->positions);

	/*check move and if relevant- enter the position to the array of movements*/
	if (row + 2 < BOARD_SIZE && col + 1 < BOARD_SIZE && row + 2 >= 0 && col + 1 >= 0)
	{
		knights->positions[counter][0] = 'A' + row + 2;
		knights->positions[counter][1] = '1' + col + 1;
		counter++;
	}
	if (row + 2 < BOARD_SIZE && col - 1 < BOARD_SIZE && row + 2 >= 0 && col - 1 >= 0)
	{
		knights->positions[counter][0] = 'A' + row + 2;
		knights->positions[counter][1] = '1' + col - 1;
		counter++;
	}
	if (row - 2 < BOARD_SIZE && col + 1 < BOARD_SIZE && row - 2 >= 0 && col + 1 >= 0)
	{
		knights->positions[counter][0] = 'A' + row - 2;
		knights->positions[counter][1] = '1' + col + 1;
		counter++;
	}
	if (row - 2 < BOARD_SIZE && col - 1 < BOARD_SIZE && row - 2 >= 0 && col - 1 >= 0)
	{
		knights->positions[counter][0] = 'A' + row - 2;
		knights->positions[counter][1] = '1' + col - 1;
		counter++;
	}
	if (row + 1 < BOARD_SIZE && col + 2 < BOARD_SIZE && row + 1 >= 0 && col + 2 >= 0)
	{
		knights->positions[counter][0] = 'A' + row + 1;
		knights->positions[counter][1] = '1' + col + 2;
		counter++;
	}
	if (row + 1 < BOARD_SIZE && col - 2 < BOARD_SIZE && row + 1 >= 0 && col - 2 >= 0)
	{
		knights->positions[counter][0] = 'A' + row + 1;
		knights->positions[counter][1] = '1' + col - 2;
		counter++;
	}
	if (row - 1 < BOARD_SIZE && col + 2 < BOARD_SIZE && row - 1 >= 0 && col + 2 >= 0)
	{
		knights->positions[counter][0] = 'A' + row - 1;
		knights->positions[counter][1] = '1' + col + 2;
		counter++;
	}
	if (row - 1 < BOARD_SIZE && col - 2 < BOARD_SIZE && row - 1 >= 0 && col - 2 >= 0)
	{
		knights->positions[counter][0] = 'A' + row - 1;
		knights->positions[counter][1] = '1' + col - 2;
		counter++;
	}
	knights->size = counter;

	if(knights->size < BOARD_SIZE)
	{ 
	knights->positions = (chessPos*)realloc(knights->positions, sizeof(chessPos) * knights->size); /*update the size of the allocation*/
	}
	return knights;
}

/*Q2*/

/*print all the board*/
void printBoard(chessPosList lst)
{
	chessPosCell* curr = lst.head;
	printFirstLine();

	/*insert numbers for each cell by order from lst*/
	int nodeCounter = 0;
	int insertByOrder[BOARD_SIZE][BOARD_SIZE];

	resetIntBoard(insertByOrder);

	while (curr != NULL) 
	{
		nodeCounter++;
		insertByOrder[curr->position[0] - 'A'][curr->position[1] - '1'] = nodeCounter;
		curr = curr->next;
	}

	printTable(insertByOrder);
}

/*print all the board beside the first line*/
void printTable(int insertByOrder[][BOARD_SIZE])
{
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j <= BOARD_SIZE; j++)
		{
			if (j == 0)
			{
				printf("|%3c  ", 'A' + i);
			}
			else if (insertByOrder[i][j - 1] != 0 && insertByOrder[i][j - 1] <= 9)
			{
				printf("|  %d  ", insertByOrder[i][j - 1]);/*print the list by order*/
			}
			else if (insertByOrder[i][j - 1] > 9)
			{
				printf("| %d  ", insertByOrder[i][j - 1]);/*print the list by order*/
			}
			else
			{
				printf("|     ");
			}
		}
		printf("|\n");
		for (int k = 0; k <= BOARD_SIZE; k++)
		{
			printf("+-----");
		}
		printf("+\n");
	}
}

/*print the first line of the borad*/
void printFirstLine()
{
	int i;
	for (i = 0; i <= BOARD_SIZE; i++)
	{
		printf("+-----");
	}
	printf("+\n");
	for (i = 0; i <= BOARD_SIZE; i++)
	{

		if (i > 0)
		{
			printf("|%3d  ", i);
		}
		else
		{
			printf("|     ");
		}

	}
	printf("|\n");
	for (i = 0; i <= BOARD_SIZE; i++)
	{
		printf("+-----");
	}
	printf("+\n");
}

/*reset all the board to empty cells and update boolean array each check of move*/
void display(chessPosList* lst)
{
	bool isEmpty[BOARD_SIZE][BOARD_SIZE];

	for (int i = 0; i < BOARD_SIZE; i++)/*To reset the value of each cell to true*/
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			isEmpty[i][j] = true;
		}
	}

	chessPosCell* curr = lst->head, * saver;

	while (curr != NULL)
	{
		if (isEmpty[curr->position[0] - 'A'][curr->position[1] - '1'] == false)/*if position allready appear- delete the relevent lnode in list*/
		{
			saver = curr->next;/*save the next lnode to connect between prev and next*/
			deleteCell(lst, curr);
			curr = saver;
		}
		else
		{
			isEmpty[curr->position[0] - 'A'][curr->position[1] - '1'] = false;/*make current lnode as appeared*/
			curr = curr->next;
		}
	}
}

/*delete the cell that appeared allready*/
void deleteCell(chessPosList* lst, chessPosCell* delete)
{
	chessPosCell* after = lst->head, * saver;

	if (delete == lst->head)/*delete from head*/
	{
		if (lst->head->next == NULL)/*list has only one node*/
		{
			free(lst->head);
		}
		else/*list has more then one node*/
		{
			saver = lst->head->next;
			free(lst->head);
			lst->head = saver;
		}
	}
	else
	{
		if (delete == lst->tail)/*delete from middle or tail*/
		{
			while (after->next != delete)
			{
				after = after->next;
			}
			free(delete);
			lst->tail = after;
			after->next = NULL;
		}
		else/*delete from middle*/
		{
			while (after->next != delete)
			{
				after = after->next;
			}
			saver = delete->next;
			free(delete);
			after->next = saver;
		}
	}
}

/*reset all the board to 0*/
void resetIntBoard(int insertByOrder[][BOARD_SIZE])
{
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			insertByOrder[i][j] = 0;
		}
	}
}