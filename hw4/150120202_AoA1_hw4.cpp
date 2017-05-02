
#include "Heap.h"

/**
	Istanbul Technical University
	ISE315, Analysis of Algorithms, Fall 2015
	Homework 4

	Ahmet Furkan TEKE
	150120202

*/

#include <time.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>

#define BIDS_SIZE 100000
#define FILE_NAME "bids.txt"
#define INCREMENT_RATE 0.25

void setBids(int* array){
	string line;
    ifstream inFile (FILE_NAME);
    int n;
    int counter = 0;
    if (inFile.is_open()){
    	while (counter < BIDS_SIZE){
    		getline(inFile, line,'\n');
            istringstream ss(line);
            ss >> n;
            array[counter++] = n;
        }
    }
   	inFile.close();
}

void simulation(int* bids, float p, int m){
	Heap bidsHeap;
	int c = 0;
	int bidc = 1;
	int max;
	int r;

	if (m < 100){
		cout << "Total bids can not be under 100" << endl;
		return;
	}
	for (int i = 0; i < 100; i++)
		bidsHeap.insert(bids[c++]);

	bidsHeap.buildHeap();
	while(c <= m){
		if(bidsHeap.getSize() == 100){
			int max = bidsHeap.extractMax();
			printf("%3d. Auction Wonner: %d\n", bidc++, max);
			c++;
		}
		else{
			bidsHeap.insert(bids[c++]);
			for (int i = 1; i < 100; i++){
				r = rand()%101; // 0
				int bid = bidsHeap.getKey(i);
				if (r < p * 100){
					bidsHeap.increaseKey(i, bid+=bid*INCREMENT_RATE);
					c++;
				}
				else
					bidsHeap.increaseKey(i, bids[c++]);
			}
		}
	}
}
int main(int argc, char* argv[]){

	float p = atof(argv[1]);
	int m 	= atoi(argv[2]);

	int bids[BIDS_SIZE];
	setBids(bids);

	clock_t t = clock();
	simulation(bids, p, m);
	t = clock() - t;
	printf ("It took me %f miliseconds.\n",((float)t)/CLOCKS_PER_SEC*1000);
    return 0;
}