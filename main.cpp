// Written by Sam Coday and Ben Wise for SMU Data Structures (CSE2341)

#include <iostream>
#include <chrono>
#include <ctime>
#include "SortingCompetition.h"
using namespace std;

int main()
{
    chrono::time_point<chrono::system_clock> start, end;
    SortingCompetition* sort = new SortingCompetition("allfiles.txt");
    chrono::duration<double> elapsed_seconds;
    cout<<"Preparing Data..."<<endl;
    sort->readData();
    sort->prepareData();
    cout<< "Sorting:\n";
    for(int i=0; i<100; i++){
    start=chrono::system_clock::now();
    sort->sortData();
    end=chrono::system_clock::now();
    sort->outputData("output1.txt");
    elapsed_seconds+= end-start;
    }

    cout<<"Elapsed time Threaded: " << elapsed_seconds.count()/100 << " s\n";
    return 0;
}

