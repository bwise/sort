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
    char** wordsSorted;
    unsigned long int* lengthOfWords;
    unsigned long int* lengthToSort;
    unsigned long allWordsCapacity, allWordsSize;
    bool lessThan(unsigned long int&,unsigned long int&);

    bool lessThanOrEqual(long unsigned int&, long unsigned int&);
    void swap(unsigned long int &, unsigned long int);
    void insertionSort(unsigned long int);
    void quickSort(unsigned long int, unsigned long int);
    void quickSortThread(unsigned long int , unsigned long int );
    bool insertionSort(unsigned long int &, unsigned long int &);
    void introSort(unsigned long int, unsigned long int,unsigned long int);
    void mergeSort();
    void merge();
    void sortDataThread();
    void introSort(unsigned long int,unsigned long int);


public:
    SortingCompetition(const std::string& inputFileName);
    void setFileName(const std::string& inputFileName);
    bool readData();
    bool prepareData();
    void sortData();
    void sortData(unsigned long int);

    void outputDataThread(const std::string& outputFileName);
    void outputData(const std::string& outputFileName);
    void resize();
    ~SortingCompetition();
};

#endif // SORTINGCOMPETITION_H
