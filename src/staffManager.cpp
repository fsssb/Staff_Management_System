#include "staffManager.h"
#include <iostream>
using namespace std;


//构造函数
StaffManager::StaffManager()
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in);

    //文件不存在的情况
    if (!ifs.is_open())
    {
        cout << "文件不存在！" << endl;
        this->m_FileIsEmpty = true;//文件为空标志为真
        this->m_StaffNum = 0;
        this->m_StaffArray = nullptr;
        ifs.close();
        return;
    }

    //文件存在但为空的情况
    char ch;
    ifs >> ch;
    if (ifs.eof())
    {
        cout << "文件为空！" << endl;
        this->m_FileIsEmpty = true;//文件为空标志为真
        this->m_StaffNum = 0;
        this->m_StaffArray = nullptr;
        ifs.close();
        return;
    }  

    //文件存在且不为空的情况 
    int num = this->GetStaffNum();
    // cout << "职工个数为：" << num << endl;

    this->m_StaffNum = num;

    //将文件中的数据存到数组中
    this->initStaff();
    
    //文件为空标志为假！
    this->m_FileIsEmpty = false;

    // for(int i = 0;i < this->m_StaffNum;i++)
    // {
    //     cout << "职工编号： " << this->m_StaffArray[i]->m_Id
    //         <<"\t职工姓名：" << this->m_StaffArray[i]->m_name
    //         <<"\t部门编号：" << this->m_StaffArray[i]->m_DeptId 
    //         << endl;
    // }
}

//展示菜单
void StaffManager::showMenu(StaffManager& vm)
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



//退出系统
void StaffManager::exitSystem()
{
    system("clear");
    cout << "欢迎下次使用！" << endl;

    //清空屏幕并退出
    this->CleanAndPause();
    
    exit(0);
}


//添加职工函数
void StaffManager::add_Staff()
{
    cout << "请输入要添加的职工数量：" << endl;
    int addNum = 0;
    cin >> addNum;

    if (addNum > 0)
    {
        //计算一下新的空间的大小
        int newSize = this->m_StaffNum + addNum;

        //开辟一个新空间
        Staff** newSpace = new Staff*[newSize];

        //将原来空间下的数据拷贝到新空间下
        if (this->m_StaffArray != nullptr)
        {
            for (int i = 0; i < this->m_StaffNum; i++)
            {
                newSpace[i] = this->m_StaffArray[i];
            }

        }
        //输入新数据
        for (int i = 0; i < addNum; i++)
        {
            int id;
            string name;
            int dSelect;
            cout << "请输入第 " << i + 1 << " 个新职工的编号：" << endl;
            cin >> id;
            cout << "请输入第 " << i + 1 << " 个新职工的姓名：" << endl;
            cin >> name;
            cout << "请选择该职工的岗位：" << endl;
            cout << "\t1.普通员工" << endl;
            cout << "\t2.经理" << endl;
            cout << "\t3.老板" << endl;
            cin >> dSelect;

            //根据岗位选择创建不同类型的职工对象
            Staff* newStaff = nullptr;
            switch (dSelect)
            {
                case 1:
                    newStaff = new Employee(id, name, 1);
                    break;
                case 2:
                    newStaff = new Manager(id, name, 2);
                    break;
                case 3:
                    newStaff = new Boss(id, name, 3);
                    break;
                default:
                    cout << "输入有误！" << endl;
                    delete[] newSpace; 
                    return; // 如果输入无效，直接返回
            }

            //将新职工添加到数组中
            newSpace[this->m_StaffNum + i] = newStaff;
        }

        //释放原有空间
        delete[] this->m_StaffArray;    
        this->m_StaffArray = nullptr;

        //更新成员变量
        this->m_StaffArray = newSpace;
        this->m_StaffNum = newSize;

        //更新文件为空标志
        this->m_FileIsEmpty = false;

        //t提示添加成功
        cout << "成功添加 " << addNum << " 名新职工！" << endl; 
        
        //保存文件
        this->saveFile();

        //清理屏幕并暂停
        this->CleanAndPause();

    }

    else
    {
        cout << "输入有误！" << endl;
    }
}

//保存文件
void StaffManager::saveFile()
{
    ofstream ofs;
    ofs.open(FILENAME, ios::out);   
    for (int i = 0; i < this->m_StaffNum; i++)
    {
        ofs << this->m_StaffArray[i]->m_Id << "\t "
            << this->m_StaffArray[i]->m_name << "\t "
            << this->m_StaffArray[i]->m_DeptId << endl;
    }
    ofs.close();
}


//获取职工人数  
int StaffManager::GetStaffNum()
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in); //读文件

    int id;
    string name;
    int dId;

    int num = 0;

    while (ifs >> id && ifs >> name && ifs >> dId) 
    {
        num++;
    }

    this->m_StaffNum = num;

    ifs.close();

    return num;
}

//初始化员工
void StaffManager::initStaff()
{
    //初始化职工
    ifstream ifs;
    ifs.open(FILENAME, ios::in); //读文件

    int id;
    string name;
    int dId;
    int index = 0;
    
    //开辟内存
    this->m_StaffArray = new Staff * [this->m_StaffNum];
    while (ifs >> id && ifs >> name && ifs >> dId)
    {
        Staff* s = nullptr;
        switch (dId)
        {
            case 1:
                s = new Employee(id, name, dId);
                break;
            case 2:
                s = new Manager(id, name, dId);
                break;
            case 3:
                s = new Boss(id, name, dId);
                break;
        }
        this->m_StaffArray[index] = s;
        index++;
    }
    ifs.close();
}

//显示职工信息
void StaffManager::showStaffInfo()
{
    if(this->m_FileIsEmpty)
    {
        cout <<"文件不存在或者文件记录为空！"<< endl;
    }

    else
    {
        for(int i = 0;i < this->m_StaffNum;i++)
        {
            this->m_StaffArray[i]->showInfo();
        }
    }

    this->CleanAndPause();
}


//职工是否在系统里
int StaffManager::isExist(int id)
{
    int index = -1;
    for(int i = 0;i < this->m_StaffNum; i++)
    {
        if(this->m_StaffArray[i]->m_Id == id)
        {
            index = i;
            break;
        }
    }
    return index;
}


//删除离职职工(按职工ID删除)
void StaffManager::delStaff()
{
    if(this->m_FileIsEmpty)
    {
        cout << "文件不存在或者记录为空！" << endl;
    }

    else
    {
        int id;
        cout << "请输入您要删除的职工ID:" << endl;
        cin >> id;

        if(this->isExist(id) == -1)
        {
            cout << "系统中不存在该员工！" << endl; 
        }

        else
        {
            int target = this->isExist(id);
            for (int i = target; i < this->m_StaffNum - 1; i++) //边界条件
             {
                this->m_StaffArray[i] = this->m_StaffArray[i+1];
            }
            this->m_StaffNum--;

            //数据重新写入文件中
            this->saveFile();

            cout << " 已经成功删除该员工！" << endl;
        }
    }

    this->CleanAndPause();

}


//修改职工信息
void StaffManager::modify_Staff()
{
    if(this->m_FileIsEmpty){
        cout << "文件不存在或者文件记录为空！" << endl;
    }

    else
    {
        cout << "请输入要修改的职工编号：" << endl;
        int id;
        cin >> id;

        int ret = this->isExist(id);
        if(ret != -1)
        {
            delete this->m_StaffArray[ret];

            int newId = 0;
            string newName = "";
            int newDSelect = 0;

            cout << "查到：" << id << "号职工，请重新输入职工编号：" << endl;
            cin >> newId;
            
            cout << "请重新输入姓名：" << endl;
            cin >> newName;

            cout << "请重新输入岗位：" << endl;
            cout << "1.普通员工" << endl;
            cout << "2.经理" << endl;
            cout << "3.老板" << endl;
            cin >> newDSelect;

            Staff* newStaff = nullptr;
            switch(newDSelect)
            {
                case 1:
                    newStaff = new Employee(newId,newName,newDSelect);
                    break;
                case 2:
                    newStaff = new Manager(newId,newName,newDSelect);
                    break;
                case 3:
                    newStaff = new Boss(newId,newName,newDSelect);
                    break;
                default:
                    break;
            }

            this->m_StaffArray[ret] = newStaff;

            cout << "修改成功! " << endl;

            //更新到文件！
            this->saveFile();
        }
        else
        {
            cout << "查无此人！无法修改" << endl;
        }
    }

    this->CleanAndPause();
}



//查找职工
void StaffManager::findStaff()
{
    if(this->m_FileIsEmpty)
    {
        cout << "文件不存在或者文件记录为空！" << endl;
    }
    else
    {
        while(true)
        {
            cout << "选择查找方式：" << endl;
            cout << "1.按照ID查找" << endl;
            cout << "2.按照姓名查找：" << endl;

            int sel = 0;
            cin >> sel;

            //按照ID查找
            if(sel == 1)
            {   
                cout << "请输入职工ID：" << endl;
                int id = 0;
                cin >> id;

                int ret = this->isExist(id);
                if(ret != -1)
                {
                    cout << "找到此人！信息如下" << endl;
                    this->m_StaffArray[ret]->showInfo();
                } 
                else
                {
                    cout << "查无此人！" << endl;
                }

                break;
            }
            

            //按照姓名查找
            else if(sel == 2)
            {
                 //加入是否找到判断标志
                bool flag = false;

                cout << "请输入职工姓名" << endl;
                string name = "";
                cin >> name;
                for (int i = 0; i < this->m_StaffNum;i++)
                {
                    if(this->m_StaffArray[i]->m_name == name)
                    {
                        cout << "找到此人！信息如下" << endl;
                        this->m_StaffArray[i]->showInfo();
                        flag = true;
                    }
                }
                if(!flag)
                {
                    cout << "查无此人！" << endl;
                }
                break;
            }

            //输入其他数字(待优化问题，处理非法输入！)
            else
            {
                cout << "请输入正确的选择序号！" << endl;
            }
        }
    }

    this->CleanAndPause();
}


//职工排序
void StaffManager::sortStaff()
{
    if(this->m_FileIsEmpty)
    {
        cout << "文件不存在或者文件记录为空！" << endl;
        return;
    }
    cout << "请选择排序方式：" << endl;
    cout << "1.按照员工ID升序排列" << endl;
    cout << "2.按照员工ID降序排列" << endl;

    int select = 0;
    cin >> select;

    //开始选择排序
    for(int i = 0;i < this->m_StaffNum-1;i++)
    {
        int targetIndex = i;//记录最大或者最小值

        for(int j = i + 1; j < this->m_StaffNum; j++)
        {
            if(select == 1)
            {
                if(this->m_StaffArray[i]->m_Id > this->m_StaffArray[j]->m_Id)
                {
                    targetIndex = j;
                }
            }

            else
            {
                if(this->m_StaffArray[i]->m_Id < this->m_StaffArray[j]->m_Id)
                {
                    targetIndex = j;
                }
            }
        }
        if (targetIndex != i)
        {
            Staff* temp = this->m_StaffArray[i];
            this->m_StaffArray[i] = this->m_StaffArray[targetIndex];
            this->m_StaffArray[targetIndex] = temp;

        }
    }

    cout << "排序成功！" << endl;
    //保存到文件并展示！
    this->saveFile();
    this->showStaffInfo(); 
}

//清空文件
void StaffManager::cleanFile()
{
    // 1. 再次确认 (防止手抖误删)
    cout << "确认清空？" << endl;
    cout << "1. 确认" << endl;
    cout << "2. 返回" << endl;

    int select = 0;
    cin >> select;

    if (select != 1)
    {
        this->CleanAndPause();
        return;
    }

    ofstream ofs(FILENAME,ios::trunc);
    ofs.close();

    if(this->m_StaffArray != nullptr)
    {
        //释放每一个数组对象
        for(int i = 0; i < this->m_StaffNum; i++)
        {
            delete this->m_StaffArray[i];
            this->m_StaffArray[i] = nullptr;
        }        
    }
    //再释放整个数组指针本身
    delete[] this->m_StaffArray;
    this->m_StaffArray = nullptr;

    //计数清零
    this->m_StaffNum = 0;

    //更新文件标志位
    this->m_FileIsEmpty = true;

    cout << " 清空成功！" << endl;

    this->CleanAndPause();
}

//清理屏幕并暂停
void StaffManager::CleanAndPause()
{
    cout << "请按任意键继续..." << endl;
    cin.ignore(1024, '\n');
    cin.get();
    system("clear");
}


//析构函数
StaffManager::~StaffManager()
{
    if (this->m_StaffArray != nullptr)
    {
        for (int i = 0; i < this->m_StaffNum; i++)
        {   
            if (this->m_StaffArray[i] != nullptr)
            {
            //删除每一个职工对象
            delete this->m_StaffArray[i];
            }
        }
        //删除职工数组
        delete[] this->m_StaffArray;
    }
}