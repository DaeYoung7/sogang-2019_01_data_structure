#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include<string.h>

typedef struct {
	int coef;
	int expo;
}forPoly;


int padd(forPoly a[], int sum, int start1, int finish1, int start2, int finish2)
{
	int sumtemp = sum;

	while (start1 <= finish1 && start2 <= finish2)
	{
		switch ((a[start1].expo > a[start2].expo) ? 1 : a[start1].expo == a[start2].expo ? 0 : -1)
		{
		case -1:
		{
			a[sumtemp].expo = a[start2].expo;
			a[sumtemp++].coef = a[start2].coef;
			start2++;
			break;
		}
		case 0:
		{
			if (a[start1].coef + a[start2].coef)
			{
				a[sumtemp].expo = a[start1].expo;
				a[sumtemp++].coef = a[start1].coef + a[start2].coef;
			}
			start1++;
			start2++;
			break;
		}
		case 1:
		{
			a[sumtemp].expo = a[start1].expo;
			a[sumtemp++].coef = a[start1].coef;
			start1++;
			break;
		}
		}
	}
	for (; start1 <= finish1; start1++)
	{
		a[sumtemp].expo = a[start1].expo;
		a[sumtemp++].coef = a[start1].coef;
	}
	for (; start2 <= finish2; start2++)
	{
		a[sumtemp].expo = a[start2].expo;
		a[sumtemp++].coef = a[start2].coef;
	}
	return sumtemp;
}

void readPoly(forPoly a[], int count[])
{
	int fwalkA = 0;
	int fwalkB = 0;
	int fwalkC = 0;
	int res = 0;
	FILE* fp1 = fopen("A.txt", "r");
	while (1)
	{
		res = fscanf(fp1, "%d %d", &a[fwalkA].coef, &a[fwalkA].expo);
		if (res == EOF) break;
		fwalkA++;
	}
	fclose(fp1);
	FILE* fp2 = fopen("B.txt", "r");
	while (1)
	{
		res = fscanf(fp2, "%d %d", &a[fwalkA + fwalkB].coef, &a[fwalkA + fwalkB].expo);
		if (res == EOF) break;
		fwalkB++;
	}
	fclose(fp2);
	FILE* fp3 = fopen("C.txt", "r");
	while (1)
	{
		res = fscanf(fp3, "%d %d", &a[fwalkA + fwalkB + fwalkC].coef, &a[fwalkA + fwalkB + fwalkC].expo);
		if (res == EOF) break;
		fwalkC++;
	}
	fclose(fp3);
	count[0] = fwalkA;
	count[1] = fwalkB;
	count[2] = fwalkC;
	return;
}

void printPoly(forPoly a[], int sumStart, int sumFinish)
{
	for (int i = sumStart; i < sumFinish; i++)
	{
		if (i != sumFinish - 1 )
		{
			printf("(%d,%d), ", a[i].coef, a[i].expo);
		}
		else
		{
			printf("(%d,%d)\n", a[i].coef, a[i].expo);
		}
	}
	return;
}

int main()
{
	clock_t start = clock();
	double duration;
	int count[3];
	forPoly a[100];
	readPoly(a, count);
	int sum = count[0] + count[1] + count[2];
	int sumAB = padd(a, sum,0,count[0]-1,count[0],count[0]+count[1]-1);
	int sumC = padd(a, sumAB,count[0]+count[1], count[0]+count[1]+count[2]-1, sum,sumAB);
	printPoly(a, sumAB, sumC-1);
	duration = ((double)(clock() - start)) / CLOCKS_PER_SEC;
	printf("[Finished in %.3f\s]", duration);
}