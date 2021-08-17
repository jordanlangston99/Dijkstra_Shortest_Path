#pragma once
#ifndef HEAP_H_
#define HEAP_H_


typedef struct TAG_ELEMENT{
	float key;
	int pos;
	int vertex;
}ELEMENT;

typedef ELEMENT* pELEMENT;


typedef struct TAG_HEAP{
	int capacity; /* max size of the heap */
	int size; /* current size of the heap */
	pELEMENT* H; /* pointer to pointers to elements */

}HEAP;

	HEAP* initialize(int n);
	void printHeap(HEAP* heap);
	int parent(int i);
	int left(int i);
	int right(int i);
	void minHeapify(HEAP* heap, int i);
	void buildHeap(HEAP* heap,int *f);
	pELEMENT extractMin(HEAP* heap,int* flag);
	int decreaseKey(HEAP* heap, int *i, int *val, int flag);
	int insert(HEAP* heap, ELEMENT* element);
	void swap(HEAP* heap,int index1, int index2);


#endif /* HEAP_H_ */
