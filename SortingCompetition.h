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
    bool lessThan(unsigned long int,char*,int);
    bool lessThan(char*,unsigned long int,int);
    void swap(unsigned long int, unsigned long int);
    void insertionSort(unsigned long int);
    void quickSort(int,int);
    bool insertionSort();

public:
    SortingCompetition(const std::string& inputFileName);
    void setFileName(const std::string& inputFileName);
    bool readData();
    bool prepareData();
    void sortData();
    void outputData(const std::string& outputFileName);
    void resize();
    ~SortingCompetition();
};

#endif // SORTINGCOMPETITION_H
