#pragma once
#include <string>
using namespace std;
class StudentInfo
{
public:
	//������������ȡΪ�ӿ�
	string IthPropertyToString(int i);
	int getPropertyCount();

	StudentInfo(void);
	~StudentInfo(void);
	string number;
	string name;
	int gender;
	string phone;
	string email;
	int age;
};
