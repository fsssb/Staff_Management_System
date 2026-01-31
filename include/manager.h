#pragma once
#include <iostream>
#include "staff.h"



class Manager: public Staff
{
public:

    Manager(int id,std::string name,int dId);
    virtual void showInfo();
    virtual std::string getDeptName();
};