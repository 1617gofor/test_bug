#include<iostream>
#include"workerManager.h"
#include"worker.h"
#include"employee.h"
#include"manager.h"
#include"Boss.h"
using namespace std;
//����
void test() {
	Worker *w = NULL;
	w = new Employee(1, "����", 1);
	w->ShowInfo();
	delete w;

	w = new Manager(2, "����", 2);
	w->ShowInfo();
	delete w;

	w = new Boss(3, "����", 3);
	w->ShowInfo();
	delete w;
}
int main() {
	//����
	//test();
	//ʵ�����������
	WorkerManager wm;
	int choice = 0;//�����û�ѡ��
	while (true)
	{
		//���ò˵�չʾ����
		wm.ShowMenu();
		cout << "���������ѡ��" << endl;
		cin >> choice;
		switch (choice)
		{
		case 0://�˳�ϵͳ
			wm.ExitSystem();
			break;
		case 1://���
			wm.AddEmp();
			break;
		case 2://��ʾ
			wm.ShowEmp();
			break;
		case 3://ɾ��
			wm.Del();
			break;
		case 4://�޸�
			wm.ModEmp();
			break;
		case 5://����
			wm.FindEmp();
			break;
		case 6://����
			wm.SortEmp();
			break;
		case 7://���
			wm.CleanFile();
			break;
		default:
			system("cls");//��������
			break;
		}
	}
	
	system("pause");
	return 0;
}