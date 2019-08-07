#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

#define MAX_TERMS 100
typedef struct treeNode* treePtr;
typedef struct treeNode {
	treePtr lchild;
	int data;
	treePtr rchild;
}treeNode;

void inorder(treePtr tree)
{
	if (tree)
	{
		inorder(tree->lchild);
		printf("%d ", tree->data);
		inorder(tree->rchild);
	}
}

void postorderFree(treePtr tree)
{
	if (tree)
	{
		postorderFree(tree->lchild);
		postorderFree(tree->rchild);
		free(tree);
	}
}

void preorder(treePtr tree)
{
	if (tree)
	{
		printf("%d ", tree->data);
		preorder(tree->lchild);
		preorder(tree->rchild);
	}
}
void insert(treePtr* tree, int d)
{
	treePtr root = *tree;
	treePtr temp = (treePtr)malloc(sizeof(treeNode));
	temp->data = d;
	temp->lchild = temp->rchild = NULL;
	if (root)
	{
		for(;;)
		{
			if (root->data < d)
			{
				if (root->rchild) root = root->rchild;
				else
				{
					root->rchild = temp;
					break;
				}
			}
			else
			{
				if (root->lchild) root = root->lchild;
				else
				{
					root->lchild = temp;
					break;
				}
			}
		}
	}
	else (*tree) = temp;
}
treePtr modifiedSearch(treePtr tree, int s)
{
	if (!tree) return NULL;
	if (tree->data == s) return tree;
	if (tree->data < s) return modifiedSearch(tree->rchild, s);
	return modifiedSearch(tree->lchild, s);
}

int main()
{
	int i, n, A[MAX_TERMS];
	char k;
	treePtr tree = NULL;
	FILE*fp = fopen("input.txt", "r");
	fscanf(fp, "%d", &n);
	for (i = 0; i < n; i++)
	{
		fscanf(fp, "%d", &A[i]);
		insert(&tree, A[i]);
	}
	fclose(fp);
	inorder(tree);
	printf("\n");
	preorder(tree);
	postorderFree(tree);
	system("pause");
}