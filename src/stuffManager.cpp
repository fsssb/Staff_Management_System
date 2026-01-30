#include "stuffManager.h"
#include <iostream>
using namespace std;


StuffManager::StuffManager()
    {

    }
StuffManager::~StuffManager()
    {
        
    }

void StuffManager::showMenu(StuffManager& vm)
{
    cout << "--------------------------------------" << endl;
    cout << "--------欢迎使用职工管理系统！--------" << endl;
    cout << "--------------------------------------" << endl;
    cout << endl;
    cout << "\t0.退出管理系统" << endl;
    cout << "\t1.增加职工信息" << endl;
    cout << "\t2.显示职工信息" << endl;
    cout << "\t3.删除离职员工" << endl;
    cout << "\t4.修改职工信息" << endl;
    cout << "\t5.查找职工信息" << endl;
    cout << "\t6.按照编号排序" << endl;
    cout << "\t7.清空所有文档" << endl;
    cout << endl;
    cout << "--------------------------------------" << endl;
    cout << endl;
}

void StuffManager::exitSystem()
{
    system("clear");
    cout << "欢迎下次使用！" << endl;
    
    exit(0);
}