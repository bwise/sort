// Written by Sam Coday and Ben Wise for SMU Data Structures (CSE2341)

#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <omp.h>
#include <thread>
#include "SortingCompetition.h"

using namespace std;

//constructor-initializes file name, and allWords Array
SortingCompetition::SortingCompetition(const string &inputFileName)
{
    fileName = inputFileName;
    allWordsCapacity=100000;//sets intital array size to 100000
    allWordsSize=0;
    allWords = new char* [allWordsCapacity];
    wordLen = new int [allWordsCapacity];
}

//setter to change fileName
void SortingCompetition::setFileName(const string &inputFileName){
    fileName = inputFileName;
}

//reads in all of the words from the file
bool SortingCompetition::readData(){
    ifstream fin(fileName, ios::in);//opens file
    char buffer [8100] ={};
    while(!fin.eof()){//continues while not at end of file
        fin>>buffer;
        if(allWordsSize>=allWordsCapacity)
            resize();//resizes if capacity is too small
        allWords[allWordsSize] = new char [strlen(buffer)+1];
        strcpy(allWords[allWordsSize],buffer);
        allWordsSize++;
    }
    fin.close();//closes input file


    //make an array of wordsizes to avoid having to use strlen
    wordLen= new int[allWordsSize];

    for(int i=0; i<allWordsSize; i++)
        wordLen[i]=strlen(allWords[i]);

    return true;
}

//resizes allWords Array(increases by 100000 each call)
void SortingCompetition::resize(){
    char** temp = new char*[allWordsCapacity+100000];
    for( unsigned long int i=0; i<allWordsCapacity; i++){
        temp[i] = allWords[i];
    }
    delete [] allWords;//deletes old array
    allWords=temp;
    allWordsCapacity+=100000;//increases capacity(PBR)
}

//copies all data from readIn array to wordsToSort
bool SortingCompetition::prepareData(){
    wordsToSort = new char* [allWordsSize];
    for( unsigned long int i =0; i< allWordsSize-1; i++){
        wordsToSort[i] = new char [strlen(allWords[i])+1];
        strcpy(wordsToSort[i], allWords[i]);
    }
    return true;

}

//Quicksort that switches to insertion Sort AKA Introsort
void SortingCompetition::quickSort(long unsigned int left, long unsigned int right){
    if((right-left)<6){
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

    if(right-left<20){
        unsigned long int itemp=i-1;
        insertionSort(left, itemp);
        insertionSort(i, right);
    }else{

        quickSort(left,i-1);
        quickSort(i,right);
    }
}

void SortingCompetition::sortData(){

    //Non-Parallel Version, but it works
    quickSort(0,allWordsSize-1);

    /*//Parallel Version that doesn't quite work
    int NUM_THREADS =16, i;
    omp_set_num_threads(16);
#pragma omp parallel shared(NUM_THREADS) private(i)
{
#pragma omp for schedule(static)
        for(i=0; i<NUM_THREADS; i++){
            quickSort(((i*allWordsSize)/NUM_THREADS), (((allWordsSize*(i+1))/NUM_THREADS))-1);
        }
}
    //*
    temp = new char*[allWordsSize];

    unsigned long int pivots[100];
    unsigned long int itemp=0;
    pivots[0]=0;
    int cur=1;
    int max=1;


    for(unsigned long int i=0; i< allWordsSize; i++){
        itemp=i+1;
        if(lessThan(itemp,i)){
            cout<< itemp <<"\n";
            pivots[cur]=itemp;
            cur++;
            max++;
        }
    }

    pivots[max]=allWordsSize-1;


    for(cur=max-1; cur>0; cur--){
        cout << "Merge " << pivots[cur-1] <<" "<< pivots[cur] <<" "<<pivots[max]<<"\n";
        merge(pivots[cur-1],pivots[cur],pivots[max]);
    }

 /*
    unsigned long int m=0;
    unsigned long int r=0;


    for(unsigned long int i=0; i< allWordsSize; i++){
        itemp=i+1;
        if(lessThan(itemp,i)){
            m=itemp;
            break;
        }
    }

    for(unsigned long int i=r+1; i< allWordsSize-1; i++){
        itemp=i+1;
        if(lessThan(itemp,i)){
            cout << "Merge 0 " << m <<" "<<itemp<<"\n";
            merge(0,m,itemp);
            m=itemp;
        }
    }

    //merge(NUM_THREADS);

*/
}

void SortingCompetition::merge(unsigned long int left, unsigned long int middle,  unsigned long int right){

    char ** temparr = new char * [allWordsCapacity];

    unsigned long int a=left;
    unsigned long int b=middle;
    unsigned long int c=0;

    for(c=0; c<right-left; c++){
        if(a<middle && (b<right || lessThan(a,b))){
            temparr[c]=wordsToSort[a];
            a++;
        }else{
            temparr[c]=wordsToSort[b];
            b++;
        }
    }

    for(c=left; c<right; c++)
        cout << temp[c];
        wordsToSort[c]=temparr[c];
}

//Merge arrays
void SortingCompetition::merge(unsigned long n){
    if(n<=1)
        return;
    unsigned long int a=0,b=0, k, tempPos;

   // #pragma omp parallel for schedule(dynamic)
    for(k=0; k<n; k+=2)
    {
        a= (allWordsSize*(k))/n;
        b= (allWordsSize*(k+1))/n;
        tempPos=a;
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
    wordsToSort = temp;
    merge(n/2);
}


//Write Output to File
void SortingCompetition::outputData(const string &outputFileName){
    ofstream fout(outputFileName, ios::out);
    for( unsigned long int i=0; i< allWordsSize-1; i++){
        fout<<wordsToSort[i]<<"\n";
    }
    fout.close();
}

//Custom Less Than function that checks lenght before word comparison
bool SortingCompetition::lessThan(unsigned long &index1, unsigned long &index2){
    if(wordsToSort[index1]==NULL)
        return false;
    if(wordsToSort[index2]==NULL||wordLen[index1]<wordLen[index2])
        return true;
    else{
        if(wordLen[index1]==wordLen[index2]){
            if(strcmp(wordsToSort[index1],wordsToSort[index2])<0)
                return true;
            else
                return false;
        }
        else
            return false;
    }
}

//Swaps elements, keeps track of the wordlength
void SortingCompetition::swap(unsigned long int& index1, unsigned long index2){
    if(index1==index2||index1>=allWordsSize-1||index2>=allWordsSize-1)
        return;
    char * tempPtr=wordsToSort[index1];
    wordsToSort[index1]=wordsToSort[index2];
    wordsToSort[index2]=tempPtr;

    int itemp=wordLen[index1];
    wordLen[index1]=wordLen[index2];
    wordLen[index2]=itemp;

}

//Insertion Sort
bool SortingCompetition::insertionSort(long unsigned int& left,long unsigned int& right){
    long unsigned int temp,initLeft= left;
    for(;left<=right; left++){
        for(long unsigned int j=left; j>initLeft; j--){
            temp = j-1;
            if(lessThan(j,temp))
                swap(temp,j);
        }
    }
}

//Destructor
SortingCompetition::~SortingCompetition(){
    delete [] allWords;
    delete allWords;
    delete [] temp;
    delete temp;
    delete [] wordsToSort;
    delete wordsToSort;

}
