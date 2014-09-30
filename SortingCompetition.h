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
    int allWordsCapacity, allWordsSize;
    bool lessThan(unsigned long int, unsigned long int);
    void swap(unsigned long int, unsigned long int);

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
