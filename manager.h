#pragma once
#include"worker.h"

//经理
class Manager :public Worker {
public:
	Manager(int id, string name, int dpid);
	//显示个人信息
	virtual void ShowInfo();

	//获取岗位名称
	virtual string GetDeptName();
};
