#ifndef SORTINGCOMPETITION_H
#define SORTINGCOMPETITION_H

class SortingCompetition
{
public:
    SortingCompetition(const string& inputFileName);
    void setFileName(const string& inputFileName);
    bool readData();
    bool prepareData();
    void sortData();
    void outputData(const string& outputFileName);
};

#endif // SORTINGCOMPETITION_H
