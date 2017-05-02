/**
	ISE 315 Analysis of Algorithms
	Fall 2015 - Homework 5
	Ahmet Furkan TEKE - 150120202
*/


#include<iostream>
#include"RBTree.h"
#include"RBTree.cpp"

#include <fstream>
#include <sstream>

#define FILE_NAME "data.txt"

using namespace std;
int lineCounter(){
	int counter = 0;
	ifstream in(FILE_NAME);
	string unused;
	while (getline(in, unused) )
   		++counter;
   	return counter;
}
void setData(int* array){
	string line;
    ifstream inFile (FILE_NAME);
    int counter = 0;
    int n;
    if (inFile.is_open()){
    	while (getline(inFile, line,'\n')){
            istringstream ss(line);
            ss >> n;
            array[counter++] = n;
        }
    }
   	inFile.close();
}

int main(void){
    int c = lineCounter();
    int data[c];
    setData(data);
	ptr tree = NULL;
    for(int i=0; i<c; i++){
		tree = insert(tree, data[i]);
		check(tree); // check if tree is valid or not
	}
	display(tree);
	return 0;
}
