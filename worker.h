#pragma once
#include<iostream>
#include<string>
#include<iomanip>
using namespace std;
//����һ��worker������
class Worker {
public:

	//��ʾ������Ϣ
	virtual void ShowInfo() = 0;

	//��ȡ��λ����
	virtual string GetDeptName() = 0;
	//Ա�����
	int id;
	//Ա������
	string name;
	//���ű��
	int dpid;
};
