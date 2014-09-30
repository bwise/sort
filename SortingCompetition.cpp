#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>

#include "SortingCompetition.h"

using namespace std;

SortingCompetition::SortingCompetition(const string &inputFileName)
{
    fileName = inputFileName;
    allWordsCapacity=0;
    allWordsSize=0;
}

void SortingCompetition::setFileName(const string &inputFileName){
    fileName = inputFileName;
}

bool SortingCompetition::readData(){
    ifstream fin(fileName, ios::in);
    char buffer [8100] ={};
    while(!fin.eof()){
        fin>>buffer;

        if(allWordsSize>=allWordsCapacity)
            resize();
        allWords[allWordsSize] = new char [strlen(buffer)];
        strcpy(allWords[allWordsSize],buffer);
        allWordsSize++;
    }
    fin.close();
    return true;
}

void SortingCompetition::resize(){
    char** temp = new char*[allWordsCapacity+10];
    for(int i=0; i<allWordsCapacity; i++)
        temp[i] = allWords[i];
    delete [] allWords;
    allWords=temp;
    allWordsCapacity+=10;
}

bool SortingCompetition::prepareData(){
    return true;
}

void SortingCompetition::sortData(){

}

void SortingCompetition::outputData(const string &outputFileName){
    ofstream fout(outputFileName, ios::out);
    for(int i=0; i< allWordsSize; i++){
        fout<<allWords[i];
    }
}

SortingCompetition::~SortingCompetition(){
     delete[] allWords;
     delete allWords;
}
