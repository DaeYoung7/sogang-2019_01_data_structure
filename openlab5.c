#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
typedef struct {
	int key;
}element;
typedef struct stack* stackPointer;
typedef struct stack {
	element data;
	stackPointer link;
}stack;
typedef struct queue* queuePointer;
typedef struct queue{
	element data;
	queuePointer link;
}queue;
stackPointer top;
queuePointer front, rear;

void addStack(stackPointer *top, element d)
{
	stackPointer temp;
	temp = (stack*)malloc(sizeof(stack));
	temp->data = d;
	temp->link = *top;
	*top = temp;
}

void deleteStack(stackPointer *top)
{
	if (*top)
	{
		stackPointer temp;
		temp = *top;
		*top = temp->link;
		free(temp);
	}
	else
	{
		printf("삭제할 스텍이 없습니다.");
	}
}

void addQueue(queuePointer *front,queuePointer *rear, element d)
{
	queuePointer temp;
	temp = (queue*)malloc(sizeof(queue));
	temp->data = d;
	temp->link = NULL;
	if (*front)
	{
		(*rear)->link = temp;
		(*rear) = temp;
	}
	else
	{
		*front = temp;
		*rear = temp;
	}
}

void deleteQueue(queuePointer *front)
{
	if (*front)
	{
		queuePointer temp;
		temp = *front;
		*front = temp->link;
		free(temp);
	}
	else
	{
		printf("삭제할 큐가 없습니다.");
	}
}

void printStack(stackPointer top)
{
	stackPointer temp;
	while (top)
	{
		printf("%d ",top->data.key);
		temp = top;
		top = temp->link;
		free(temp);
	}
}

void printQueue(queuePointer front)
{
	queuePointer temp;
	while (front)
	{
		printf("%d ", front->data.key);
		temp = front;
		front = temp->link;
		free(temp);
	}
}

int main()
{
	front = top = rear = NULL;
	int check;
	element data;
	char k;
	FILE*fp = fopen("input.txt", "r");
	while (1)
	{
		k = fscanf(fp,"%d", &check);
		if (k == EOF) break;
		if (check == 0)
		{
			fscanf(fp,"%d", &data.key);
			addStack(&top, data);
			addQueue(&front,&rear, data);
		}
		else if (check == 1)
		{
			deleteStack(&top);
			deleteQueue(&front);
		}
	}
	printStack(top);
	printf("\n");
	printQueue(front);
	fclose(fp);
	system("pause");
}