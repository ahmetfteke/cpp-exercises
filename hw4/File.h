#ifndef FILE_H
#define FILE_H

#include <string>
#include <vector>

using namespace std;

class File{
private:
	string filename;
	vector<int> nums;
public:
	File(string filename);
	void setVector();
	vector<int> getVector();
	int getSize();
	void print();
};
#endif