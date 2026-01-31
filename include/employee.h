#pragma once
#include <iostream>
#include "staff.h"



class Employee: public Staff
{
public:

    Employee(int id,std::string name,int dId);
    virtual void showInfo();
    virtual std::string getDeptName();
};