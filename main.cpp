#include <iostream>
#include <chrono>
#include <ctime>
#include "SortingCompetition.h"

using namespace std;

int main()
{
    chrono::time_point<chrono::system_clock> start, end;

    SortingCompetition* sort = new SortingCompetition("warandpeace.txt");
    sort->readData();
    sort->prepareData();

    start=chrono::system_clock::now();
        sort->sortData();
    end=chrono::system_clock::now();

    sort->outputData("outfile1.txt");

    chrono::duration<double> elapsed_seconds = end-start;
    time_t end_time = chrono::system_clock::to_time_t(end);

    cout << "Finished at " << ctime(&end_time) << "Elapsed time: " << elapsed_seconds.count() << " s\n";

    return 0;
}

