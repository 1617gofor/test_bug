#pragma once
#include"worker.h"

//����
class Manager :public Worker {
public:
	Manager(int id, string name, int dpid);
	//��ʾ������Ϣ
	virtual void ShowInfo();

	//��ȡ��λ����
	virtual string GetDeptName();
};
