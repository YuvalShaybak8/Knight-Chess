#include "general.h"
#include "Q12.h"
#include "Q34.h"
#include "Q56.h"
#include "Q7.h"

/*Q7*/

void play()
{
	int choice;
	pathTree treeRoot;
	treeRoot.root = NULL;
	chessPos* inputMove = NULL;
	chessPosList* pathList = NULL;
	bool caseOne = false, caseTwo = false, caseThree = false;
	char row = NOT_EXIST;
	int col = NOT_EXIST;
	bool isPlaying = true;

	while (isPlaying)
	{
		printMenu();
		printf("\nmake your choice: ");
		fseek(stdin, 0, SEEK_END);/*clean buffer*/
		scanf("%d", &choice);

		while (vaildChoice(choice) == false)/*valid choice between 1 to 6*/
		{
			printf("\nchoose again please: ");
			fseek(stdin, 0, SEEK_END);/*clean buffer*/
			scanf("%d", &choice);
			fseek(stdin, 0, SEEK_END);
		}

		switch (choice)/*switch case as desrribed in the question*/
		{
		case 1:
		{
			if (caseOne == true)/*in case user choose option 1 more then one time*/
			{
				/*reset flags*/
				free(inputMove);/*free last position*/
				caseOne = false;

				if (caseThree == true)
				{
					freeList(pathList);
					caseThree = false;
				}

				if (caseTwo == true)
				{
					freeTree(treeRoot);
					caseTwo = false;
				}
			}
			positionCheck(&row, &col);/*check if position is in BOARD- return NULL if position is wrong*/

			if (row == NOT_EXIST || col == NOT_EXIST)/*print message in the function*/
				continue;
			else
			{
				caseOne = true;
				inputMove = (chessPos*)malloc(sizeof(chessPos));
				checkMemoryAllocation(inputMove);
				inputMove[0][0] = row;
				inputMove[0][1] = col + '0';
			}
			break;
		}
		case 2:
		{
			if (caseOne == false)/*user didnt choose option 1 or position is invalid*/
			{
				printf("\n\nPlease choose option 1 first!\n\n");
			}
			/*initialize case 2*/
			else
			{
				treeRoot = findAllPossibleKnightPaths(inputMove);
				printf("\nTree has been built!\n");
				caseTwo = true;
			}
			break;
		}
		case 3:
		{
			if (caseOne == false)/*user didnt choose option 1 or position is invalid*/
			{
				printf("\nPlease choose option 1 first!\n\n");
				continue;
			}
			if (caseTwo == false)/*user didnt choose option 2- automatic execute*/
			{
				printf("\nYou didnt choose option 2 - we are executing..\n");
				treeRoot = findAllPossibleKnightPaths(inputMove);
				printf("\nTree has been built!\n\n");
				caseTwo = true;
			}
			/*initialize case 3*/
			pathList = findKnightPathCoveringAllBoard(&treeRoot);
			caseThree = true;
			if (pathList->head == NULL)/*if there is no full path from the starting position*/
			{
				printf("\nNo full path from %c%c\n", inputMove[0][0], inputMove[0][1]);
			}
			else
			{
				printf("\nFull path has found from %c%c\n", inputMove[0][0], inputMove[0][1]);
			}
			break;
		}
		case 4:
		{
			if (caseOne == false)/*user didnt choose option 1 or position is invalid*/
			{
				printf("\nPlease choose option 1 first!\n\n");
				continue;
			}
			if (caseTwo == false)/*user didnt choose option 2- automatic execute*/
			{
				printf("\nYou didnt choose option 2 - we are executing..\n");
				treeRoot = findAllPossibleKnightPaths(inputMove);
				printf("\nTree has been built!\n\n");
				caseTwo = true;
			}
			if (caseThree == false)/*user didnt choose option 3- automatic execute*/
			{
				printf("\nYou didnt choose option 3 - we are executing..\n");
				pathList = findKnightPathCoveringAllBoard(&treeRoot);
				caseThree = true;
			}
			/*initialize case 4- need full path to create file*/
			if (pathList->head == NULL)/*if there is no full path from the starting position*/
			{
				printf("\nNo full path from %c%c!\nPlease choose another position!\n\n", inputMove[0][0], inputMove[0][1]);
				continue;
			}
			else
			{
				printf("\nFull path has found from %c%c\n", inputMove[0][0], inputMove[0][1]);
			}
			/*create file with full path*/
			fseek(stdin, 0, SEEK_END);/*clean buffer*/
			createFile(pathList);
			printf("\nFile was created succcesfully!\n");
			break;
		}
		case 5:
		{
			fseek(stdin, 0, SEEK_END);/*clean buffer*/
			char* fileName = nameFile();
			int outcome = checkAndDisplayPathFromFile(fileName);
			free(fileName);

			printReturnValue(outcome);
			break;
		}
		case 6:
		{
			if (caseOne)
				free(inputMove);

			if (caseThree)
				freeList(pathList);

			if (caseTwo)
				freeTree(treeRoot);

			printf("\nGoodBye\n");
			exit(STOP);
		}
		}
	}
}

/*print the menu*/
void printMenu()
{
	printf("1.Enter a knight's starting position\n");
	printf("2.Create all possible knight paths\n");
	printf("3.Find a knight path covering all board\n");
	printf("4.Save knight path covering all board to file\n");
	printf("5.Load and display path from file\n");
	printf("6.Exit\n");
}

/*check it the choice is vaild in main manu*/
bool vaildChoice(int choice)
{
	return (choice >= 1 && choice <= 6);
}

/*print the return value from the checkAndDisplayPathFromFile function to the user */
void printReturnValue(int outcome)
{
	switch (outcome)
	{
	case 1:
	{
		printf("The knight path is invaild\n\n");
		break;
	}
	case 2:
	{
		printf("The path covers the entire board\n\n");
		break;
	}
	case 3:
	{
		printf("The path doesn't covers the entire board\n\n");
		break;
	}
	case -1:
	{
		printf("The file doesn't exist\n\n");
		break;
	}
	}
}

/*create file*/
void createFile(chessPosList* pathList)
{
	char* fileName = nameFile();

	saveListToBinFile(fileName, pathList);

	free(fileName);
}

/*create name to the file*/
char* nameFile()
{
	int logSize = 0, phsSize = 1;
	char* text;

	text = (char*)malloc(phsSize * sizeof(char));
	checkMemoryAllocation(text);

	printf("Please enter file name without '.bin' (for example:'namefile') :");

	char ch = getchar();

	while (ch != '\n')
	{
		text[logSize] = ch;
		logSize++;

		if (logSize == phsSize)
		{
			phsSize *= 2;
			text = (char*)realloc(text, phsSize * sizeof(char));/*realloc each time the (logSize == phsSize)*/
			checkMemoryAllocation(text);
		}
		ch = getchar();
	}
	text[logSize] = '\0';
	char* newFileName = (char*)malloc((logSize + 5) * sizeof(char));
	checkMemoryAllocation(newFileName);

	sprintf(newFileName, "%s%s", text, ".bin");

	free(text);
	return newFileName;
}

/*check if the row and the col both are vaild*/
bool vaildRowandCol(char row, int col)
{
	return (row >= 'A' && row <= ('A' + BOARD_SIZE - 1) && col >= 1 && col <= BOARD_SIZE);
}


/*check the position*/
void positionCheck(char* row, int* col)
{
	char currRow;
	int currCol;

	printf("\nPlease enter a row and a col:\n");
	printf("(Row between A-%c and col between 1-%d) ", ('A' + BOARD_SIZE - 1), BOARD_SIZE);

	fseek(stdin, 0, SEEK_END);/*clean the buffer*/

	scanf("%c%d", &currRow, &currCol);

	if (!(vaildRowandCol(currRow, currCol)))
	{
		printf("\nThe position isn't  valid !\n\n");
		*row = NOT_EXIST;
		*col = NOT_EXIST;
	}
	else
	{
		*row = currRow;
		*col = currCol;
		printf("\nThe position is valid !\n\n");
	}
}
