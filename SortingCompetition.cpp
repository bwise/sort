// Written by Sam Coday and Ben Wise for SMU Data Structures (CSE2341)

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

void SortingCompetition::quickSort(int left, int right){
    if(right-left<6){
        insertionSort(left,right);
        return;
    }
    int center = (left+right)/2;
    if(lessThan(center,left)){
        swap(left,center);
    }
    if(lessThan(right,left)){
        swap(left,right);
    }
    if(lessThan(right,center)){
        swap(right,center);
    }
    swap(center, right-1);
    long unsigned int pivot = right-1;
    int i=left,j=right-1;
    while(true){
        while(lessThan(++i,pivot)){
            ;
        }
        while(lessThan(pivot,--j)){
            ;
        }
        if(i<j)
            swap(i,j);
        else
            break;
    }
    swap(i,right-1);
    quickSort(left,i-1);
    quickSort(i+1,right);
}


void SortingCompetition::sortData(){
    introSort(0, allWordsSize-1,19); //1280
    //quickSort(0, allWordsSize-1);
    //insertionSort(0, allWordsSize);
}

void SortingCompetition::sortData(int compare){
    introSort(0,allWordsSize-1, compare);
}


void SortingCompetition::outputData(const string &outputFileName){
    ofstream fout(outputFileName, ios::out);
    for(unsigned int i=0; i< allWordsSize-1; i++){
        fout<<wordsToSort[i]<<"\n";
    }
    fout.close();
}

bool SortingCompetition::lessThan(unsigned long int index1, unsigned long int index2){
    if(index1==index2||index1>allWordsSize-1||index2>allWordsSize-1)
        return false;
    if(lengthToSort[index1]<lengthToSort[index2])
        return true;
    else{
        if(lengthToSort[index1]==lengthToSort[index2]){
            if(strcmp(wordsToSort[index1],wordsToSort[index2])<0)
                return true;
            else
                return false;
        }
        else
            return false;
    }
}

void SortingCompetition::swap( unsigned long int index1, unsigned long int index2){
    if(index1==index2||index1>=allWordsSize-1||index2>=allWordsSize-1)
        return;
    //cout <<"s";
    //cout << wordsToSort[index1]<<wordsToSort[index2];

    char * tempPtr=wordsToSort[index1];
    wordsToSort[index1]=wordsToSort[index2];
    wordsToSort[index2]=tempPtr;

    int tempInt = lengthToSort[index1];
    lengthToSort[index1]=lengthToSort[index2];
    lengthToSort[index2]=tempInt;

}

bool SortingCompetition::insertionSort(unsigned long int left, unsigned long int right){
unsigned long int currentmax;
    for(unsigned long int j=left; j<=right; j++){
        currentmax=j;
        for(unsigned long int i=j+1; i<=right; i++){
            if(lessThan(currentmax,i))
                currentmax=i;
        }
        swap(currentmax,j);
    }
    return true;
}

SortingCompetition::~SortingCompetition(){
    delete[] allWords;
    delete lengthOfWords;
    delete lengthToSort;
    delete[] wordsToSort;
    delete wordsToSort;
    delete allWords;
}

void SortingCompetition::introSort(unsigned long int left, unsigned long int right, unsigned long int switchsize){

    if(right-left<6){
        insertionSort(left,right);
        return;
    }
    int center = (left+right)/2;
    if(lessThan(center,left)){
        swap(left,center);
    }
    if(lessThan(right,left)){
        swap(left,right);
    }
    if(lessThan(right,center)){
        swap(right,center);
    }
    swap(center, right-1);
    long unsigned int pivot = right-1;
    int i=left,j=right-1;
    while(true){
        while(lessThan(++i,pivot)){
            ;
        }
        while(lessThan(pivot,--j)){
            ;
        }
        if(i<j)
            swap(i,j);
        else
            break;
    }
    swap(i,right-1);


    if(right-left<=switchsize){
        insertionSort(left,i-1);
        insertionSort(i+1,right);
    }
    else{
        introSort(left,i-1, switchsize);
        introSort(i+1,right, switchsize);
    }
    //cout <<"r";
    return;
}
