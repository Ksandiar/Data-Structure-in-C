#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int simpleFind(int i);
void simpleUnion(int i, int j);
int parent[9]; /*Representation of disjoint sets in an array*/
int adj[9][9]; /*Adjacency Matrix*/
typedef struct edge
{
	int u, v, w;
}edge;
void sort(edge[], int);
edge edgel[36]; /*List of edges*/

int a, b,vertexn,en=1,i,j,k,edgen,min,mincost=0;
int main(void) {
	printf("Initialize Kruskal's Algorithm\n");
	printf("Enter number of vertices (At maximum 9): ");
	scanf("%d", &vertexn);
	printf("\n");
	printf("Enter the cost adjacency matrix (The costs should be less than 999)\n");

	/*Scan adjacency matrix*/
	for (i = 0; i < vertexn; i++)
	{
		for (j = 0; j < vertexn; j++)
		{
			scanf("%d", &adj[i][j]);
			if (adj[i][j] == 0)
				adj[i][j] = 999;
		}
	}
	printf("\n");
	edgen = ((vertexn * vertexn) - vertexn) / 2; /*Number of valid edges in the graph*/
	
	/*Represent the graph through list of edges(u,v,w)*/
	k = 0;
	for (i = 0; i < vertexn; i++) {
		for (j = i+1; j < vertexn; j++) {
			edgel[k].u = i;
			edgel[k].v = j;
			edgel[k].w = adj[i][j];
			k++;
		}
	}
	/*Sort the list of edges by weight*/
	sort(edgel, edgen);
	
	/*Initializing Sets*/
	for (i = 0; i < vertexn; i++) {
		parent[i] = -1;
	}
	/*Main Part for Kruskal's Alg*/
	for (i = 0; i < edgen; i++) {
		if (simpleFind(edgel[i].u) != simpleFind(edgel[i].v)) { /*If the vertices in the edge are in different sets*/
			simpleUnion(edgel[i].u, edgel[i].v); /*DO Union operation between two sets*/
			a = edgel[i].u ; b = edgel[i].v; min = edgel[i].w;
			printf("edge %d (%d,%d) = %d\n", en, a, b, min);
			en++;
			mincost += min;
		}
		if (en >= vertexn) break;
	}
	printf("\nMinimum cost: %d\n", mincost);
	return 1;
}

/*Function for finding it's own set in disjoint sets*/
int simpleFind(int i) {
	for (; parent[i] >= 0; i = parent[i])
		;
	return i;
}

/*Function for an Union operation of two disjoint sets*/
void simpleUnion(int i, int j) {
	parent[simpleFind(i)] = j;
}

/*Function for selection sort*/
void sort(edge list[], int n) {
	int i, j, min;
	edge temp;
	for (i = 0; i < n - 1; i++) {
		min = i;
		for (j = i + 1; j < n; j++) {
			if (list[j].w < list[min].w) {
				min = j;
			}
		}
		temp = list[i];
		list[i] = list[min];
		list[min] = temp;
	}
}