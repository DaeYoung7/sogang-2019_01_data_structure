#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>

typedef struct threadedTree *threadedPointer;
typedef struct threadedTree {
	short int leftThread;
	threadedPointer leftChild;
	char data;
	threadedPointer rightChild;
	short int rightThread;
}threadedTree;

threadedPointer insucc(threadedPointer tree)
{
	threadedPointer temp;
	temp = tree->rightChild;
	if (tree->data == '-')
	{
		while (!temp->leftThread)
		{
			temp = temp->leftChild;
		}
		return temp;
	}
	if (!tree->rightThread)
	{
		while (!temp->leftThread)
		{
			temp = temp->leftChild;
		}
	}
	return temp;
}

void tinorder(threadedPointer tree)
{
	threadedPointer temp = tree;
	for (;;)
	{
		temp = insucc(temp);
		if (temp == tree) break;
		printf("%c ", temp->data);
	}
}

void insertRight(threadedPointer s, threadedPointer r)
{
	threadedPointer temp;
	r->leftThread = 1;
	r->rightThread = s->rightThread;
	r->leftChild = s;
	r->rightChild = s->rightChild;
	s->rightThread = 0;
	s->rightChild = r;
	if (!r->rightThread)
	{
		temp = insucc(r);
		temp->leftChild = r;
	}
}

void insertLeft(threadedPointer s, threadedPointer l)
{
	threadedPointer temp;
	l->leftThread = s->leftThread;
	l->leftChild = s->leftChild;
	l->rightChild = s;
	l->rightThread = 1;
	s->leftThread = 0;
	s->leftChild = l;
	if (!l->leftThread)
	{
		if (!l->leftChild->rightThread) l->leftChild->rightChild = l;
		else l->leftChild = l;
	}
}

threadedPointer getNewNode(char data)
{
	threadedPointer a;
	a = (threadedPointer)malloc(sizeof(threadedTree));
	a->data = data;
	a->rightThread = 1;
	a->leftThread = 1;
	a->leftChild = a;
	a->rightChild = a;
	return a;
}


int main()
{
	threadedPointer root = getNewNode('-');
	insertLeft(root, getNewNode('A'));
	insertLeft(root->leftChild, getNewNode('B'));
	insertLeft(root->leftChild->leftChild, getNewNode('D'));
	insertLeft(root->leftChild->leftChild->leftChild, getNewNode('H'));
	insertRight(root->leftChild->leftChild->leftChild, getNewNode('I'));
	insertRight(root->leftChild->leftChild, getNewNode('E'));
	insertRight(root->leftChild, getNewNode('C'));
	insertLeft(root->leftChild->rightChild, getNewNode('F'));
	insertRight(root->leftChild->rightChild, getNewNode('G'));
	//printf("%d %d", root->leftThread,root->rightThread);
	tinorder(root);
	system("pause");
	return 0;
}