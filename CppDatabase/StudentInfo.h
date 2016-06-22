#pragma once
#include <string>
using namespace std;
class StudentInfo
{
public:
	//这两个可以提取为接口
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
