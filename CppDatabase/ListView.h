#pragma once
#include <windows.h>
#include <tchar.h>
#include <commctrl.h>
#include <string>
#include <vector>
#include "StudentInfo.h"
using namespace std;
class ListView
{
public:
	HWND handle;
	ListView(INT id,HWND parent,DWORD dwStyle,UINT x, UINT y,UINT width,UINT height,HINSTANCE hInst);
	~ListView(void);
	void ClearContent();
	void AddColumn(char* colName,int i);
	void Fill(vector<StudentInfo>& v);
};
