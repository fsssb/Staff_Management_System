#include "boss.h"

using namespace std;

Boss::Boss(int id,string name,int dId)
{
    this->m_Id = id;
    this->m_name = name;
    this->m_DeptId = dId;
}
void Boss::showInfo()
{
    cout << "职工编号:" << this->m_Id
        << "\t职工姓名:" << this->m_name
        << "\t岗位:" << this->getDeptName()
        <<"\t岗位职责：负责公司运转，给经理下发任务" << endl;
}

string Boss::getDeptName()
{
    return string ("老板");
}