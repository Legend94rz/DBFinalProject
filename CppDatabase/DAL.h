#pragma once
#include "StudentInfo.h"
#include <assert.h>
#include <vector>
using namespace std;

class DAL
{
public:
	DAL(char* usr,char* pswd,char* serv);
	~DAL(void);
	
	bool Add(StudentInfo stu);
	bool Update(StudentInfo stu);
	vector<StudentInfo> Get(string filter);
	int Delete(string filter);
};
