#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#include "util.h"
#include "heap.h"

using namespace std;

int nextWord(char* c);
int dijkstra(int n, pNODE* A, int s, int t, int flag);


int main(int argc, char *argv[])
{
	ifstream ifile;
	string line;

	pNODE* A;
	pNODE node;

	char word[256];
	char word2[256];
	int n, m, directed_graph, i, source;
	int s, s_new, t, t_new, source_new, destination, destination_new;
	int u, v, edge_id, flag, flag_new;
	float w;
	int r_value=0;
	int pathFind=1;

	if (argc != 3){
		printf("Command Format; %s <graph_file> <direction> \n", argv[0]);
		exit(1);

	}

	if (strcmp(argv[2], "directed\0") == 0){
		directed_graph=1;
	}
	if (strcmp(argv[2], "undirected\0") == 0){
		directed_graph=0;
	}

	//OPEN THE GRAPH FILE
	ifile.open(argv[1]); //open the file
	if (!ifile.is_open())
	{
		cout << "ErrorGLX1: cannot open file fore reading." << endl;
	}

	ifile >> n;
	ifile >> m;

    //CREATE ADJACENCY LIST A
    A = (pNODE*) calloc (n+1, sizeof(pNODE));

    if(!A)
	{
		cout << "error: failed to create A" << endl;
	}

    //READ IN THE EDGES ALONG WITH THEIR CORRESPONDING VERTICES AND WEIGHT
	for (i=1; i<=m; i++)
	{
		ifile >> edge_id;
		ifile >> u;
		ifile >> v;
		ifile >> w;

        //CREATE A NEW NODE TO STORE READ VALUES
		node = new NODE;
		if (!node)
		{
			cout << "Error: failed to create node" << endl;
		}

        //CREATE NODE REPRESENTING CONNECTION FROM U->V WITH WEIGHT W
        //STORE RECENTLY READ VALUES IN ADJACECNY LIST NODE
		node->u = u;
		node->v = v;
		node->w = w;
		node->next = A[u];
		A[u] = node;

		//end for undirected graphs
		//begin code for directed graphs
        //IF UNDIRECTED, CREATE NODE REPRESENTING A CONNECTION IN THE OPPOSITE DIRECTION AS WELL
		if (!directed_graph)
		{
			node = new NODE;
			if (!node)
			{
				cout << "failed to create node"<< endl;
				exit(1);
			}
        
            //CREATE NODE REPRESENTING CONNECTION FROM V->U WITH WEIGHT W
			node->u = v;
			node ->v = u;
			node ->w = w;
			node ->next = A[v];
			A[v] = node;
		}

	}



    //INITIALIZE VALUES AND CLOSE FILE
	source =0;
	destination = 0;
	ifile.close();


	//BEGIN QUERY PART
	while (1){
		r_value = nextWord(word);
		if (!r_value)
		{
			cout << "ErrorGLX: EOF" << endl;
			continue;
		}

		if (strcmp(word, "stop") == 0)
		{
			cout << "Query: " << word << endl;
			break;
		}

		if (strcmp(word, "find") == 0)
		{
            //READ IN SOURCE AND DESTINATION NODES FOR DIJKSTRA FUNCTION CALL
			cin >> source_new;
			cin >> destination_new;
			cin >> flag_new;

			printf("Query: %s %d %d %d\n", word, source_new, destination_new, flag_new);

			if (source_new < 1 || source_new > n || flag_new < 0|| flag_new > 1){
				cout << "Error: invalid find query" << endl;
			}
			else{
                //OVERWRITE VARIABLES WITH NEW INPUT IF THE INPUT IS VALID
				source = source_new;
				destination = destination_new;
				flag = flag_new;
				pathFind = dijkstra(n, A, source, destination, flag);
			}
		}
		else if (strcmp(word, "write") == 0)
		{
			r_value = nextWord(word2);
			if (!r_value){
				cout << "ErrorGLX4: EOF" << endl;
				continue;
			}

			if (strcmp(word2, "path") == 0)
			{
				cin >> s_new;
				cin >> t_new;

				printf("Query: %s %s %d %d\n", word, word2, s_new, t_new);
                
                //TEST IF DIJKSTRA HAS BEEN RUN YET
				if (source == 0){
					cout << "Error: no path computation done" << endl;
				}
                //TEST IF THERE IS A POSSIBILITY FOR A PATH BETWEEN GIVEN VERTICES
				else if (s_new != source || t_new == s_new || t_new < 1 || t_new > n)
				{
					cout << "Error: invalid source destination pair" << endl;
				}
				else
				{
                    //OVERWRITE VARIABLES IF INPUT WAS VALID
					s = s_new;
					t = t_new;
					printPath(n, source, destination, s, t, pathFind);
				}


			}



		}
		else
		{
			cout << "ErrorGLX: Bad input" << endl;
		}

	}


	
}






