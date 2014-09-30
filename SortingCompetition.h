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
    bool lessThan(unsigned long int, unsigned long int, char**,int*);
    void swap(unsigned long int, unsigned long int);
    bool insertionSort();

public:
    SortingCompetition(const std::string& inputFileName);
    void setFileName(const std::string& inputFileName);
    bool readData();
    bool prepareData();
    bool quickSort(int,int);
    void sortData();
    void outputData(const std::string& outputFileName);
    void resize();
    ~SortingCompetition();
};

#endif // SORTINGCOMPETITION_H
