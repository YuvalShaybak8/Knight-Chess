#include "general.h"

/*function for checking memory allocation*/
void checkMemoryAllocation(void* arr)
{
	if (arr == NULL)
	{
		puts("Memory allocation failed");
		exit(STOP);
	}
}

/*function to check if file opened succesfully*/
void checkFile(FILE* file)
{
	if (file == NULL)
	{
		printf("File opening failed \n");
		exit(STOP);
	}
}

/*function to free the list*/
void freeList(chessPosList* lst)
{
	chessPosCell* curr, * next;
	curr = lst->head;

	while (curr != NULL)
	{
		next = curr->next; /*inputting the next node in list to not lose the next node*/
		free(curr);
		curr = next; /*moving forward*/
	}
}

/*function to free the tree*/
void freeTree(pathTree tr)
{
	freeTreeHelper(tr.root);
}

/*helper to freeTree */
void freeTreeHelper(treeNode* root)
{
	treeNodeListCell* curr = root->next_possible_positions, * tmp;

	if (root == NULL)
		return;

	while (curr != NULL)
	{
		tmp = curr->next;
		freeTreeHelper(curr->node);
		free(curr);
		curr = tmp;
	}
}