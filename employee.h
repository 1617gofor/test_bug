#pragma once
#include"worker.h"

//ְ����
class Employee :public Worker {
public:
	Employee(int id, string name, int dpid);
	//��ʾ������Ϣ
	virtual void ShowInfo();

	//��ȡ��λ����
	virtual string GetDeptName();
};
