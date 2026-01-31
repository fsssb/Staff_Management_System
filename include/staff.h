#pragma once 
#include <iostream>
#include <string>



class Staff
{
public:
    //显示个人信息
    virtual void showInfo() = 0;

    //获取岗位名称
    virtual std::string getDeptName() = 0;

    virtual ~Staff() = default;

    int m_Id;//职工编号
    std::string m_name; //职工姓名
    int m_DeptId; //职工所在部分编号

};