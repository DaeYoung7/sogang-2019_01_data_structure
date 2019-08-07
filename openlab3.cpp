#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<Windows.h>
#include<time.h>
#define MAX 56

typedef struct {
	int row;
	int col;
	int value;
}sparse;

void readFile(sparse matrix[])
{
	int i = 0, r = 0, c = 0, k, num, countValue = 0;
	FILE *fp = fopen("a[3].txt", "r");
	k = fscanf(fp, "%d %d", &matrix[0].row, &matrix[0].col);
	while(1)
	{
		k = fscanf(fp, "%d", &num);
		if (k == EOF) break;
		if (num != 0)
		{
			i++;
			countValue++;
			matrix[i].row = r;
			matrix[i].col = c;
			matrix[i].value = num;
		}
		c++;
		if (c % 8 == 0)
		{
			c = 0;
			r++;
		}
	}
	matrix[0].value = countValue;
}

void countRowterms(int rowTerms[], sparse matrix[])
{
	int i;
	for (i = 0; i < matrix[0].value; i++)
	{
		rowTerms[matrix[i+1].col]++;
	}
}

void makeRowterms(int rowTerms[], sparse matrix[])
{
	int i, temp1 = 1, temp2;
	for (i = 0; i < matrix[0].col; i++)
	{
		temp2 = rowTerms[i + 1];
		rowTerms[i + 1] = rowTerms[i] + temp1;
		temp1 = temp2;
	}
	rowTerms[0] = 1;
}

void fastTranspose(int rowTerms[], sparse matrix[], sparse matrixT[])
{
	int i, j;
	for (i = 0; i < matrix[0].value; i++)
	{
		j = rowTerms[matrix[i + 1].col]++;
		matrixT[j].row = matrix[i + 1].col;
		matrixT[j].col = matrix[i + 1].row;
		matrixT[j].value = matrix[i + 1].value;
	}
	matrixT[0].row = matrix[0].col;
	matrixT[0].col = matrix[0].row;
	matrixT[0].value = matrix[0].value;
}

void printMatrixT(sparse matrixT[])
{
	int i;
	for (i = 0; i <= matrixT[0].value; i++)
	{
		printf("%d %d %d\n", matrixT[i].row, matrixT[i].col, matrixT[i].value);
	}
}

int main()
{
	int k;
	clock_t start = clock();
	double duration;
	sparse matrix[MAX+1], matrixT[MAX+1];
	int rowTerms[MAX] = { 0 };
	FILE *fp = fopen("a[3].txt", "r");
	readFile(matrix);
	countRowterms(rowTerms, matrix);
	makeRowterms(rowTerms, matrix);
	fastTranspose(rowTerms, matrix, matrixT);
	printMatrixT(matrixT);
	duration = ((double)(clock() - start)) / CLOCKS_PER_SEC;
	printf("[Finished in %.3f\s]\n", duration);
	system("pause");
	return 0;
}