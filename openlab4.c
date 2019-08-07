#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<windows.h>
#include<string.h>

int* fail(char pat[], int*countK)
{
	int i = -1, j;
	int leng = strlen(pat);
	int failure[100];
	int tmp = *countK;
	failure[0] = -1;
	for (j = 1; j < leng; j++)
	{
		i = failure[j - 1];
		while ((pat[j] != pat[i + 1]) && (i >= 0))
		{
			i = failure[i];
			tmp++;
		}
		if (pat[j] == pat[i + 1])
		{
			failure[j] = i + 1;
		}
		else
		{
			failure[j] = -1;
		}
		tmp++;
	}
	*countK = tmp;
	return failure;
}

int kmp(char string[], char pat[], int*failure,int*countK)
{
	int i = 0, j = 0, tmp = *countK;
	int lengs = strlen(string);
	int lengp = strlen(pat); 
	while ((i < lengs) && (j < lengp))
	{
		if ((j != 0) && (string[i] != pat[j]))
		{
			j = failure[j - 1] + 1;
		}
		else if (string[i] == pat[j])
		{
			i++, j++;
		}
		else i++;
		tmp++;
	}
	*countK = tmp;
	return ((j == lengp) ? 1 : 0);
}
int nfind(char string[], char pat[], int *countN)
{
	int lengp = strlen(pat), lengs = strlen(string), tmp = *countN;
	int i = (lengp - 1), j = (lengp - 1);
	while (i < lengs)
	{
		if (string[i] == pat[j])
		{
			tmp++;
			int temp = i - lengp + 1;
			for (j = 0; j < lengp - 1; j++)
			{
				tmp++;
				if (string[temp] == pat[j])
				{
					temp++;
				}
				else j = lengp;
			}
			if (j == lengp - 1) break;
		}
		else
		{
			tmp++;
		}
		i++;
		j = lengp - 1;
	}
	*countN = tmp;
	return ((i==lengs) ? 0: 1);
}

int main()
{
	int countK = 0, countN = 0, tempK, tempN;
	int *failure;
	char *testN;
	char string[100], pat[100];
	scanf("%s", string);
	scanf("%s", pat);
	tempN = nfind(string, pat, &countN);
	failure = fail(pat, &countK);
	tempK = kmp(string, pat, failure, &countK);
	if (tempK&&tempN) printf("nfind:    YES %d\nkmp:     YES %d", countN, countK);
	else printf("nfind:    NO %d\nkmp:     NO %d", countN, countK);
	system("pause");
}