#include"manager.h"

Manager::Manager(int id, string name, int dpid) {
	this->id = id;
	this->name = name;
	this->dpid = dpid;
}
//��ʾ������Ϣ
void Manager::ShowInfo() {
	cout << std::left << setw(7) << "ְ����ţ�" << this->id<<"  "
		<< std::left << setw(7) << "ְ��������" << this->name << "  "
		<< std::left << setw(7) << "��λ��" << this->GetDeptName() << "  "
		<< std::left << setw(20) << "��λְ�� ����ϰ彻�������񣬲��ҹ���Ա��" << endl;
}

//��ȡ��λ����
string Manager::GetDeptName() {
	return string("����");
}