#include <iostream>
#include <string>
#include <sys/types.h>   
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>   
#include <fstream>
#include <vector>
#include <dirent.h>
#include <sstream>
#include <thread>

using namespace std;

vector<string> getFileNames(const char* p){
    vector<string> fNames;
    DIR *dpdf;
    struct dirent *epdf;
    string str(".txt");
    dpdf = opendir(p); 
    if (dpdf != NULL){
       while (epdf = readdir(dpdf)){
            string fName = epdf->d_name;
            if(fName.find(str) != string::npos){ // if ".txt" in file name
                fNames.push_back(fName);
            }
       }
    }
    return fNames;
}
void threadFunction(string inputfile, int index){
   
    string line;
    ifstream inFile (inputfile.c_str());
    int maximum = 0;
    int median = 0;
    int minimum = 100;
    int counter = 0;
    
    int num;
    vector<int> v;
    ifstream infile(inputfile.c_str());{
        if (inFile.is_open()){
            while (getline(inFile, line,'\n')){
                istringstream ss(line);
                for(int i = 0; i < index; i++){
                    ss >> num;
                }
                if(num < minimum){
                    minimum = num;   
                }
                else if(num > maximum){
                    maximum = num;
                }
                v.push_back(num);
                counter++;
            }   
        }   
        
    }
    median = v.at(counter/2);
    cout << "Thread: " << inputfile << " Min: " << minimum << " Max: " << maximum << " Med: " << median << endl;
    inFile.close();

}

void makeThreads(vector<string> files, int index){
    vector<thread> threads;
     for(vector<string>::iterator it = files.begin(); it != files.end(); ++it) {
        string inputfile = *it;
        thread t(&threadFunction,inputfile, index);
        t.join();
     }
}

int main(int argc , char** argv ){
    const char* path = argv[1];
    vector<string> fileNames;
    cout << "Master: Start" << endl;
    cout << "Master: Passed input folder path to main: " << path << endl;
    fileNames = getFileNames(path);
    pid_t s1 = fork();
    if (s1 == 0){
        int status;
        cout << "Slave 1: Project Statistics" << endl;
        makeThreads(fileNames, 1);
    }
    else{
        int status1;
        waitpid(s1, &status1, 0); 

        pid_t s2 = fork();
        if (s2 == 0){
            cout << "Slave 2: Midterm Statistics" << endl;
            makeThreads(fileNames, 2);
        }
        else{
            int status2;
            waitpid(s2, &status2, 0); 

            pid_t s3 = fork();
            if(s3 == 0){
                cout << "Slave 3: Final Statistics" << endl;
                makeThreads(fileNames, 3);
            }
            else{   
                int status3;
                waitpid(s3, &status3, 0);
                cout << "Master: Finish" << endl;
            }
        }
    }
    return 0;
}