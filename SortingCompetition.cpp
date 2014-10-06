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
    if(left>=right-1)
        return;
     int center = ((left+right)/2);
    if(lessThan(center,left)){
        swap(left,center);
    }
    if(lessThan(right,left)){
        swap(left,right);
    }
    if(lessThan(right,center)){
        swap(center,right);
    }
    swap(center, right-1);
    int size = strlen(wordsToSort[right-1])+1;
    char* pivot= new char[size];
    strcpy(pivot,wordsToSort[right-1]);
    int i=left,j=right-1;
    while(true){
        while(lessThan(++i,pivot,size-1)){
            cout<<size-1;

        }
        while(lessThan(pivot,--j,size-1)){
            ;
        }
        if(i>=j){
            break;

            //i++;
            //j--;
        }
        else
            swap(i,j);
    }
    swap(i,right-1);
    quickSort(left,i-1);
    quickSort(i+1,right);
}
void SortingCompetition::sortData(){
    quickSort(0, allWordsSize-1);
    //insertionSort();
}


void SortingCompetition::outputData(const string &outputFileName){
    ofstream fout(outputFileName, ios::out);
    for(unsigned int i=0; i< allWordsSize-1; i++){
        fout<<wordsToSort[i]<<"\n";
    }
    fout.close();
}

bool SortingCompetition::lessThan(unsigned long int index1, char* index2,int size){
    if(index1>allWordsSize-1||index1<0)
        return false;
    if(lengthToSort[index1]<size)
        return true;
    else{
        if(lengthToSort[index1]==size){
            if(strcmp(wordsToSort[index1],index2)<0)
                return true;
            else
                return false;
        }
        else
            return false;
    }
}

bool SortingCompetition::lessThan(char* index2,unsigned long int index1,int size){
    if(index1>allWordsSize-1||index1<0)
        return false;
    if(lengthToSort[index1]<size)
        return true;
    else{
        if(lengthToSort[index1]==size){
            if(strcmp(wordsToSort[index1],index2)<0)
                return true;
            else
                return false;
        }
        else
            return false;
    }
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
    //cout << wordsToSort[index1]<<wordsToSort[index2];

    char * tempPtr=wordsToSort[index1];
    wordsToSort[index1]=wordsToSort[index2];
    wordsToSort[index2]=tempPtr;

    int tempInt = lengthToSort[index1];
    lengthToSort[index1]=lengthToSort[index2];
    lengthToSort[index2]=tempInt;
    lengthToSort[index1]=tempInt;

}

bool SortingCompetition::insertionSort(){

    for(int j=allWordsSize; j>1; j--){

        unsigned long int currentmax=0;

        for(unsigned long int i=1; i<j; i++)
            if(lessThan(currentmax,i))
                currentmax=i;
        swap(currentmax,j-1);

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

