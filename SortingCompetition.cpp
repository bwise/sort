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

bool SortingCompetition::quickSort(int bottom, int top){
    int pivot, i,j;
    if(bottom<top){
        if(lessThan(top,bottom)&&lessThan(top/2,top))
            pivot = top;
        else if(lessThan(bottom,top)&&lessThan(top/2, bottom))
            pivot =bottom;
        else
            pivot = top/2;
        i = top-1;
        j=bottom+1;

        while(j<i){
            while(lessThan(i,pivot)&&i>0){
                i--;
            }
            while(lessThan(pivot,j)&&j<top){
                j++;
            }

        }

        swap(i,j);
        quickSort(pivot+1,top);
        quickSort(bottom,pivot);
    }
    return true;

}

void SortingCompetition::sortData(){
    //quickSort(0, allWordsSize-1);
    insertionSort();
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

bool SortingCompetition::lessThan(unsigned long int index1, unsigned long int index2){
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
    //cout << wordsToSort[index1]<<wordsToSort[index2];

    char * tempPtr=wordsToSort[index1];
    wordsToSort[index1]=wordsToSort[index2];
    wordsToSort[index2]=tempPtr;

    int tempInt = lengthToSort[index1];
    lengthToSort[index1]=lengthToSort[index2];
    lengthToSort[index1]=tempInt;

    //cout << wordsToSort[index1]<<wordsToSort[index2] << "\n";

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
