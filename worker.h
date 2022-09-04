#pragma once
#include<iostream>
#include<string>
#include<iomanip>
using namespace std;
//创建一个worker抽象类
class Worker {
public:

	//显示个人信息
	virtual void ShowInfo() = 0;

	//获取岗位名称
	virtual string GetDeptName() = 0;
	//员工编号
	int id;
	//员工姓名
	string name;
	//部门编号
	int dpid;
};
