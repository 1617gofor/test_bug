#pragma once//防止头文件重复包含
#include<iostream>
#include"worker.h"
#include"employee.h"
#include"Boss.h"
#include"manager.h"
#include<fstream>
using namespace std;
#define FILENAME "empFile.txt"
class WorkerManager {
public:
	//表示文件是否为空
	bool FileIsEmpty;
	
	WorkerManager();

	//展示菜单
	void ShowMenu();

	//记录职工人数
	int EmpNum;
	//职工数组指针
	Worker** EmpArray;

	//添加职工
	void AddEmp();

	//保存文件
	void Save();

	//统计文件中的人数
	int getEmpNum();
	//初始化员工
	void intEmp();
	//显示员工信息
	void ShowEmp();
	//删除职工
	void Del();
	//判断职工是否存在
	int IsExit(int id);
	//修改职工
	void ModEmp();
	//查找职工
	void FindEmp();
	//排序
	void SortEmp();
	//用于每次出入后的排序
	void SortByone();
	//标记是何种排序
	int SortFlag;//暂时没用
	//清空文件
	void CleanFile();
	//退出系统
	void ExitSystem();
	~WorkerManager();

};
