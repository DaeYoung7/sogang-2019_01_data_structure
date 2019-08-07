#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define _CRT_SECURE_NO_WARNINGS
int* sort(int *a, int size)
{
	for (int j = 0; j < size - 1; j++)
	{
		for (int o = j + 1; o < size; o++)
		{
			if (a[o] < a[j])
			{
				int temp = a[j];
				a[j] = a[o];
				a[o] = temp;
			}
			continue;
		}
	}
	return a;
}
int main()
{
	clock_t start_all = clock();
	int k = 0, num, i = 0;
	FILE *fp = fopen("lab1.data", "r");
	int *arrInput = (int*)calloc(1, sizeof(int));
	while (1)
	{
		k = fscanf(fp, "%d", &num);
		if (k == EOF) break;
		arrInput[i] = num;
		i++;
		arrInput = (int*)realloc(arrInput, (i + 1) * sizeof(int));
	}
	fclose(fp);
	printf("Input : ");
	for (int i = 0; i < 10; i++)
	{
		printf("%d", arrInput[i]);
	}
	arrInput = sort(arrInput, i);
	printf("\nOutput : ");
	for (int i = 0; i < 10; i++)
	{
		printf("%d", arrInput[i]);
	}
	free(arrInput);
	int a[100];
	double takeTime;
	printf("\n	      n  	repetitions  	time\n");
	double sum = 0;
	for (int i = 0; i < 101; i += 10)
	{
		int rep = 0;
		clock_t start = clock();
		do
		{
			rep++;
			for (int p = 0; p < i; p++)
			{
				a[p] = p - 1;
				sort(a, i);
			}
		} while (clock() - start < 10);
		takeTime = ((double)(clock() - start)) / CLOCKS_PER_SEC;
		takeTime /= rep;
		sum += takeTime;
		printf("\t%7d \t%7d \t%7f\n", i, rep, takeTime);
	}
	double take_time_all = ((double)(clock() - start_all));
	printf("[Finished in %.1f s]", take_time_all);
}