#include <math.h>
#include <iostream>
#include <stdio.h>
#include "graph.h"
#include "heap.h"


using namespace std;

int heapifyCalls=0;

HEAP* initialize(int n)
{
	HEAP* heap = new HEAP;
	heap->capacity = n;
	heap->size =0;
	heap->H = new pELEMENT[n+1];	//create dynamically allocated array of elements
	return heap;
}

void printHeap(HEAP* heap)
{

	if(heap == NULL)
	{
		cout << "Error: cannot print" << endl;
	}
	else
	{
		cout << "capacity=" << heap->capacity << ", " << "size=" << heap->size << endl;

		//PRINT ELEMENTS OF THE HEAP SEPARATED BY A COMMA
		int i=1;

		if(heap->size>0)
		{
			for(i=1;i<heap->size;i++)	//print from element 1 to size-1, then print heap[heap->size] w/o comma
			{
				cout << heap->H[i]->key << ", ";
			}
			cout << heap->H[i]->key << endl;	//PRINT FINAL ELEMENT OF THE HEAP W/OUT COMMA
		}

	}

}

int parent(int i)
{
	return floor(i/2);
}

int left(int i)
{
	return 2*i;
}

int right(int i)
{
	return (2*i+1);
}

void swap(HEAP* heap,int index1, int index2)
{
	ELEMENT* temp;

	temp = heap->H[index1];
	heap->H[index1] = heap->H[index2];
	heap->H[index2] = temp;
}

void minHeapify(HEAP* heap, int i)
{
	int smallest;
	int L = left(i);
	int R = right(i);

	if (L<=heap->size && heap->H[L]->key <= heap->H[i]->key)
	{
		smallest = L;
	}
	else
	{
		smallest = i;
	}

	if (R<=heap->size && heap->H[R]->key < heap->H[smallest]->key)
	{
		smallest = R;
	}

	if(smallest != i)
	{
        //UPDATE POSITIONS AND OTHER FIELDS BEIGN SWAPPED
		swap(V[heap->H[i]->vertex]->pos, V[heap->H[smallest]->vertex]->pos);
		swap(heap->H[i]->pos, heap->H[smallest]->pos);
		swap(heap->H[i]->key, heap->H[smallest]->key);
		swap(heap->H[i]->vertex,heap->H[smallest]->vertex);

		minHeapify(heap, smallest);
		heapifyCalls++;
	}



}

void movingUp (HEAP* heap, int pos)
{
	int parent;

	parent = pos/2;
	if (pos>1 && heap->H[pos]->key < heap->H[parent]->key)
	{

		swap(heap,pos,parent);

		V[heap->H[pos]->vertex]->pos = pos;
		V[heap->H[parent]->vertex]->pos = parent;
		movingUp(heap,parent);

	}
}


int decreaseKey(HEAP* heap, int pos, int newKey, int flag)
{

	if (pos < 1 || pos > heap->size || newKey >= heap->H[pos]->key) {
	        cout << "Error in decrease key\n";
	        return 1;
	    }

	if (flag ==1){
		printf("Decrease key of vertex %d, from %12.4f to %12.4f\n",heap->H[pos]->vertex, heap->H[pos]->key, (float)newKey);
	}

	heap->H[pos]->key = newKey;
	movingUp(heap,pos);

	return 0;
}




pELEMENT extractMin(HEAP* heap, int* flag)
{
	heapifyCalls=0;
	pELEMENT min, last;
	if (heap->size < 1)
	{
		cout << "Error in DeleteMin: heap empty" << endl;
		return NULL;
	}
	else
	{
		min = heap->H[1];
		//cout << "Deleted key: " << min->key << endl;
		last = heap->H[heap->size];
		heap->size--;
		heap->H[1] = last;
		V[heap->H[1]->vertex]->pos = 1;
		minHeapify(heap,1);
		heapifyCalls++;
		V[min->vertex]->pos =0;
		return min;
	}

	if (*flag==1)
	{
		cout << "Number of Heapify calls: " << heapifyCalls << endl;
	}

}


int insert(HEAP* heap, pELEMENT element)
{

	if (heap->size >= heap->capacity)
	{
		cout << "Error in HeapInsert: Heap full..." << endl;
		return 1;
	}

	heap->size++;
	heap->H[heap->size]=element;
	heap->H[heap->size]->pos = heap->size;
	V[element->vertex]->pos = heap->size;

	movingUp(heap, heap->size);

	return 0;

}


void buildHeap(HEAP* heap,int *f)
{
	heapifyCalls=0;
	for (int i=floor(heap->size/2);i>=1; i--)
	{
			minHeapify(heap, i);
			heapifyCalls++;
	}

	if(*f==1)
	{
		cout << "Number of Heapify calls: " << heapifyCalls << endl;
	}

}













