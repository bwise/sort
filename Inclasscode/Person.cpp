#include "Person.h"

Person::Person()
{
}

int Person::getAge(){
    return age;
}

std::string Person::getName(){
    return name;
}
void Person::setAge(int a){
    age=a;

}
void Person::setName(std::string s){
    name=s;

}

Person::~Person(){

}

void Person::setNamebyRef(std::string &n){
    name=n;
}

void Person::setAgebyRef(int &a){
    age=a;

}
