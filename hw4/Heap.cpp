#include "Heap.h"
#include <stddef.h>


using namespace std;

Heap::Heap(int* array, int size){
    heap_size = 0;
    for (int i = 1; i <= size; i++){
        maxHeap[i] = array[i-1];
        heap_size++;
    }
}
Heap::Heap(){
    heap_size = 0;
}

int Heap::getSize(){
    return heap_size;
}

void Heap::heapify(int i) {
    int l = 2*i;
    int r = 2*i + 1;
    int largest = i;

    if ((l <= heap_size) && (maxHeap[l] > maxHeap[i]))
        largest = l;
    else 
        largest = i;
    
    if ((r <= heap_size) && (maxHeap[r] > maxHeap[largest]))
        largest = r;
    

    if (largest != i) {
        swap(maxHeap[i], maxHeap[largest]);
        heapify(largest);
    }
}

void Heap::buildHeap() {
    int n = heap_size;
    for (int i = floor(n / 2); i >= 1; i--)
        heapify(i);
}

int Heap::extractMax(){
    if (heap_size < 1){
        cout << "Heap underflow" << endl;
        exit(0);
    }
    int max = maxHeap[1];
    maxHeap[1] = maxHeap[heap_size];
    heap_size--;
    heapify(1);
    return max;
}
void Heap::print(){
    for(int i = 1; i <= heap_size; i++)
        cout << maxHeap[i] << endl;
    cout << "------------" << endl;
}
int Heap::getKey(int i){
    return maxHeap[i];
}

void Heap::increaseKey(int i, int key){
    maxHeap[i] = key;
    while ((i > key) && maxHeap[i/2] < maxHeap[i]){
        swap(maxHeap[i], maxHeap[i/2]);
        i /= 2;
    }
}

void Heap::insert(int key){
    heap_size++;
    maxHeap[heap_size] = 0;
    increaseKey(heap_size, key);
}