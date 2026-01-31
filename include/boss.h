#pragma once
#include <iostream>
#include "staff.h"



class Boss: public Staff
{
public:

    Boss(int id,std::string name,int dId);
    virtual void showInfo();
    virtual std::string getDeptName();
};