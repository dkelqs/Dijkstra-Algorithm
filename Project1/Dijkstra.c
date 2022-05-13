#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define maxvertex 100
#define MAX 1000000

#define true 1
#define false 0
int distance[maxvertex];
int found[maxvertex];

typedef struct graphtype
{
	int n;
	int weight[maxvertex][maxvertex];
} graphtype;

int choose(int distance[], int n, int found[])
{
	int min, minpos;
	min = INT_MAX;
	minpos = -1;
	for (int i = 0; i < n; i++)
	{
		if (distance[i] < min && !found[i])
		{
			min = distance[i];
			minpos = i;
		}
	}
	return minpos;
}

void print_status(graphtype* g)
{
	static int step = 1;
	printf("STEP %d: ", step++);
	printf("distance: ");
	for (int i = 0; i < g->n; i++)
	{
		if (distance[i] == MAX)
			printf(" * ");
		else
			printf("%d ", distance[i]);
	}
	printf("\n");
	printf(" found: ");
	for (int i = 0; i < g->n; i++)
		printf("%d ", found[i]);
	printf("\n");
}

void shortest_path(graphtype* g, int start)
{
	int u;
	for (int i = 0; i < g->n; i++)
	{
		distance[i] = g->weight[start][i];
		found[i] = false;
	}
	found[start] = true;
	distance[start] = 0;
	for (int i = 0; i < g->n - 1; i++)
	{
		print_status(g);
		u = choose(distance, g->n, found);
		found[u] = true;
		for (int w = 0; w < g->n; w++)
		{
			if (!found[w])
			{
				if (distance[u] + g->weight[u][w] < distance[w])
				{
					distance[w] = distance[u] + g->weight[u][w];
				}
			}
		}
	}
}

int main(void)
{
	graphtype g = { 7,
	{{ 0, 7, MAX, MAX, 3, 10, MAX },
	{ 7, 0, 4, 10, 2, 6, MAX },
	{ MAX, 4, 0, 2, MAX, MAX, MAX },
	{ MAX, 10, 2, 0, 11, 9, 4 },
	{ 3, 2, MAX, 11, 0, MAX, 5 },
	{ 10, 6, MAX, 9, MAX, 0, MAX },
	{ MAX, MAX, MAX, 4, 5, MAX, 0 } }
	};
	shortest_path(&g, 0);
	return 0;
}