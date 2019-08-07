#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

typedef struct Node* nodePtr;
typedef struct Node{
	int data;
	nodePtr link;
}Node;

nodePtr temp, startA, lastA, startB, lastB;

nodePtr makeList(char filename[], nodePtr walk)
{
	nodePtr start = NULL;
	FILE* fp = fopen(filename, "r");
	char k;
	int num;
	while (1)
	{
		k = fscanf(fp, "%d", &num);
		if (k == EOF) break;
		temp = (nodePtr)malloc(sizeof(Node));
		temp->data = num;
		if (!start) { 
			start = temp; 
			walk = temp;
			start->link = start;
		}
		else
		{
			walk->link = temp;
			temp->link = start;
			walk = temp;
		}
	}
	fclose(fp);
	return start;
}

void deleteData(char filename[])
{
	FILE*fp = fopen(filename, "r");
	nodePtr walk;
	char k;
	int num, numR;
	while (1)
	{
		k = fscanf(fp, "%d", &num);
		if (k == EOF) break;
		numR = num % 2;
		if ((num > 0) && (num < 27) && (!numR))
		{
			walk = startB;
			temp = lastA;
			while (walk != startA)
			{
				if (walk->data == num)
				{
					if (walk == startB) startB = startB->link;
					temp->link = walk->link;
					free(walk);
					walk = temp->link;
				}
				else
				{
					temp = walk;
					walk = walk->link;
				}
			}
			lastB = temp;
		}
		else if ((num > 0) && (num < 27) && numR)
		{
			walk = startA;
			temp = lastB;
			while (walk != startB)
			{
				if (walk->data == num)
				{
					if (walk == startA) startA = startA->link;
					temp->link = walk->link;
					free(walk);
					walk = temp->link;
				}
				else
				{
					temp = walk;
					walk = walk->link;
				}
			}
			lastA = temp;
		}
	}
	fclose(fp);
}

void printList()
{
	nodePtr walk = startA;
	do {
		printf("%d ", walk->data);
		walk = walk->link;
	} while (walk != startA);
	printf("\n");
}

void freeList()
{
	nodePtr walk, temp;
	walk = startA->link;
	temp = startA->link;
	while (walk != startA)
	{
		walk = walk->link;
		free(temp);
		temp = walk;
	}
	free(temp);
}

int main()
{
	startA = makeList("A.txt", lastA);
	lastA = temp;
	startB = makeList("B.txt",lastB);
	lastB = temp;
	lastA->link = startB;
	lastB->link = startA;
	printList();
	deleteData("C.txt");
	printList();
	freeList();
	system("pause");
}