#pragma once
#include"worker.h"

//经理
class Boss :public Worker {
public:
	Boss(int id, string name, int dpid);
	//显示个人信息
	virtual void ShowInfo();

	//获取岗位名称
	virtual string GetDeptName();
};
