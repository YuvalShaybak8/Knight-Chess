#include "Q56.h"
/*Q5*/

/*save a list to a file to save space*/
void saveListToBinFile(char* file_name, chessPosList* pos_list)
{
	short int ListSize = sizeOfList(pos_list);

	FILE* listFile = fopen(file_name, "wb");
	checkFile(listFile);

	fwrite(&ListSize, sizeof(short int), 1, listFile);/*write the size of the list*/

	short int size = ListSize * 2;

	BYTE* arr = (BYTE*)malloc(sizeof(BYTE) * size);
	checkMemoryAllocation(arr);

	updateArr(arr, size, pos_list);/* insert all BYTES to arr*/

	short int DivSize = size / 8;
	short int ModSize = size % 8;

	writeDivSizeChars(listFile, arr, DivSize);/*handle with size DIV 8*/
	writeModSizeChars(listFile, arr + (DivSize * 8), ModSize);/*handle with size MOD 8*/

	free(arr);
	fclose(listFile);
}

/*the rest of the list is written to the file(with MOD size)*/
void writeModSizeChars(FILE* listFile, BYTE* arr, short int ModSize)
{
	if (ModSize == 2)
	{
		BYTE tmpArr[1] = { 0 };
		tmpArr[0] = tmpArr[0] | (arr[0] << 5);
		tmpArr[0] = tmpArr[0] | (arr[1] << 2);
		fwrite(tmpArr, sizeof(BYTE), 1, listFile);
	}
	if (ModSize == 4)
	{
		BYTE tmpArr[3] = { 0 };
		tmpArr[0] = tmpArr[0] | (arr[0] << 5);
		tmpArr[0] = tmpArr[0] | (arr[1] << 2);
		tmpArr[0] = tmpArr[0] | (arr[2] >> 1);
		tmpArr[1] = tmpArr[1] | (arr[2] << 7);
		tmpArr[2] = tmpArr[2] | (arr[3] << 4);

		fwrite(tmpArr, sizeof(BYTE), 3, listFile);
	}
	if (ModSize == 6)
	{
		BYTE tmpArr[3] = { 0 };
		tmpArr[0] = tmpArr[0] | (arr[0] << 5);
		tmpArr[0] = tmpArr[0] | (arr[1] << 2);
		tmpArr[0] = tmpArr[0] | (arr[2] >> 1);

		tmpArr[1] = tmpArr[1] | (arr[2] << 7);
		tmpArr[1] = tmpArr[1] | (arr[3] << 4);
		tmpArr[1] = tmpArr[1] | (arr[4] << 1);
		tmpArr[1] = tmpArr[1] | (arr[5] >> 2);

		tmpArr[2] = tmpArr[2] | (arr[5] << 6);

		fwrite(tmpArr, sizeof(BYTE), 3, listFile);
	}
}

/*write 4 chessPos(8 chars) data each iteration to the file(with DIV size)*/
void writeDivSizeChars(FILE* listFile, BYTE* arr, short int DivSize)
{
	for (int i = 0; i < DivSize * 8; i += 8)
	{
		BYTE smallArr[3] = { 0 };

		smallArr[0] = smallArr[0] | (arr[i] << 5);

		smallArr[0] = smallArr[0] | (arr[i + 1] << 2);
		smallArr[0] = smallArr[0] | (arr[i + 2] >> 1);

		smallArr[1] = smallArr[1] | (arr[i + 2] << 7);
		smallArr[1] = smallArr[1] | (arr[i + 3] << 4);
		smallArr[1] = smallArr[1] | (arr[i + 4] << 1);
		smallArr[1] = smallArr[1] | (arr[i + 5] >> 2);

		smallArr[2] = smallArr[2] | (arr[i + 5] << 6);
		smallArr[2] = smallArr[2] | (arr[i + 6] << 3);
		smallArr[2] = smallArr[2] | (arr[i + 7]);

		fwrite(smallArr, sizeof(BYTE), 3, listFile);
	}
}

/*update array to numeric number*/
void updateArr(BYTE* arr, short int size, chessPosList* pos_list)
{
	chessPosCell* curr = pos_list->head;

	for (int i = 0; i < size; i += 2)
	{
		arr[i] = curr->position[0] - 'A';
		arr[i + 1] = curr->position[1] - '1';
		curr = curr->next;
	}
}

/*find size of list*/
short int sizeOfList(chessPosList* pos_list)
{
	short int counter = 0;
	chessPosCell* curr = pos_list->head;

	while (curr != NULL)
	{
		counter++;
		curr = curr->next;
	}
	return counter;
}

/*Q6*/

/*extract list of chessPos from file and check if the list is legal. return number according to described in Question 6*/
int checkAndDisplayPathFromFile(char* file_name)
{
	bool isValidList;
	FILE* readFile = fopen(file_name, "rb");

	if (readFile == NULL)
		return NOT_EXIST;
		

	short int size = 0;

	fread(&size, sizeof(short int), 1, readFile);


	short int updateSize = size * 2;
	BYTE* arr;

	arr = calloc(updateSize, sizeof(BYTE));
	checkMemoryAllocation(arr);

	short int DivSize = updateSize / 8;/* / 8 because 3 BYTE is full 24 bites*/
	short int ModSize = updateSize % 8;/*deal with remainings*/

	readDivSizeChars(readFile, arr, DivSize);/*read 4 cheesPos each iteration*/
	readModSizeChars(readFile, arr + (DivSize * 8), ModSize); /*read last chesPos's in list*/

	fclose(readFile);

	chessPosList list;
	list.head = list.tail = NULL;

	updateList(&list, arr, updateSize);/*insert array on chars into chessPos List*/
	free(arr);

	isValidList = checkVaildList(list);

	if (!isValidList)
	{
		freeList(&list);
		return INVALID_LIST;
	}

	display(&list);/*print updated list*/
	printBoard(list);

	int sizeList = sizeOfList(&list);
	if (sizeList == BOARD_SIZE * BOARD_SIZE)
	{
		freeList(&list);
		return FULL_BOARD;
	}

	freeList(&list);
	return LESS_THAN_FULL_BOARD;
}

/*get array of chars and exchange it to List*/
void updateList(chessPosList* list, BYTE* arr, short int size)
{
	chessPosCell* cell = NULL;
	chessPosCell* saver = NULL;

	for (int i = 0; i < size; i += 2)// c5 a4 d4
	{
		cell = (chessPosCell*)malloc(sizeof(chessPosCell));
		checkMemoryAllocation(cell);

		cell->position[0] = arr[i];/*get COL*/
		cell->position[1] = arr[i + 1];/*get row*/
		if (i == 0)
		{
			list->head = cell;
			cell->next = NULL;
			saver = cell;
			continue;
		}
		saver->next = cell;

		saver = cell;
	}
	list->tail = cell;
	list->tail->next = NULL;
}

/*check if list is legal*/
bool checkVaildList(chessPosList list)
{
	chessPosCell* curr = list.head;
	bool nextMoveVail;

	while (curr != list.tail)/*check for every lnode*/
	{
		nextMoveVail = checkVaildNext(curr, curr->next);

		if (!nextMoveVail)
		{
			return false;
		}
		curr = curr->next;
	}
	return true;
}

/*get current lnode and next lnode and check if its legal move*/
bool checkVaildNext(chessPosCell* curr, chessPosCell* next)
{
	int row = curr->position[0];
	int col = curr->position[1];
	bool MoveFound = false;

	if (row + 2 == next->position[0] && col + 1 == next->position[1])
	{
		MoveFound = true;
	}
	if (row + 2 == next->position[0] && col - 1 == next->position[1])
	{
		MoveFound = true;
	}
	if (row - 2 == next->position[0] && col + 1 == next->position[1])
	{
		MoveFound = true;
	}
	if (row - 2 == next->position[0] && col - 1 == next->position[1])
	{
		MoveFound = true;
	}
	if (row + 1 == next->position[0] && col + 2 == next->position[1])
	{
		MoveFound = true;
	}
	if (row + 1 == next->position[0] && col - 2 == next->position[1])
	{
		MoveFound = true;
	}
	if (row - 1 == next->position[0] && col + 2 == next->position[1])
	{
		MoveFound = true;
	}
	if (row - 1 == next->position[0] && col - 2 == next->position[1])
	{
		MoveFound = true;
	}

	return MoveFound;
}

/*read 4 chessPos in each itteration. (4 chessPos is 8 chars)*/
void readDivSizeChars(FILE* listFile, BYTE* arr, short int DivSize)
{
	for (int i = 0; i < DivSize * 8; i += 8)
	{
		BYTE mask;
		BYTE tmpArr[3] = { 0 };

		fread(tmpArr, sizeof(BYTE), 3, listFile);
		arr[i] = arr[i] | (tmpArr[0] >> 5);
		arr[i] = arr[i] + 'A';

		mask = 28;/* mask 00011100 */
		arr[i + 1] = arr[i + 1] | ((tmpArr[0] & mask) >> 2);
		arr[i + 1] = arr[i + 1] + '1';

		mask = 3;/* mask 00000011 */
		arr[i + 2] = arr[i + 2] | ((tmpArr[0] & mask) << 1);
		arr[i + 2] = arr[i + 2] | (tmpArr[1] >> 7);
		arr[i + 2] = arr[i + 2] + 'A';

		mask = 112;/* mask 01110000 */
		arr[i + 3] = arr[i + 3] | ((tmpArr[1] & mask) >> 4);
		arr[i + 3] = arr[i + 3] + '1';

		mask = 14;/* mask 00001110 */
		arr[i + 4] = arr[i + 4] | ((tmpArr[1] & mask) >> 1);
		arr[i + 4] = arr[i + 4] + 'A';

		mask = 1;/* mask 00000001 */
		arr[i + 5] = arr[i + 5] | ((tmpArr[1] & mask) << 2);
		arr[i + 5] = arr[i + 5] | (tmpArr[2] >> 6);
		arr[i + 5] = arr[i + 5] + '1';

		mask = 56;/* mask 00111000 */
		arr[i + 6] = arr[i + 6] | ((tmpArr[2] & mask) >> 3);
		arr[i + 6] = arr[i + 6] + 'A';

		mask = 7;/* mask 00000111 */
		arr[i + 7] = arr[i + 7] | (tmpArr[2] & mask);
		arr[i + 7] = arr[i + 7] + '1';
	}
}

/*extract remainings chessPos's from file*/
void readModSizeChars(FILE* listFile, BYTE* arr, short int ModSize)
{
	BYTE mask;

	if (ModSize == 2)/*one chessPos*/
	{
		BYTE tmpArr[1] = { 0 };
		fread(tmpArr, sizeof(BYTE), 1, listFile);

		arr[0] = arr[0] | (tmpArr[0] >> 5);
		arr[0] = arr[0] + 'A';

		mask = 28;/* mask 00011100 */
		arr[1] = arr[1] | ((tmpArr[0] & mask) >> 2);
		arr[1] = arr[1] + '1';
	}

	if (ModSize == 4)/*two chessPos's*/
	{
		BYTE tmpArr[2] = { 0 };
		fread(tmpArr, sizeof(BYTE), 2, listFile);

		arr[0] = arr[0] | (tmpArr[0] >> 5);
		arr[0] = arr[0] + 'A';

		mask = 28;/* mask 00011100 */
		arr[1] = arr[1] | ((tmpArr[0] & mask) >> 2);
		arr[1] = arr[1] + '1';

		mask = 3;/* mask 00000011 */
		arr[2] = arr[2] | ((tmpArr[0] & mask) << 1);
		arr[2] = arr[2] | (tmpArr[1] >> 7);
		arr[2] = arr[2] + 'A';

		mask = 112;/* mask 01110000 */
		arr[3] = arr[3] | ((tmpArr[1] & mask) >> 4);
		arr[3] = arr[3] + '1';
	}

	if (ModSize == 6)/*3 chessPos's*/
	{
		BYTE tmpArr[3] = { 0 };
		fread(tmpArr, sizeof(BYTE), 3, listFile);

		arr[0] = arr[0] | (tmpArr[0] >> 5);
		arr[0] = arr[0] + 'A';

		mask = 28;/* mask 00011100 */
		arr[1] = arr[1] | ((tmpArr[0] & mask) >> 2);
		arr[1] = arr[1] + '1';

		mask = 3;/* mask 00000011 */
		arr[2] = arr[2] | ((tmpArr[0] & mask) << 1);
		arr[2] = arr[2] | (tmpArr[1] >> 7);
		arr[2] = arr[2] + 'A';

		mask = 112;/* mask 01110000 */
		arr[3] = arr[3] | ((tmpArr[1] & mask) >> 4);
		arr[3] = arr[3] + '1';

		mask = 14;/* mask 00001110 */
		arr[4] = arr[4] | ((tmpArr[1] & mask) >> 1);
		arr[4] = arr[4] + 'A';

		mask = 1;/* mask 00000001 */
		arr[5] = arr[5] | ((tmpArr[1] & mask) << 2);
		arr[5] = arr[5] | (tmpArr[2] >> 6);
		arr[5] = arr[5] + '1';
	}
}