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
    allWordsCapacity=10;
    allWordsSize=0;
    allWords = new char* [allWordsCapacity];
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
    wordsToSort = new char* [allWordsSize];
    for(int i =0; i< allWordsSize-1; i++){
        wordsToSort[i] = new char [strlen(allWords[i])];
        strcpy(wordsToSort[i], allWords[i]);
    }
    return true;
}

void SortingCompetition::sortData(){

}

void SortingCompetition::outputData(const string &outputFileName){
    ofstream fout(outputFileName, ios::out);
    for(int i=0; i< allWordsSize-1; i++){
        fout<<wordsToSort[i];
    }
}

SortingCompetition::~SortingCompetition(){
     delete[] allWords;
     delete allWords;
}
