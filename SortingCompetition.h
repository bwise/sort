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
    int* lengthOfWords;
    int* lengthToSort;
    unsigned long allWordsCapacity, allWordsSize;
    bool lessThan(unsigned long int, unsigned long int);
    void swap(unsigned long int, unsigned long int);
    void insertionSort(unsigned long int);
    void quickSort(int, int);
    void quickSortThread(int, int);
    bool insertionSort(unsigned long, unsigned long);
    void introSort(unsigned long int, unsigned long int,unsigned long int);

public:
    SortingCompetition(const std::string& inputFileName);
    void setFileName(const std::string& inputFileName);
    bool readData();
    bool prepareData();
    void sortData();
    void sortDataThread();
    void sortData(int);
    void outputData(const std::string& outputFileName);
    void resize();
    ~SortingCompetition();
};

#endif // SORTINGCOMPETITION_H
