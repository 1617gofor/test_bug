#pragma once
#include"worker.h"

//����
class Boss :public Worker {
public:
	Boss(int id, string name, int dpid);
	//��ʾ������Ϣ
	virtual void ShowInfo();

	//��ȡ��λ����
	virtual string GetDeptName();
};
