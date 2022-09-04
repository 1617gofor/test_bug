#include"Boss.h"
Boss::Boss(int id, string name, int dpid) {
	this->id = id;
	this->name = name;
	this->dpid = dpid;
}
//显示个人信息
void Boss::ShowInfo() {
	cout <<std::left<<setw(7) << "职工编号：" << this->id << "  "
		<< std::left << setw(7) << "职工姓名：" << this->name << "  "
		<< std::left << setw(7) << "岗位：" << this->GetDeptName() << "  "
		<< std::left << setw(20) << "岗位职责：管理公司所有事务" << endl;
}

//获取岗位名称
string Boss::GetDeptName() {
	return string("总裁");
}