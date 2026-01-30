#pragma once
#include <iostream>
#include "stuff.h"

using namespace std;

class Employee: public Stuff
{
public:

    Employee(int id,string name,int dId);
    virtual void showInfo();
    virtual string getDeptName();
};