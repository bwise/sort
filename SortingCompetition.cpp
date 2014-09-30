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
    allWordsCapacity=100000;
    allWordsSize=0;
    allWords = new char* [allWordsCapacity];
    lengthOfWords = new int[allWordsCapacity];
}

void SortingCompetition::setFileName(const string &inputFileName){
    fileName = inputFileName;
}

bool SortingCompetition::readData(){
    ifstream fin(fileName, ios::in);
    if(!fin){
        cout<<"cant open";
    }
    char buffer [8100] ={};
    while(!fin.eof()){
        fin>>buffer;
        if(allWordsSize>=allWordsCapacity)
            resize();
        allWords[allWordsSize] = new char [strlen(buffer)+1];
        strcpy(allWords[allWordsSize],buffer);
        lengthOfWords[allWordsSize] = strlen(buffer);
        allWordsSize++;
    }
    fin.close();
    return true;
}

void SortingCompetition::resize(){
    char** temp = new char*[allWordsCapacity+100000];
    int* tempLen = new int[allWordsCapacity+100000];
    for(unsigned int i=0; i<allWordsCapacity; i++){
        temp[i] = allWords[i];
        tempLen[i] = lengthOfWords[i];
    }
    delete [] allWords;
    allWords=temp;
    delete [] lengthOfWords;
    lengthOfWords=tempLen;
    allWordsCapacity+=100000;
}

bool SortingCompetition::prepareData(){
    wordsToSort = new char* [allWordsSize];
    for(unsigned int i =0; i< allWordsSize-1; i++){
        wordsToSort[i] = new char [strlen(allWords[i])+1];
        strcpy(wordsToSort[i], allWords[i]);
    }
    lengthToSort = new int[allWordsSize];
    for(unsigned int i =0; i< allWordsSize-1; i++){
        lengthToSort[i] = lengthOfWords[i];
    }
    return true;
}

void SortingCompetition::quickSort(){

}

void SortingCompetition::sortData(){

}


void SortingCompetition::outputData(const string &outputFileName){
    ofstream fout(outputFileName, ios::out);
    for(unsigned int i=0; i< allWordsSize-1; i++){
        fout<<wordsToSort[i]<<"\n";
    }
    fout.close();
}

SortingCompetition::~SortingCompetition(){
     delete[] allWords;
     delete allWords;
}
