// Written by Sam Coday and Ben Wise for SMU Data Structures (CSE2341)

#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <omp.h>
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

void SortingCompetition::quickSort(long unsigned int left, long unsigned int right){
    if((right-left)<5){
        insertionSort(left,right);
        return;
    }
    long unsigned int center = (left+right)/2;
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
    long unsigned int i=left,j=right-1;
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
    quickSort(i,right);
}


void SortingCompetition::sortData(){
    quickSort(0,allWordsSize-1);
}

void SortingCompetition::sortDataThread(){
int NUM_THREADS =4;

#pragma omp parallel for
        for(int i=0; i<NUM_THREADS; i++)
        {
            quickSort(((i*allWordsSize)/NUM_THREADS), (((allWordsSize*(i+1))/NUM_THREADS))-1);
        }

    temp = new char*[allWordsSize];
    merge(NUM_THREADS);

}

void SortingCompetition::merge(long unsigned int n){
    if(n<=1)
        return;
    long unsigned int a=0,b=0;
#pragma omp parallel
  {
#pragma omp for nowait
    for(int k=0; k<n; k+=2)
    {
        a= (allWordsSize*(k))/n;
        b= (allWordsSize*(k+1))/n;
        int tempPos=a;
        while(a<(allWordsSize*(k+1))/n&& b<(((k+2)*allWordsSize)/n)){
            if(lessThan(a,b))
                temp[tempPos++]=wordsToSort[a++];
            else
                temp[tempPos++]= wordsToSort[b++];
        }
        while(a<(allWordsSize*(k+1))/n)
            temp[tempPos++]=wordsToSort[a++];
        while(b<(allWordsSize*(k+2))/n)
            temp[tempPos++]=wordsToSort[b++];
    }
}
    for(unsigned int i =0; i<allWordsSize; i++){
        wordsToSort[i]=temp[i];
    }
    merge(n/2);
}

/*void SortingCompetition::mergeSort(){
    long unsigned int a= 0, bi= (allWordsSize/4), ci =((allWordsSize*2)/4), di= ((3*allWordsSize)/4);
    long unsigned int b=bi,c=ci,d=di;
    wordsSorted = new char* [allWordsSize];
    int count=0;
    cout<<allWordsSize<<endl;

    for(int i=0; i<allWordsSize; i++)
    {
        if(lessThanOrEqual(a,b)&&lessThanOrEqual(a,c)&&lessThanOrEqual(a,d)){
            wordsSorted[i] = new char [strlen(wordsToSort[a])+1];
            strcpy(wordsSorted[i], wordsToSort[a]);
            count++;
            a++;
            if(a>=bi){
                //memset(wordsToSort[a],0,strlen(wordsToSort[a]));
              wordsToSort[a]=NULL;
            }

        }
        else if(lessThanOrEqual(b,a)&&lessThanOrEqual(b,c)&&lessThanOrEqual(b,d)){
            wordsSorted[i] = new char [strlen(wordsToSort[b])+1];
            strcpy(wordsSorted[i], wordsToSort[b]);
            count++;
              b++;
            if(b>=ci){
                //memset(wordsToSort[b],0,strlen(wordsToSort[b]));
                wordsToSort[b]=NULL;
            }

        }
        else if(lessThanOrEqual(c,b)&&lessThanOrEqual(c,a)&&lessThanOrEqual(c,d)){
            wordsSorted[i] = new char [strlen(wordsToSort[c])+1];
            strcpy(wordsSorted[i], wordsToSort[c]);
            count++;
            if(c>=di){
               // memset(wordsToSort[c],0,strlen(wordsToSort[c]));
                wordsToSort[c]=NULL;
            }
            c++;

        }
        else if(lessThanOrEqual(d,b)&&lessThanOrEqual(d,c)&&lessThanOrEqual(d,a)){
            wordsSorted[i] = new char [strlen(wordsToSort[d])+1];
            strcpy(wordsSorted[i], wordsToSort[d]);
            count++;
            d++;
            if(d>=allWordsSize){
                cout<<"beofre"<<d<<wordsToSort[d]<<endl;
                //memset(wordsToSort[d],0,strlen(wordsToSort[d]));
                wordsToSort[d]=NULL;
                cout<<"after"<<endl;

            }


        }
    }
}

void SortingCompetition::sortData(int compare){
    //introSort(0,allWordsSize, compare);
}
*/

void SortingCompetition::outputData(const string &outputFileName){
    ofstream fout(outputFileName, ios::out);
    for(unsigned int i=0; i< allWordsSize-1; i++){
        fout<<wordsToSort[i]<<"\n";
    }
    fout.close();
}

void SortingCompetition::outputDataThread(const string &outputFileName){
    ofstream fout(outputFileName, ios::out);
    for(unsigned int i=0; i< allWordsSize-1; i++){
        fout<<wordsToSort[i]<<"\n";
    }
    fout.close();
}

bool SortingCompetition::lessThan(unsigned long &index1, unsigned long &index2){
    if(wordsToSort[index1]==NULL)
        return false;
    if(wordsToSort[index2]==NULL||strlen(wordsToSort[index1])<strlen(wordsToSort[index2]))
        return true;
    else{
        if(strlen(wordsToSort[index1])==strlen(wordsToSort[index2])){
            if(strcmp(wordsToSort[index1],wordsToSort[index2])<0)
                return true;
            else
                return false;
        }
        else
            return false;
    }
}

bool SortingCompetition::lessThanOrEqual(unsigned long int& index1, unsigned long int& index2){
    /*if(index1==index2||index1>allWordsSize-1||index2>allWordsSize-1||(wordsToSort[index1]==NULL&&wordsToSort[index2]!=NULL){
        cout<<"what is going on"<<endl;
        return false;
    }*/
    if(wordsToSort[index2]==NULL){
        return true;
    }
    if(wordsToSort[index1]==NULL){
        return false;
    }
    if(strlen(wordsToSort[index1])<strlen(wordsToSort[index2])){
        return true;
}
    //cout<<index1<<"\t"<<index2<<endl;
    //cout<<wordsToSort[index1]<<strlen(wordsToSort[index1])<<"\t"<<wordsToSort[index2]<<strlen(wordsToSort[index2])<<endl;
    if(strlen(wordsToSort[index1])==strlen(wordsToSort[index2])){
        if(strcmp(wordsToSort[index1],wordsToSort[index2])<=0)
            return true;
        else
            return false;
    }
    else
        return false;
}

void SortingCompetition::swap(unsigned long &index1, unsigned long index2){
    if(index1==index2||index1>=allWordsSize-1||index2>=allWordsSize-1)
        return;
    char * tempPtr=wordsToSort[index1];
    wordsToSort[index1]=wordsToSort[index2];
    wordsToSort[index2]=tempPtr;

}

bool SortingCompetition::insertionSort(long unsigned int& left,long unsigned int& right){
    long unsigned int temp,initLeft= left;
    for(;left<=right; left++){
        for(long unsigned int j=left; j>initLeft; j--){
            temp = j-1;
            if(lessThan(j,temp))
                swap(temp,j);
        }
    }
    /*long unsigned int currentmax;
    for(long unsigned int j=left; j<=right; j++){
        currentmax=j;
        for(long unsigned int i=j+1; i<=right; i++){
            if(lessThan(currentmax,i))
                currentmax=i;
        }
        swap(currentmax,j);
    }
   */ return true;
}

SortingCompetition::~SortingCompetition(){
    delete[] allWords;
    delete lengthOfWords;
    delete lengthToSort;
    delete[] wordsToSort;
    delete wordsToSort;
    delete allWords;
    delete [] wordsSorted;
    delete wordsSorted;
    delete [] temp;
    delete temp;
}

/*void SortingCompetition::introSort(unsigned long int left, unsigned long int right, unsigned long int switchsize){
    if(left>right-2)
        return;

    unsigned long int pivotIndex=left, tLeft=left+2, tRight=right-2, count=0;

    while(tLeft<=tRight)
    {
        if(lessThan(pivotIndex,tLeft)&&lessThan(tRight, pivotIndex)){
            //cout << wordsToSort[tLeft] <<wordsToSort[pivotIndex] << wordsToSort[tRight] << "\n";
            swap(tLeft,tRight);
            }
        if(lessThan(tLeft,pivotIndex)){
            count=tLeft;
            tLeft++;
        }
        if(lessThan(pivotIndex,tRight))
            tRight--;
    }

    swap(left,count);

    cout << "a";

    if(right-left<=switchsize){
        insertionSort(left,count-1);
        insertionSort(count+1,right);
    }
    else{
        introSort(left,count-1, switchsize);
        introSort(count+1,right, switchsize);
    }
    cout <<"r";
    return;
}*/
