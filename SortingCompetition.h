#ifndef SORTINGCOMPETITION_H
#define SORTINGCOMPETITION_H

#include <string>

class SortingCompetition
{
private:
    std::string fileName;
    char** allWords;
    int allWordsCapacity, allWordsSize;

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
