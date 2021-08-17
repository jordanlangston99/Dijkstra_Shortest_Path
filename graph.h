#pragma once
#ifndef GRAPH_H_
#define GRAPH_H_

typedef struct TAG_NODE{
	int u;
	int v;
	float w;
	TAG_NODE* next;
}NODE;

typedef NODE* pNODE;

typedef struct TAG_VERTEX{
	int color;
	int pi;
	float d;
	int pos;
}VERTEX;

typedef VERTEX* pVERTEX;

typedef struct TAG_PATH{
	int vertex;
	TAG_PATH* next;
}PATH;

typedef PATH *pPATH;

extern pVERTEX* V;


void printPath(int n, int source, int destination, int s, int t, int pathFind);
int dijkstra(int n, pNODE* A, int s, int t, int flag);



#endif
