#include "StudentInfo.h"

StudentInfo::StudentInfo(void)
{
}

StudentInfo::~StudentInfo(void)
{
}
string StudentInfo::IthPropertyToString(int i)
{
	switch(i)
	{
		case 0:return number;
		case 1:return name;
		case 2:return gender?"male":"female";
		case 3:return phone;
		case 4:return email;
		case 5:
		{
			char buf[255];
			_ltoa_s(age,buf,255,10);
			return buf;
		}
		
	}
	return "Not Valid.";
}
int StudentInfo::getPropertyCount()
{
	return 6;
}