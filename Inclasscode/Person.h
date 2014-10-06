#ifndef PERSON_H
#define PERSON_H
#include<string>

class Person
{
private:
    std::string name;
    int age;
public:
    Person();
    ~Person();
    std::string getName();
    int getAge();
    void setName( std::string name);
    void setAge(int age);
    void setNamebyRef(std::string &name);
    void setAgebyRef(int &age);
};

#endif // PERSON_H
