#include<iostream>
#include"workerManager.h"
#include"worker.h"
#include"employee.h"
#include"manager.h"
#include"Boss.h"
using namespace std;
//测试
void test() {
	Worker *w = NULL;
	w = new Employee(1, "张三", 1);
	w->ShowInfo();
	delete w;

	w = new Manager(2, "李四", 2);
	w->ShowInfo();
	delete w;

	w = new Boss(3, "王五", 3);
	w->ShowInfo();
	delete w;
}
int main() {
	//测试
	//test();
	//实例化管理对象
	WorkerManager wm;
	int choice = 0;//接收用户选择
	while (true)
	{
		//调用菜单展示函数
		wm.ShowMenu();
		cout << "请输入你的选择" << endl;
		cin >> choice;
		switch (choice)
		{
		case 0://退出系统
			wm.ExitSystem();
			break;
		case 1://添加
			wm.AddEmp();
			break;
		case 2://显示
			wm.ShowEmp();
			break;
		case 3://删除
			wm.Del();
			break;
		case 4://修改
			wm.ModEmp();
			break;
		case 5://查找
			wm.FindEmp();
			break;
		case 6://排序
			wm.SortEmp();
			break;
		case 7://清空
			wm.CleanFile();
			break;
		default:
			system("cls");//清屏操作
			break;
		}
	}
	
	system("pause");
	return 0;
}