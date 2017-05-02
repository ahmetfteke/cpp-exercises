#include <iostream>
#include <string>
#include <stdlib.h>   
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <time.h>

/**
    ISE 315 Analysis of Algorithms
    Fall 2015 - Homework 3
    Ahmet Furkan TEKE
    150120202
*/
    
using namespace std;

void setArray(int* array, int size){
   
    string line;
    string inputfile = "data.txt";
    ifstream inFile (inputfile.c_str());

    int num;
    int counter = 0;
    ifstream infile(inputfile.c_str());
    if (inFile.is_open()){
        while (getline(inFile, line,'\n') && counter < size){
            istringstream ss(line);
            ss >> num;
            array[counter++] = num;
        }
    }
}

void saveArray(int* array, int size){
    int counter = 0;
    ofstream out ("sorted.txt"); 
    if (out.is_open()){
        while(counter < size){
            out << array[counter++] << endl;
        }
    }
}

int partition(int* array, int p, int q){
    int x = array[p];
    int i = p;
    int j;
    for(j=p+1; j<q; j++){
        if(array[j]<=x){
            i=i+1;
            swap(array[i],array[j]);
        }
    }
    swap(array[i],array[p]);
    return i;
}

void quickSort(int* array, int p, int r){
    int q;
    if(p < r){
        q = partition(array, p, r);
        quickSort(array, p, q);  
        quickSort(array, q+1, r);
    }
}


int main(int argc , char** argv ){
    int size = atoi(argv[1]);
    int array[size];
    setArray(array, size);

    clock_t t = clock();
    quickSort(array, 0, size);
    t = clock() - t;
    cout << "It took me " << (float)t/CLOCKS_PER_SEC << " seconds."<< endl;
    saveArray(array, size);
}