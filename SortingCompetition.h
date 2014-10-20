// Written by Sam Coday and Ben Wise for SMU Data Structures (CSE2341)
#ifndef SORTINGCOMPETITION_H
#define SORTINGCOMPETITION_H

#include <string>

class SortingCompetition
{
private:
    std::string fileName;
    char** allWords;
    char** wordsToSort;
    char** temp;
    unsigned long allWordsCapacity, allWordsSize;
    void resize();
    bool lessThan(long unsigned int&, long unsigned int&);
    void swap(long unsigned int &, unsigned long int );
    bool insertionSort(long unsigned int &,long unsigned int &);
    void merge(long unsigned int);
    void quickSort(unsigned long int, unsigned long int);

public:
    SortingCompetition(const std::string& inputFileName);
    void setFileName(const std::string& inputFileName);
    bool readData();
    bool prepareData();
    void sortData();
    void sortData1();
    void outputData(const std::string& outputFileName);
    ~SortingCompetition();
};

#endif // SORTINGCOMPETITION_H
