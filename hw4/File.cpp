#include "File.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

File::File(string filename){
	this->filename = filename;
	setVector();
}

void File::setVector(){
	string line;
    ifstream inFile (filename.c_str());
    int n;
    if (inFile.is_open()){
    	while (getline(inFile, line,'\n')){
            istringstream ss(line);
            ss >> n;
            this->nums.push_back(n);
        }
    }
   	inFile.close();
}

vector<int> File::getVector(){
	return this->nums;
}

int File::getSize(){
	return this->nums.size();
}

void File::print(){
	for (vector<int>::const_iterator i = this->nums.begin(); i != this->nums.end(); ++i)
    	cout << *i << endl;
}