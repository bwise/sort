// Written by Sam Coday and Ben Wise for SMU Data Structures (CSE2341)

#include <iostream>
#include <chrono>
#include <ctime>
#include "SortingCompetition.h"
using namespace std;

int main()
{
    //Initialize Timing Vars
    chrono::time_point<chrono::system_clock> start, end;
    //Read in Data
    SortingCompetition* sort = new SortingCompetition("allfiles.txt");
    //More Timing Vars
    chrono::duration<double> elapsed_seconds;
    //Read In and Prep Data
    cout<<"Preparing Data..."<<endl;
    sort->readData();
    sort->prepareData();
    //Sort
    cout<< "Sorting:\n";
    for(int i=0; i<1; i++){
    start=chrono::system_clock::now();
    sort->sortData();
    end=chrono::system_clock::now();
    sort->outputData("output1.txt");
    elapsed_seconds+= end-start;
    }

    //Display results
    cout<<"Elapsed time: " << elapsed_seconds.count()/1<< " s\n";
    return 0;
}

