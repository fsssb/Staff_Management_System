#pragma once
#include <iostream>
#include "staff.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"

#include <fstream>
#define FILENAME "StaffFile.txt"


class StaffManager
{
public:

    //构造函数
    StaffManager();

    //展示菜单
    void showMenu(StaffManager& vm);

    //退出系统
    void exitSystem();

    //添加职工函数
    void add_Staff();

    //保存文件
    void saveFile();

    //获取职工人数
    int GetStaffNum();

    //初始化员工
    void initStaff();

    //显示职工信息
    void showStaffInfo();

    //职工是否在系统里
    int isExist(int id);

    //删除离职职工(按职工ID删除)
    void delStaff();

    //修改职工信息
    void modify_Staff();

    //查找职工
    void findStaff();

    //职工排序
    void sortStaff();

    //清空文件
    void cleanFile();
    
    //清理屏幕并暂停
    void CleanAndPause();

    //析构函数
    ~StaffManager();

private:

    //员工数组的指针
    Staff** m_StaffArray;

    //记录当前文件中的人员个数
    int m_StaffNum;

    //文件是否为空的标志
    bool m_FileIsEmpty;

   

    
};