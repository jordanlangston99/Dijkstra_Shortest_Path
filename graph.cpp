#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stack>
#include "graph.h"
#include "heap.h"

pVERTEX* V;
int fullyComputed;

using namespace std;

int decreaseKey(HEAP* heap, int pos, int newKey, int flag);

int dijkstra(int n, pNODE* A, int s, int t, int flag){

    //DELETE EXISTING VERTEX ARRAY IF IT ALREADY EXISTS
	if(V)
	{
		for (int i=1; i<=n;i++)
		{
			delete (V[i]);
		}
	}
	delete V;

    //INITIALIZE VALUES FOR DIJKSTRA
	int u,v;
	float w;
	V = new pVERTEX[n+1];
	HEAP* heap;
	ELEMENT* element;
	pNODE node;

    //FILL VERTEX ARRAY WITH INITIALIZED VERTICES
	for (int i=1;i<=n;i++)
	{
		pVERTEX vertex = new VERTEX;
		vertex->color = 1;
		vertex->pi = NULL;
		V[i] = vertex;
	}

	//set initial source node color to grey  and set its distance to zero
	V[s]->color =2;
	V[s]->d = 0;

	//initialize heap and insert source node element
	heap = initialize(n);

	element = new ELEMENT;
	element->vertex = s;
	element->key = 0;

	insert(heap, element);

	if (flag == 1){
				printf("Insert vertex %d, key=%12.4f\n", element->vertex, element->key);
			}



	//while the priority queue (min-heap) is not empty, extract the element closest to the source node (min key)
	while (heap->size){
		element = extractMin(heap,&flag);


		if (flag ==1){
			printf("Delete vertex %d, key=%12.4f\n", element->vertex, element->key);
		}

		u = element->vertex;

		V[u]->color = 3;

        //TEST IF EXTRACTED VERTEX IS DESTINATION VERTEX
		if (element->vertex == t){
			fullyComputed =0;
			return 0;
		}

        //MEMORY DEALLOCATION
		delete element;

        //SET NODE EQUAL TO THE VERTEX THAT HAS JUST BEEN EXTRACTED
		node = A[u];
		while (node){
			v = node->v;
			w = node->w;

			//check if the node is white and needs to be explored
			if (V[v]->color == 1){
				V[v]->d = V[u]->d + w;					//initiaize vertex weight
				V[v]->pi = u;							//initialize predecessor
				V[v]->color = 2;						//COLOR NODE GRAY
				element = new ELEMENT;					//CREATE NEW ELEMENT TO INSERT INTO PRIORITY QUEUE
				element->vertex =v;
				element->key = V[v]->d;
				insert(heap,element);
				if (flag == 1)
				{
					printf("Insert vertex %d, key=%12.4f\n", element->vertex, element->key);
				}

			}//CHECK IF THE VERTEX CAN BE RELAXED
			else if(V[v]->d > V[u]->d +w)
			{
				V[v]->d = V[u]->d+w;				//UPDATE VERTEX DISTANCE TO SOURCE
				V[v]->pi = u;						//UPDATE VERTEX PREDECESSOR
				//cout << "V[v]->pos: " << V[v]->pos << endl;
				decreaseKey(heap,V[v]->pos,V[v]->d,flag);
			}
			node = node->next;						//MOVE TO THE NEXT NODE IN THE ADJACENCY LIST
		}


	}

    //INDICATE THE GRAPH HAS BEEN FULLY EXPLORED
	fullyComputed =1;
	return 0;
}


void printPath(int n, int source, int destination, int s, int t, int pathFind)
{
	std::stack<int> stackyStack;
	int u = t;
	float pathWeight =0;

	if(pathFind ==1)
	{
		cout << "Error: no path computation done" << endl;
		return;
	}
	else
	{
		//CHECK IF SOURCE-DESTINATION NODE PATH HAS BEEN COMPUTED PARTIALLY, FULLY, OR NOT AT ALL
		if (V[t]->color == 1 && fullyComputed ==0)
		{
			cout << "No " << s << "-" << t << " path has been computed." << endl;
			return;
		}
		else if(V[t]->color == 1 && fullyComputed == 1)
		{
			cout << "No " << s << "-" << t << " path exists." << endl;
			return;
		}
		else if (V[t]->color == 2) //MEANING DESTINATION NODE HAS NOT BEEN EXPLORED
		{
			cout << "Path not known to be shortest: <";
		}
		else if (V[t]->color == 3)
		{
			cout << "Shortest path: <";
		}


		//CREATE THE PATH BY FOLLOWING THE PREDECESSORS AND PUSHING VERTICES ONTO A STACK
		stackyStack.push(u);
		while (V[u]->pi)
		{
			pathWeight += V[u]->d;
			stackyStack.push(V[u]->pi);     //push predecessor onto the stack
			u = V[u]->pi;                   //move pointer to predecessor
		}

		//PRINT THE PATH
		cout << stackyStack.top();
		stackyStack.pop();

		while(!stackyStack.empty())
		{
			cout <<", ";
			cout << stackyStack.top();
			stackyStack.pop();
		}
		cout << ">" << endl;

		printf("The path weight is: %12.4f\n", V[t]->d);


	}

}













