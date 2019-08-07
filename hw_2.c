#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

//그래프노드
typedef struct node* nodePtr;
typedef struct node {
	int x,y;
	nodePtr link;
}node;
//다리 연결가능 정보
typedef struct edge* edgePtr;
typedef struct edge {
	int x, y;
}edge;
//테스트케이스 노드
typedef struct teca* tecaPtr;
typedef struct teca {
	int cost, n, m, cl, cr,N,D;
	//N:테스트케이스 순번, D:cl>cr여부
	edgePtr edges;
	tecaPtr link, link_same_cost;
	nodePtr link_g;
}teca;

tecaPtr readFile(int *tn)
{
	tecaPtr T;
	edgePtr temp;
	int n, m, cl, cr, x, y;
	int i, j;
	FILE* fp = fopen("input.txt", "r");
	fscanf(fp, "%d", tn);
	T = (tecaPtr)malloc(sizeof(teca)**tn);
	for (i = 0; i < *tn; i++)
	{
		fscanf(fp, "%d %d %d %d", &n, &m, &cl, &cr);
		(T + i)->N = i + 1;
		(T + i)->n = n;
		(T + i)->m = m;
		(T + i)->cl = cl;
		(T + i)->cr = cr;
		(T + i)->edges = (edgePtr)malloc(sizeof(edge)*(m + 1));
		(T + i)->link = NULL;
		(T + i)->link_same_cost = NULL;
		for (j = 1; j < m + 1; j++)
		{
			temp = ((T + i)->edges + j);
			fscanf(fp, "%d %d", &x, &y);
			temp->x = x;
			temp->y = y;
		}
	}
	fclose(fp);
	return T;
}

int findParent(int*set, int x, int y)
{
	int i, temp_x, temp_y;
	while (x > 0)
	{
		temp_x = x;
		x = *(set + x);
	}
	while (y > 0)
	{
		temp_y = y;
		y = *(set + y);
	}
	if (temp_y == temp_x) return 0;
	else
	{
		*(set + temp_y) = temp_x;
		return 1;
	}
}

int makeGraph(tecaPtr test, nodePtr graph, int* set,int D)
{
	int i, bcnt = 0;
	nodePtr n1, n2, temp_n1, temp_n2 = NULL;
	edgePtr temp_e;
	graph->link = NULL;
	graph->x = graph->y = 0;
	for (i = 0; i < test->n + 1; i++)
	{
		set[i] = -1;
	}
	if (D)
	{
		for (i = 1; i < test->m + 1; i++)
		{
			temp_e = test->edges + i;
			if (findParent(set, temp_e->x, temp_e->y))
			{
				bcnt++;
				n1 = (nodePtr)malloc(sizeof(node));
				n1->x = temp_e->x;
				n1->y = temp_e->y;
				n1->link = NULL;
				temp_n1 = graph;
				while (temp_n1)
				{
					temp_n2 = temp_n1;
					temp_n1 = temp_n1->link;
				}
				temp_n2->link = n1;
			}
		}
	}
	return bcnt;
}

int insertHeap(tecaPtr heapArr, teca a, int l, nodePtr graph)
{
	int i, pn, n = l;
	teca temp;
	tecaPtr temp1, temp2 = NULL;
	a.link_g = graph;
	if (n == 1)
	{
		*(heapArr + 1) = a;
		return ++l;
	}

	else
	{
		temp1 = (heapArr + 1);
		while (temp1)
		{
			temp2 = temp1;
			temp1 = temp1->link_same_cost;
		}
		*(heapArr + n) = a;
	}
	for (; n > 1;)
	{
		pn = n / 2;
		if (((heapArr + n)->cost) < (heapArr + pn)->cost)
		{
			temp = *(heapArr + pn);
			*(heapArr + pn) = *(heapArr + n);
			*(heapArr + n) = temp;
			n = pn;
		}
		else if (((heapArr + n)->cost) == (heapArr + pn)->cost)
		{
			temp1 = (tecaPtr)malloc(sizeof(teca));
			*temp1 = a;
			temp2->link_same_cost = temp1;
			return l;
		}
		else return ++l;
	}
	if ((heapArr + 1)->cost == (heapArr+l)->cost) 
	{
		temp1 = (tecaPtr)malloc(sizeof(teca));
		*temp1 = a;
		temp2->link_same_cost = temp1;
		return l;
	}
	else return ++l;
}

int main()
{
	tecaPtr heapArr,temp2;
	tecaPtr T;
	nodePtr graph;
	nodePtr temp1;
	int** set;
	int i, j, l, tn = 0, bcnt, mcnt, max_cost = 0;

	T = readFile(&tn);
	heapArr = (tecaPtr)malloc(sizeof(teca)*(tn + 1));
	graph = (nodePtr)malloc(sizeof(node)*tn);
	set = (int**)malloc(sizeof(int*)*tn);
	for (i = 0; i < tn; i++)
	{
		bcnt = mcnt = 0;
		if (((T + i)->cl) > ((T + i)->cr)) (T + i)->D = 1;
		else (T + i)->D = 0;
		*(set + i) = (int*)malloc(sizeof(int)*((T + i)->n + 1));
		bcnt = makeGraph((T + i), (graph + i), *(set + i),(T+i)->D);
		for (j = 1; j < (T + i)->n + 1; j++)
		{
			if (*(*(set + i) + j) == -1) mcnt++;
		}
		(T + i)->cost = (T + i)->cl*mcnt + (T + i)->cr*bcnt;
	}
	l = 1;
	for (i = 0; i < tn; i++)
	{
		l = insertHeap(heapArr, *(T + i), l, (graph + i));
	}
	l--;
	temp2 = (heapArr + 1);
	do {
		printf("%d\n", temp2->N);
		temp1 = temp2->link_g->link;
		while (temp1)
		{
			printf("%d %d\n", temp1->x, temp1->y);
			temp1 = temp1->link;
		}
		temp2 = temp2->link_same_cost;
	}while(temp2);
	printf("%d\n", (heapArr + 1)->cost);
	free(graph);
	system("pause");
}