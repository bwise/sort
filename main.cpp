// Written by Sam Coday and Ben Wise for SMU Data Structures (CSE2341)

#include <iostream>
#include <chrono>
#include <ctime>
#include "SortingCompetition.h"
//#include "testmulti.h"
using namespace std;

int main()
{
    chrono::time_point<chrono::system_clock> start, end;

    SortingCompetition* sort = new SortingCompetition("modestproposal.txt");
    chrono::duration<double> elapsed_seconds;
    cout<<"Preparing Data..."<<endl;
    sort->readData();
    sort->prepareData();
    /*
//EMPTY BEFORE FILE STAGE
    cout<< "Sorting:\n";
    //for(int i=0; i<50; i++){
    //testMulti* tm = new testMulti();


    start=chrono::system_clock::now();

        sort->sortDataThread();
        end=chrono::system_clock::now();

        sort->outputDataThread("outfile1.txt");

        elapsed_seconds = end-start;
        //time_t end_time = chrono::system_clock::to_time_t(end);

        //cout << "Finished at " << ctime(&end_time) <<
                //cout<<"Elapsed time Threaded: " << elapsed_seconds.count() << " s\n";
//}
      cout<<"Elapsed time Threaded: " << elapsed_seconds.count() << " s\n";
    SortingCompetition* sort2 = new SortingCompetition("allfiles.txt");
    cout<<"Preparing Data..."<<endl;
    sort2->readData();
    sort2->prepareData();
//EMPTY BEFORE FILE STAGE

*/
    cout<< "Sorting:\n";


    chrono::time_point<chrono::system_clock> start1, end1;
   chrono::duration<double> elapsed_seconds1;
  //for(int i=0; i<50; i++){
    //testMulti* tm = new testMulti();
    start1=chrono::system_clock::now();

        sort->sortData();
        end1=chrono::system_clock::now();

        sort->outputData("outfile.txt");

        elapsed_seconds1 = end1-start1;
        //time_t end_time = chrono::system_clock::to_time_t(end);

        //cout << "Finished at " << ctime(&end_time) <<
                //cout<<"Elapsed time Threaded: " << elapsed_seconds.count() << " s\n";
//}
    cout<<"Elapsed time: " << elapsed_seconds1.count() << " s\n";

    return 0;
}

