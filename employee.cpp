#include"employee.h"


Employee::Employee(int id, string name, int dpid) {
	this->id = id;
	this->name = name;
	this->dpid = dpid;
}
//��ʾ������Ϣ
void Employee::ShowInfo() {
	cout << std::left << setw(7) << "ְ����ţ�" << this->id << "  "
		<< std::left << setw(7) << "ְ��������" << this->name << "  "
		<< std::left << setw(7) << "��λ��" << this->GetDeptName() << "  "
		<< std::left << setw(20) << "��λְ����ɾ�����������" << endl;
}

//��ȡ��λ����
string Employee::GetDeptName() {
	return string("Ա��");
}