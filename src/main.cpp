#include <iostream>
#include "staffManager.h"

#include <unistd.h>
#include <termios.h>

using namespace std;


inline void pauseLinux()
{
    write(STDOUT_FILENO, "\n按回车继续...", 18);
    char c;
    read(STDIN_FILENO, &c, 1);
}


// void test01()  //代码重复，可以改进！
// {
//     Staff* Staff = nullptr;
//     Staff = new Employee(1111,"fsssb",6);    
//     Staff->showInfo();
//     delete Staff;
//     Staff = nullptr;

//     Staff = new Manager(2222,"czy",5);    
//     Staff->showInfo();
//     delete Staff;
//     Staff = nullptr;

//     Staff = new Boss(3333,"HITSZ",9);    
//     Staff->showInfo();
//     delete Staff;
//     Staff = nullptr;
// }

int main()
{

    // test01();

    //实例化管理者
    StaffManager sm;

    int choice = 0;
    while(true)
    {
        //调用展示菜单成员函数
        sm.showMenu(sm);
        cout << "请输入您的选择：" << endl;

        cin >> choice;
        
        switch(choice)
        {
            case 0://退出系统
                sm.exitSystem();
                break;
            case 1://添加职工
                sm.add_Staff();
                break;
            case 2://显示职工
                sm.showStaffInfo();
                break;
            case 3://删除职工
                sm.delStaff();
                break;
            case 4://修改职工
                sm.modify_Staff();
                break;
            case 5://查找职工
                sm.findStaff();
                break;
            case 6://排序职工
                sm.sortStaff();
                break;
            case 7://清空文件
                sm.cleanFile();
                break;
            default:
                system("clear");
                break;
        }
    }

    //调用展示菜单成员函数
    sm.showMenu(sm);
    return 0;

}

