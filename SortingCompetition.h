// Written by Sam Coday and Ben Wise for SMU Data Structures (CSE2341)
#ifndef SORTINGCOMPETITION_H
#define SORTINGCOMPETITION_H

#include <string>

class SortingCompetition
{
private:
    std::string fileName;
    char** allWords; //Keeps Words as Read In
    char** wordsToSort; //Copy to be sorted
    char** temp; //temp copy when needed
    int * wordLen; //holds word length
    unsigned long allWordsCapacity, allWordsSize; //hold size and capacity of arrays
    void resize(); //array resize
    bool lessThan(long unsigned int&, long unsigned int&); //custom comparator, does length then ascii compare
    void swap(long unsigned int &, unsigned long int ); //swaps elements in array
    bool insertionSort(long unsigned int &,long unsigned int &);//insertion sorts
    void merge(long unsigned int); //merge array chunks
    void merge(unsigned long left, unsigned long middle, unsigned long right); //merge array chunks
    void quickSort(unsigned long int, unsigned long int); //quick sort

public: //Required Public Interface Methods
    SortingCompetition(const std::string& inputFileName);
    void setFileName(const std::string& inputFileName);
    bool readData();
    bool prepareData();
    void sortData();
    void outputData(const std::string& outputFileName);
    ~SortingCompetition();
};

#endif // SORTINGCOMPETITION_H
