#pragma once
#include <iostream>
#include "stuff.h"

using namespace std;

class Manager: public Stuff
{
public:

    Manager(int id,string name,int dId);
    virtual void showInfo();
    virtual string getDeptName();
};