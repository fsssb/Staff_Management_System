#pragma once
#include <iostream>

using namespace std;

class StuffManager
{
public:
    //构造函数
    StuffManager();

    //展示菜单
    void showMenu(StuffManager& vm);

    //退出系统

    void exitSystem();

    //析构函数
    ~StuffManager();
    
};