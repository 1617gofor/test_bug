#include"manager.h"

Manager::Manager(int id, string name, int dpid) {
	this->id = id;
	this->name = name;
	this->dpid = dpid;
}
//显示个人信息
void Manager::ShowInfo() {
	cout << std::left << setw(7) << "职工编号：" << this->id<<"  "
		<< std::left << setw(7) << "职工姓名：" << this->name << "  "
		<< std::left << setw(7) << "岗位：" << this->GetDeptName() << "  "
		<< std::left << setw(20) << "岗位职责： 完成老板交付的任务，并且管理员工" << endl;
}

//获取岗位名称
string Manager::GetDeptName() {
	return string("经理");
}