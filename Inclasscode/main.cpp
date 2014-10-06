#include <iostream>
#include "Person.h"
#include <chrono>
#include <ctime>
#include<fstream>

using namespace std;

int main()
{
    unsigned long int numIt=200000000;

    string name="Sam";
    int age=18;

    Person * person = new Person();

    person->setAge(age);
    person->setName(name);

    cout << person->getName() <<" " <<person->getAge() <<"\n";

    ofstream foutVal;
    foutVal.open("outputVal.txt");

    ofstream foutRef;
    foutRef.open("outputRef.txt");

    for(int j=0; j<30; j++){

    //By Value
    chrono::time_point<chrono::system_clock> start, end;

    start=chrono::system_clock::now();

    for(unsigned long int i=0; i<numIt; i++){
        person->setAge(age);
        person->setName(name);
    }

    end=chrono::system_clock::now();

    chrono::duration<double> elapsed_seconds = end-start;
    time_t end_time = chrono::system_clock::to_time_t(end);

    foutVal <<  elapsed_seconds.count() << "\n";

    //By Ref

    start=chrono::system_clock::now();

    for(unsigned long int i=0; i<numIt; i++){
        person->setAgebyRef(age);
        person->setNamebyRef(name);
    }

    end=chrono::system_clock::now();

    elapsed_seconds = end-start;
    end_time = chrono::system_clock::to_time_t(end);

    foutRef<< elapsed_seconds.count() << "\n";

   }
    return 0;
}

