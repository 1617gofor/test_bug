#pragma once//��ֹͷ�ļ��ظ�����
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
	//��ʾ�ļ��Ƿ�Ϊ��
	bool FileIsEmpty;
	
	WorkerManager();

	//չʾ�˵�
	void ShowMenu();

	//��¼ְ������
	int EmpNum;
	//ְ������ָ��
	Worker** EmpArray;

	//���ְ��
	void AddEmp();

	//�����ļ�
	void Save();

	//ͳ���ļ��е�����
	int getEmpNum();
	//��ʼ��Ա��
	void intEmp();
	//��ʾԱ����Ϣ
	void ShowEmp();
	//ɾ��ְ��
	void Del();
	//�ж�ְ���Ƿ����
	int IsExit(int id);
	//�޸�ְ��
	void ModEmp();
	//����ְ��
	void FindEmp();
	//����
	void SortEmp();
	//����ÿ�γ���������
	void SortByone();
	//����Ǻ�������
	int SortFlag;//��ʱû��
	//����ļ�
	void CleanFile();
	//�˳�ϵͳ
	void ExitSystem();
	~WorkerManager();

};
