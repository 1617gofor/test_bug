#pragma once
#include"worker.h"

//职工类
class Employee :public Worker {
public:
	Employee(int id, string name, int dpid);
	//显示个人信息
	virtual void ShowInfo();

	//获取岗位名称
	virtual string GetDeptName();
};
