#include"Boss.h"
Boss::Boss(int id, string name, int dpid) {
	this->id = id;
	this->name = name;
	this->dpid = dpid;
}
//��ʾ������Ϣ
void Boss::ShowInfo() {
	cout <<std::left<<setw(7) << "ְ����ţ�" << this->id << "  "
		<< std::left << setw(7) << "ְ��������" << this->name << "  "
		<< std::left << setw(7) << "��λ��" << this->GetDeptName() << "  "
		<< std::left << setw(20) << "��λְ�𣺹���˾��������" << endl;
}

//��ȡ��λ����
string Boss::GetDeptName() {
	return string("�ܲ�");
}