#include"workerManager.h"

WorkerManager::WorkerManager() {
	//��ʼ������
	
	//1������ʼʱ�ļ�������
	ifstream ifs;
	ifs.open(FILENAME, ios::in);//���ļ�
	this->SortFlag = 1;//Ĭ����������
	if (!ifs.is_open()) {
		//�ļ��޷��򿪣�˵���ļ�������
		this->EmpNum = 0;
		this->EmpArray = NULL;
		this->FileIsEmpty = true;
		cout << "�ļ�������" << endl;//�������
		ifs.close();
		return;
	}
	//2�����ļ����ڣ������ļ�Ϊ��
	char ch;
	ifs >> ch;//��һ�����ַ���ch
	if (ifs.eof()) {
		//���ļ�Ϊ��������ľ����ļ�β��ǣ���eof()����ֵΪ��
		cout << "�ļ�Ϊ��" << endl;//�������
		this->EmpNum = 0;
		this->EmpArray = NULL;
		this->FileIsEmpty = true;
		ifs.close();
		return;
	}
	//3�������ļ���Ϊ��ʱ
	int num = this->getEmpNum();
	this->EmpNum = num;
	this->EmpArray = new Worker * [num];//���ٿռ�
	this->intEmp();//���ļ��е����ݳ�ʼ��������

	//����һ�´�ӡ���
	for (int i = 0; i < this->EmpNum; i++) {
		cout << this->EmpArray[i]->id << " " << this->EmpArray[i]->name << " " 
			<< this->EmpArray[i]->dpid << endl;
	}
	
}
//ʵ��ShowMenu����
void WorkerManager::ShowMenu() {
	cout << "****************************************************" << endl;
	cout << "*****************��ӭʹ��ְ������ϵͳ*****************" << endl;
	cout << "*****************   0.�˳�����ϵͳ     *****************" << endl;
	cout << "*****************   1.����ְ����Ϣ     *****************" << endl;
	cout << "*****************   2.��ʾְ����Ϣ     *****************" << endl;
	cout << "*****************   3.ɾ����ְְ��     *****************" << endl;
	cout << "*****************   4.�޸�ְ����Ϣ     *****************" << endl;
	cout << "*****************   5.����ְ����Ϣ     *****************" << endl;
	cout << "*****************   6.���ձ������     *****************" << endl;
	cout << "*****************   7.��������ĵ�     *****************" << endl;
	cout << "******************************************************" << endl;
}

//�˳�ϵͳ
void WorkerManager::ExitSystem() {
	cout << "��ӭ�ٴ�ʹ��" << endl;
	system("pause");
	exit(0);//�˳�����
}


//���ְ��,����Ҫ���Ų����ظ�,�Ұ���֮ǰѡ�������ʽ��������---����bug��������
void WorkerManager::AddEmp() {
	cout << "��������ӵ�����" << endl;
	int addNum = 0;//��¼��ӵ�����
	cin >> addNum;
	if (addNum > 0) {
		//���
		//������Ҫ���ٵ��¿ռ��С
		int newSize = this->EmpNum + addNum;

		//�����¿ռ�
		Worker** newSpace = new Worker * [newSize];
		//��ԭ���ռ��µ����ݿ������¿ռ�
		if (this->EmpArray != NULL) {
			for (int i = 0; i < this->EmpNum; i++) {
				newSpace[i] = this->EmpArray[i];
			}
		}
		//�������
        for (int i = 0; i < addNum; i++) {
			int id;//ְ�����
			string name;//ְ������
			int dpid;//���ű��
			//�������ж�������ı���Ƿ��ظ�����ʱ�޷�ʵ��
			/*while (1) {
				cout << "�������" << i + 1 << "λ��ְ�����" << endl;
				cin >> id;
				if (this->IsExit(id) == -1) {
					break;
				}
				cout << "����ı���ظ�������������" << endl;
			}*/
			cout << "�������" << i + 1 << "λ��ְ�����" << endl;
			cin >> id;
			cout << "�������" << i + 1 << "λ��ְ������" << endl;
			cin >> name;

			cout << "��ѡ���ְ����λ��" << endl;
			cout << "1����ְͨ��" << endl;
			cout << "2������" << endl;
			cout << "3���ϰ�" << endl;
			cin >> dpid;
			Worker* worker = NULL;
			//����ѡ�񴴽���ͬ����
			switch (dpid)
			{
			case 1:
				worker = new Employee(id, name, 1);
				break;
			case 2:
				worker = new Manager(id, name, 2);
				break;
			case 3:
				worker = new Boss(id, name, 3);
				break;
			default:
				break;
			}
			//������ְ�����뵽������
			newSpace[this->EmpNum + i] = worker;
		}
		//�ͷ�ԭ���Ŀռ�
		delete[] this->EmpArray;
		this->EmpArray = newSpace;
		//����ְ��������ȷ��֮ǰ�ļ�1��������ȷ��
		this->EmpNum = newSize;
		//��ʾ��ӳɹ�
		cout << "�ɹ����" <<addNum<<"��Ա��" << endl;
		//����һ������
		this->SortByone();
		//���浽�ļ���
		this->Save();
		//��Ϊ�ձ����Ϊfalse
		this->FileIsEmpty = false;
	}
	else {
		cout << "��������" << endl;
	}
	//��������������ص��ϼ�Ŀ¼
	system("pause");
	system("cls");
}

//�����ļ�
void WorkerManager::Save() {
	ofstream ofs;
	ofs.open(FILENAME, ios::out);

	for (int i = 0; i < this->EmpNum; i++) {
		ofs << this->EmpArray[i]->id << " "
			<< this->EmpArray[i]->name <<" "
			<< this->EmpArray[i]->dpid << endl;
	}

	//�ر��ļ�
	ofs.close();
}
//ͳ���ļ��е�����
int WorkerManager::getEmpNum() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);//���ļ��ķ�ʽ��
	int id;
	string name;
	int dpid;
	int sum = 0;//ͳ������
	while (ifs>>id && ifs>>name && ifs>>dpid)//��Ϊ�ļ�һ����ÿ���ֶ����ÿո�����ģ����������ӿ���һ�¶�һ������
	{	
		sum++;
	}
	ifs.close();
	return sum;

}
//��ʼ��Ա��
void WorkerManager::intEmp() {
	int id, dpid;
	string name;
	ifstream ifs;
	ifs.open(FILENAME, ios::in);//���ļ�
	int index = 0;//�����±�
	while (ifs >> id && ifs >> name && ifs >> dpid) {
		Worker* worker = NULL;
		if (dpid == 1) {//��ͨԱ��
			worker = new Employee(id, name, dpid);
		}
		else if(dpid == 2) {//����
			worker = new Manager(id, name, dpid);
		}
		else {//�ϰ�
			worker = new Boss(id, name, dpid);
		}
		this->EmpArray[index] = worker;
		index++;
	}
	ifs.close();
}
//��ʾԱ����Ϣ
void WorkerManager::ShowEmp() {
	if (this->FileIsEmpty) {
		cout << "��ǰϵͳΪ��" << endl;
	}
	else {
		for (int i = 0; i < this->EmpNum; i++) {
			this->EmpArray[i]->ShowInfo();
		}
	}
	//�����������
	system("pause");
	system("cls");
}
//ɾ��ְ��
void WorkerManager::Del() {
	//���ж��ļ��Ƿ�Ϊ��
	if (this->FileIsEmpty) {
		cout << "�ļ���ǰΪ��" << endl;
	}
	else {
		//���ж�Ҫɾ���ı���Ƿ����
		int index;
		cout << "������Ҫɾ����ְ����ţ�" << endl;
		int id;
		cin >> id;
		index = IsExit(id);
		if (index != -1) {
			//˵������
			//���������ǰ��
			for (int i = index; i < this->EmpNum - 1; i++) {
				this->EmpArray[i] = this->EmpArray[i + 1];
			}
			this->EmpNum--;
			//�����ĵ�
			this->Save();
			cout << "ɾ���ɹ�" << endl;
		}
		else {
			//˵��������
			cout << "ɾ��ʧ�ܣ������ڸ�ְ��" << endl;
		}
	}
	//�����������
	system("pause");
	system("cls");
}
//�ж�ְ���Ƿ����,���ھͷ�������λ�ã�����ͷ���-1
int WorkerManager::IsExit(int id) {
	int index = -1;
	for (int i = 0; i < this->EmpNum; i++) {
		if (this->EmpArray[i]->id == id) {
			index = i;
			break;
		}
	}
	return index;
}
//�޸�ְ��
void WorkerManager::ModEmp() {
	if (this->FileIsEmpty) {
		cout << "��ǰϵͳΪ��" << endl;
	}
	else {
		int id;
		cout << "������Ҫ�޸ĵ�ְ����ţ�" << endl;
		cin >> id;
		int ret = this->IsExit(id);
		if (ret != -1) {
			//����
			//������ɾ��ԭ��λ�õ�ְ����Ϣ�������ٰ��µļ���ȥ
			delete this->EmpArray[ret];
			int newid;
			string newname;
			int newdpid;
			cout << "�������µ�ְ�����" << endl;
			cin >> newid;
			cout << "������ְ������" << endl;
			cin >> newname;
			cout << "�������µĸ�λ���" << endl;
			cout << "1����ְͨ��" << endl;
			cout << "2������" << endl;
			cout << "3���ϰ�" << endl;
			cin >> newdpid;
			Worker* worker = NULL;
			//���ݲ�ͬ�ĸ�λ��Ŵ�������
			switch (newdpid)
			{
			case 1:
				worker = new Employee(newid, newname, newdpid);
				break;
			case 2:
				worker = new Manager(newid, newname, newdpid);
				break;
			case 3:
				worker = new Boss(newid, newname, newdpid);
				break;
			default:
				break;
			}
			this->EmpArray[ret] = worker;
			this->Save();//�����ĵ�
			cout << "�޸ĳɹ�" << endl;
		}
		else {
			//������
			cout << "��Ҫ�޸ĵ�ְ��������" << endl;
		}
	}
	//�����������
	system("pause");
	system("cls");
}
//����ְ��
void WorkerManager::FindEmp() {
	//���жϵ�ǰϵͳ�Ƿ�Ϊ��
	if (this->FileIsEmpty) {
		cout << "��ǰϵͳΪ��" << endl;
		//�����������
		system("pause");
		system("cls");
		return;
	}
	int select;//�洢�û�ѡ��
	cout << "��ѡ���ѯ��ʽ" << endl
		<< "1-����Ų�ѯ" << endl
		<< "2-��������ѯ" << endl;
	cin >> select;
	if (select == 1) {
		//1����ְ����Ų�ѯ
		cout << "��������Ҫ���ҵ�ְ�����:" << endl;
		int id;
		cin >> id;
		int ret = IsExit(id);
		if (ret == -1) {
			cout << "��Ҫ���ҵ�ְ��������" << endl;
		}
		else {
			this->EmpArray[ret]->ShowInfo();
			cout << "���ҳɹ�" << endl;
		}
	}
	else if (select == 2) {
		//��ְ��������ѯ
		cout << "������Ҫ��ѯ������" << endl;
		string name;
		cin >> name;
		bool flag = true;//�ж��Ƿ����
		for (int i = 0; i < this->EmpNum; i++) {
			if (this->EmpArray[i]->name == name) {
				flag = false;
				this->EmpArray[i]->ShowInfo();
			}
		}
		if (flag) {
			cout << "��Ҫ���ҵ�ְ��������" << endl;
		}
	}
	else {
		cout << "ѡ������" << endl;
	}
	//�����������
	system("pause");
	system("cls");
}
//����ʵ�ְ��������������߽�������
void WorkerManager::SortEmp() {
	cout << "��ѡ������ʽ" << endl
		<< "1-�������������" << endl
		<< "2-����Ž�������" << endl;
	int select;
	while (1) {//������֤�û������ѡ������ȷ��
		cin >> select;
		if (select == 1 || select == 2) {
			break;
		}
		else {
			cout << "���ѡ����������������" << endl;
		}
	}
	this->SortFlag = select;
	this->SortByone();
	cout << "�����ɹ�" << endl;
	this->Save();
	//�����������
	system("pause");
	system("cls");
}
//����ÿ�ε�����
void WorkerManager::SortByone() {
	for (int i = 0; i < this->EmpNum; i++) {
		int minOrmax = i;
		for (int j = i + 1; j < this->EmpNum; j++) {
			if (this->SortFlag == 1) {
				//����
				if (this->EmpArray[minOrmax]->id > this->EmpArray[j]->id) {
					minOrmax = j;
				}
			}
			else {
				//����
				if (this->EmpArray[minOrmax]->id < this->EmpArray[j]->id) {
					minOrmax = j;
				}
			}
		}
		if (minOrmax != i) {
			Worker* item = this->EmpArray[i];
			this->EmpArray[i] = this->EmpArray[minOrmax];
			this->EmpArray[minOrmax] = item;
		}
	}
}
//����ļ�
void WorkerManager::CleanFile() {
	//���û�����ȷ���Ƿ����
	int ack = 0;
	cout << "�Ƿ�����ļ���" << endl
		<< "1-ȷ��" << endl
		<< "2-ȡ��" << endl;
	cin >> ack;
	if (ack == 1) {
		ofstream ofs;
		ofs.open(FILENAME, ios::trunc);//�򿪷�ʽΪ������ļ�������ɾ�������´���
		ofs.close();
		//�ͷſռ�
		if (this->EmpArray != NULL) {
			for (int i = 0; i < this->EmpNum; i++) {
				if (this->EmpArray[i] != NULL) {
					delete this->EmpArray[i];
					this->EmpArray[i] = NULL;
				}
			}
			delete[] this->EmpArray;
			this->EmpArray = NULL;
			this->EmpNum = 0;
			this->FileIsEmpty = true;
		}
		cout << "��ճɹ�" << endl;
	}
	else {
		cout << "��ȡ��" << endl;
	}
	//�����������
	system("pause");
	system("cls");
}
WorkerManager::~WorkerManager() {
	//�ͷſռ�
	if (this->EmpArray != NULL) {
		for (int i = 0; i < this->EmpNum; i++) {
			if (this->EmpArray[i] != NULL) {
				delete this->EmpArray[i];
				this->EmpArray[i] = NULL;
			}
		}
		delete[] this->EmpArray;
		this->EmpArray = NULL;
	}
}