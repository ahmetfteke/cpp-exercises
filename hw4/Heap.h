#ifndef HEAP_H
#define HEAP_H

using namespace std;

#include <algorithm>    
#include <iostream>
#include <cmath>

class Heap{
private:
	int heap_size;
    int maxHeap[1000];
public:

	Heap();
	Heap(int* array, int size);

	int getSize();
	void heapify(int i);
	void buildHeap();
	void print();
	int extractMax();
	int getKey(int i);
	void increaseKey(int i, int key);
	void insert(int key);
};

#endif