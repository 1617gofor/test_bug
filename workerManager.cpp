#include"workerManager.h"

WorkerManager::WorkerManager() {
	//初始化属性
	
	//1、若开始时文件不存在
	ifstream ifs;
	ifs.open(FILENAME, ios::in);//打开文件
	this->SortFlag = 1;//默认升序排序
	if (!ifs.is_open()) {
		//文件无法打开，说明文件不存在
		this->EmpNum = 0;
		this->EmpArray = NULL;
		this->FileIsEmpty = true;
		cout << "文件不存在" << endl;//测试输出
		ifs.close();
		return;
	}
	//2、若文件存在，但是文件为空
	char ch;
	ifs >> ch;//读一个数字符给ch
	if (ifs.eof()) {
		//若文件为空则读到的就是文件尾标记，即eof()返回值为真
		cout << "文件为空" << endl;//测试输出
		this->EmpNum = 0;
		this->EmpArray = NULL;
		this->FileIsEmpty = true;
		ifs.close();
		return;
	}
	//3、若果文件不为空时
	int num = this->getEmpNum();
	this->EmpNum = num;
	this->EmpArray = new Worker * [num];//开辟空间
	this->intEmp();//将文件中的数据初始化到数组

	//测试一下打印输出
	for (int i = 0; i < this->EmpNum; i++) {
		cout << this->EmpArray[i]->id << " " << this->EmpArray[i]->name << " " 
			<< this->EmpArray[i]->dpid << endl;
	}
	
}
//实现ShowMenu函数
void WorkerManager::ShowMenu() {
	cout << "****************************************************" << endl;
	cout << "*****************欢迎使用职工管理系统*****************" << endl;
	cout << "*****************   0.退出管理系统     *****************" << endl;
	cout << "*****************   1.增加职工消息     *****************" << endl;
	cout << "*****************   2.显示职工消息     *****************" << endl;
	cout << "*****************   3.删除离职职工     *****************" << endl;
	cout << "*****************   4.修改职工消息     *****************" << endl;
	cout << "*****************   5.查找职工消息     *****************" << endl;
	cout << "*****************   6.按照编号排序     *****************" << endl;
	cout << "*****************   7.清空所有文档     *****************" << endl;
	cout << "******************************************************" << endl;
}

//退出系统
void WorkerManager::ExitSystem() {
	cout << "欢迎再次使用" << endl;
	system("pause");
	exit(0);//退出程序
}


//添加职工,并且要求编号不能重复,且按照之前选择的排序方式进行排序---存在bug！！！！
void WorkerManager::AddEmp() {
	cout << "请输入添加的人数" << endl;
	int addNum = 0;//记录添加的人数
	cin >> addNum;
	if (addNum > 0) {
		//添加
		//计算需要开辟的新空间大小
		int newSize = this->EmpNum + addNum;

		//开辟新空间
		Worker** newSpace = new Worker * [newSize];
		//将原来空间下的数据拷贝到新空间
		if (this->EmpArray != NULL) {
			for (int i = 0; i < this->EmpNum; i++) {
				newSpace[i] = this->EmpArray[i];
			}
		}
		//批量添加
        for (int i = 0; i < addNum; i++) {
			int id;//职工编号
			string name;//职工姓名
			int dpid;//部门编号
			//在这里判断新输入的编号是否重复，暂时无法实现
			/*while (1) {
				cout << "请输入第" << i + 1 << "位新职工编号" << endl;
				cin >> id;
				if (this->IsExit(id) == -1) {
					break;
				}
				cout << "输入的编号重复，请重新输入" << endl;
			}*/
			cout << "请输入第" << i + 1 << "位新职工编号" << endl;
			cin >> id;
			cout << "请输入第" << i + 1 << "位新职工姓名" << endl;
			cin >> name;

			cout << "请选择该职工岗位：" << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
			cin >> dpid;
			Worker* worker = NULL;
			//根据选择创建不同对象
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
			//将创建职工加入到数组中
			newSpace[this->EmpNum + i] = worker;
		}
		//释放原来的空间
		delete[] this->EmpArray;
		this->EmpArray = newSpace;
		//更新职工人数，确保之前的加1操作是正确的
		this->EmpNum = newSize;
		//提示添加成功
		cout << "成功添加" <<addNum<<"名员工" << endl;
		//进行一次排序
		this->SortByone();
		//保存到文件中
		this->Save();
		//把为空标记置为false
		this->FileIsEmpty = false;
	}
	else {
		cout << "输入有误" << endl;
	}
	//按任意键后，清屏回到上级目录
	system("pause");
	system("cls");
}

//保存文件
void WorkerManager::Save() {
	ofstream ofs;
	ofs.open(FILENAME, ios::out);

	for (int i = 0; i < this->EmpNum; i++) {
		ofs << this->EmpArray[i]->id << " "
			<< this->EmpArray[i]->name <<" "
			<< this->EmpArray[i]->dpid << endl;
	}

	//关闭文件
	ofs.close();
}
//统计文件中的人数
int WorkerManager::getEmpNum() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);//读文件的方式打开
	int id;
	string name;
	int dpid;
	int sum = 0;//统计人数
	while (ifs>>id && ifs>>name && ifs>>dpid)//因为文件一行中每个字段是用空格隔开的，所以这样子可以一下读一行数据
	{	
		sum++;
	}
	ifs.close();
	return sum;

}
//初始化员工
void WorkerManager::intEmp() {
	int id, dpid;
	string name;
	ifstream ifs;
	ifs.open(FILENAME, ios::in);//打开文件
	int index = 0;//数组下标
	while (ifs >> id && ifs >> name && ifs >> dpid) {
		Worker* worker = NULL;
		if (dpid == 1) {//普通员工
			worker = new Employee(id, name, dpid);
		}
		else if(dpid == 2) {//经理
			worker = new Manager(id, name, dpid);
		}
		else {//老板
			worker = new Boss(id, name, dpid);
		}
		this->EmpArray[index] = worker;
		index++;
	}
	ifs.close();
}
//显示员工信息
void WorkerManager::ShowEmp() {
	if (this->FileIsEmpty) {
		cout << "当前系统为空" << endl;
	}
	else {
		for (int i = 0; i < this->EmpNum; i++) {
			this->EmpArray[i]->ShowInfo();
		}
	}
	//按任意键清屏
	system("pause");
	system("cls");
}
//删除职工
void WorkerManager::Del() {
	//先判断文件是否为空
	if (this->FileIsEmpty) {
		cout << "文件当前为空" << endl;
	}
	else {
		//再判断要删除的编号是否存在
		int index;
		cout << "请输入要删除的职工编号：" << endl;
		int id;
		cin >> id;
		index = IsExit(id);
		if (index != -1) {
			//说明存在
			//对数组进行前移
			for (int i = index; i < this->EmpNum - 1; i++) {
				this->EmpArray[i] = this->EmpArray[i + 1];
			}
			this->EmpNum--;
			//更新文档
			this->Save();
			cout << "删除成功" << endl;
		}
		else {
			//说明不存在
			cout << "删除失败，不存在该职工" << endl;
		}
	}
	//按任意键清屏
	system("pause");
	system("cls");
}
//判断职工是否存在,存在就返回所在位置，否则就返回-1
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
//修改职工
void WorkerManager::ModEmp() {
	if (this->FileIsEmpty) {
		cout << "当前系统为空" << endl;
	}
	else {
		int id;
		cout << "请输入要修改的职工编号：" << endl;
		cin >> id;
		int ret = this->IsExit(id);
		if (ret != -1) {
			//存在
			//可以先删除原来位置的职工消息，后面再把新的加上去
			delete this->EmpArray[ret];
			int newid;
			string newname;
			int newdpid;
			cout << "请输入新的职工编号" << endl;
			cin >> newid;
			cout << "请输入职工姓名" << endl;
			cin >> newname;
			cout << "请输入新的岗位编号" << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
			cin >> newdpid;
			Worker* worker = NULL;
			//根据不同的岗位编号创建对象
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
			this->Save();//更新文档
			cout << "修改成功" << endl;
		}
		else {
			//不存在
			cout << "你要修改的职工不存在" << endl;
		}
	}
	//按任意键清屏
	system("pause");
	system("cls");
}
//查找职工
void WorkerManager::FindEmp() {
	//先判断当前系统是否为空
	if (this->FileIsEmpty) {
		cout << "当前系统为空" << endl;
		//按任意键清屏
		system("pause");
		system("cls");
		return;
	}
	int select;//存储用户选择
	cout << "请选择查询方式" << endl
		<< "1-按编号查询" << endl
		<< "2-按姓名查询" << endl;
	cin >> select;
	if (select == 1) {
		//1按照职工编号查询
		cout << "请输入你要查找的职工编号:" << endl;
		int id;
		cin >> id;
		int ret = IsExit(id);
		if (ret == -1) {
			cout << "你要查找的职工不存在" << endl;
		}
		else {
			this->EmpArray[ret]->ShowInfo();
			cout << "查找成功" << endl;
		}
	}
	else if (select == 2) {
		//按职工姓名查询
		cout << "请输入要查询的姓名" << endl;
		string name;
		cin >> name;
		bool flag = true;//判断是否存在
		for (int i = 0; i < this->EmpNum; i++) {
			if (this->EmpArray[i]->name == name) {
				flag = false;
				this->EmpArray[i]->ShowInfo();
			}
		}
		if (flag) {
			cout << "你要查找的职工不存在" << endl;
		}
	}
	else {
		cout << "选择有误" << endl;
	}
	//按任意键清屏
	system("pause");
	system("cls");
}
//排序，实现按编号升序排序或者降序排序
void WorkerManager::SortEmp() {
	cout << "请选择排序方式" << endl
		<< "1-按编号升序排序" << endl
		<< "2-按编号降序排序" << endl;
	int select;
	while (1) {//用来保证用户输入的选择是正确的
		cin >> select;
		if (select == 1 || select == 2) {
			break;
		}
		else {
			cout << "你的选择有误，请重新输入" << endl;
		}
	}
	this->SortFlag = select;
	this->SortByone();
	cout << "操作成功" << endl;
	this->Save();
	//按任意键清屏
	system("pause");
	system("cls");
}
//用于每次的排序
void WorkerManager::SortByone() {
	for (int i = 0; i < this->EmpNum; i++) {
		int minOrmax = i;
		for (int j = i + 1; j < this->EmpNum; j++) {
			if (this->SortFlag == 1) {
				//升序
				if (this->EmpArray[minOrmax]->id > this->EmpArray[j]->id) {
					minOrmax = j;
				}
			}
			else {
				//降序
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
//清空文件
void WorkerManager::CleanFile() {
	//对用户进行确认是否清空
	int ack = 0;
	cout << "是否清空文件？" << endl
		<< "1-确认" << endl
		<< "2-取消" << endl;
	cin >> ack;
	if (ack == 1) {
		ofstream ofs;
		ofs.open(FILENAME, ios::trunc);//打开方式为，如果文件存在先删除再重新创建
		ofs.close();
		//释放空间
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
		cout << "清空成功" << endl;
	}
	else {
		cout << "已取消" << endl;
	}
	//按任意键清屏
	system("pause");
	system("cls");
}
WorkerManager::~WorkerManager() {
	//释放空间
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