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
    lengthOfWords = new unsigned long int[allWordsCapacity];
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
    unsigned long int* tempLen = new unsigned long int[allWordsCapacity+100000];
    for( unsigned long int i=0; i<allWordsCapacity; i++){
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
    for( unsigned long int i =0; i< allWordsSize-1; i++){
        wordsToSort[i] = new char [strlen(allWords[i])+1];
        strcpy(wordsToSort[i], allWords[i]);
    }
    lengthToSort = new unsigned long int[allWordsSize];
    for( unsigned long int i =0; i< allWordsSize-1; i++){
        lengthToSort[i] = lengthOfWords[i];
    }
    return true;
}

void SortingCompetition::quickSort(unsigned long int left, unsigned long int right){
    if((right-left)<2)
      return;
    unsigned long int center = (left+right)/2;
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
    unsigned long int pivot = right-1;
    unsigned long int i=left,j=right-1;
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

void SortingCompetition::introSort(unsigned long int left, unsigned long int right){
    unsigned long int switchsize=23;
    if((right-left)<2)
      return;
    unsigned long int center = (left+right)/2;
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
    unsigned long int pivot = right-1;
    unsigned long int i=left,j=right-1;
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
        unsigned long int temp=i-1;
        insertionSort(left,temp);
        temp=i+1;
        insertionSort(temp,right);
    }
    else{
        quickSort(left,i-1);
        quickSort(i+1,right);
        }
}


void SortingCompetition::sortData(){
    this->sortDataThread();
}

void SortingCompetition::sortDataThread(){
    unsigned long int N=1024;
    unsigned long int chunk=1;
    unsigned long int i=0;

#pragma omp parallel private(i)
    {
#pragma omp for schedule(static,chunk) nowait
        for(i=0; i<N; i++)
        {
            quickSort(((i*allWordsSize)/N), (((allWordsSize*(i+1))/N))-1);
        }
    }

merge(1);

}

void SortingCompetition::merge(unsigned long n){
    if(n<=1){
        cout<<"end"<<endl;
        return;
    }
    cout<<n<<endl;
    unsigned long int a=0,b=0;
    for(int k=0; k<n; k+=2)
    {
        a= (allWordsSize*(k))/n;
        b= (allWordsSize*(k+1))/n;

        for(int i=(allWordsSize*k)/n; i<((k+2)*allWordsSize)/n; i++){
        if(lessThan(a,b)&&a<(allWordsSize*(k+1))/n){
            temp[i] = wordsToSort[a];
            a++;
        }
        else if(lessThan(b,a)&&b<((allWordsSize*(k+2))/n)-1){
            temp[i] = wordsToSort[b];
            b++;
        }
        cout<<wordsToSort[a]<<"\t"<<wordsToSort[b]<<"\t"<<((k+2)*allWordsSize)/n<<endl;
      }
        cout<<"here"<<endl;
    }

    for(unsigned int i =0; i< allWordsSize; i++){
        delete wordsToSort[i];
        wordsToSort[i]=temp[i];
        temp[i]=NULL;

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
*/
void SortingCompetition::sortData(unsigned long int compare){
    //introSort(0,allWordsSize, compare);
}


void SortingCompetition::outputData(const string &outputFileName){
    ofstream fout(outputFileName, ios::out);
    for( unsigned long int i=0; i< allWordsSize-1; i++){
        fout<<wordsToSort[i]<<"\n";
    }
    fout.close();
}

void SortingCompetition::outputDataThread(const string &outputFileName){
    ofstream fout(outputFileName, ios::out);
    for( unsigned long int i=0; i< allWordsSize-1; i++){
        fout<<wordsSorted[i]<<"\n";

    }
    fout.close();
}

bool SortingCompetition::lessThan(unsigned long int &index1, unsigned long int &index2){
    if(index1==index2||index1>allWordsSize-1||index2>allWordsSize-1)
        return false;
    if(strlen(wordsToSort[index1])<strlen(wordsToSort[index2]))
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

void SortingCompetition::swap(unsigned long int& index1, unsigned long int index2){
    if(index1==index2||index1>=allWordsSize-1||index2>=allWordsSize-1)
        return;
    //cout <<"s";
    //cout << wordsToSort[index1]<<wordsToSort[index2];

    char * tempPtr=wordsToSort[index1];
    wordsToSort[index1]=wordsToSort[index2];
    wordsToSort[index2]=tempPtr;

    unsigned long int tempInt = lengthToSort[index1];
    lengthToSort[index1]=lengthToSort[index2];
    lengthToSort[index2]=tempInt;

}

bool SortingCompetition::insertionSort(unsigned long int& left, unsigned long int& right){
 unsigned long int currentmax;
    for(unsigned long int j=left; j<right; j++){
        currentmax=j;
        for(unsigned long int i=j+1; i<right; i++){
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
