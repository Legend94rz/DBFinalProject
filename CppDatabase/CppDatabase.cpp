#include <iostream>
#include "ListView.h"
#include <windows.h>
#include <commctrl.h>
#include "resource.h"
#include "DAL.h"
#include "StudentInfo.h"
#include <string>
#pragma comment(linker, "/MANIFESTDEPENDENCY:\" type='Win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595B64144CCF1DF'\" ")
using namespace std;
HINSTANCE hInst;
HWND hwnd1;
StudentInfo getStudentInfo()
{
	char edit1[20], edit2[20], edit3[20], edit4[20], edit5[20], edit6[20];
	StudentInfo stu;
	GetWindowText(GetDlgItem(hwnd1, IDC_EDIT1), edit1, 20);
	GetWindowText(GetDlgItem(hwnd1, IDC_EDIT2), edit2, 20);
	GetWindowText(GetDlgItem(hwnd1, IDC_EDIT3), edit3, 20);
	GetWindowText(GetDlgItem(hwnd1, IDC_EDIT4), edit4, 20);
	GetWindowText(GetDlgItem(hwnd1, IDC_EDIT5), edit5, 20);
	GetWindowText(GetDlgItem(hwnd1, IDC_EDIT6), edit6, 20);

	stu.number = edit1;
	stu.name = edit2;
	if (edit3[0] != 0)
	{
		if ((edit3[0] == '0' || edit3[0] == '1') && edit3[1] == 0)
			stu.gender = atoi(edit3);
		else
		{
			MessageBox(hwnd1, "性别只能为0或1", "输入出错", MB_OK);
			return StudentInfo();
		}
	}
	stu.phone = edit4;
	stu.email = edit5;
	if (edit6[0] != 0)
	{
		for (int i = 0; edit6[i] != 0; i++)
		{
			if (edit6[i] > '9' || edit6[i] < '0')
			{
				MessageBox(hwnd1, "年龄只能为数字", "输入出错", MB_OK);
				return StudentInfo();
			}
		}
		stu.age = atoi(edit6);
	}

	return stu;
}
string genFilter()
{
	char edit[20], edit1[20], edit2[20], edit3[20], edit4[20], edit5[20], edit6[20];
	StudentInfo stu;
	string filter = "";
	GetWindowText(GetDlgItem(hwnd1, IDC_EDIT1), edit1, 20);
	GetWindowText(GetDlgItem(hwnd1, IDC_EDIT2), edit2, 20);
	GetWindowText(GetDlgItem(hwnd1, IDC_EDIT3), edit3, 20);
	GetWindowText(GetDlgItem(hwnd1, IDC_EDIT4), edit4, 20);
	GetWindowText(GetDlgItem(hwnd1, IDC_EDIT5), edit5, 20);
	GetWindowText(GetDlgItem(hwnd1, IDC_EDIT6), edit6, 20);

	for (int i = 0; i < 6; i++)
	{
		GetWindowText(GetDlgItem(hwnd1, IDC_EDIT1 + i), edit, 20);
		if (edit[0] != 0)
		{
			switch (i)
			{
			case 0:
			{
				if (filter == "")
					filter = filter + " SNO='" + edit + "' ";
				else
					filter = filter + "AND SNO='" + edit + "' ";
				break;
			}
			case 1:
			{
				if (filter == "")
					filter = filter + " NAME='" + edit + "' ";
				else
					filter = filter + "AND NAME='" + edit + "' ";
				break;
			}
			case 2:
			{
				if ((edit[0] == '0' || edit[0] == '1') && edit[1] == 0)
				{
					if (filter == "")
						filter = filter + " GENDER=" + edit + " ";
					else
						filter = filter + "AND GENDER=" + edit + " ";
				}
				else
				{
					MessageBox(hwnd1, "性别只能为0或1", "输入出错", MB_OK);
					return "";
				}
				break;
			}
			case 3:
			{
				if (filter == "")
					filter = filter + " PHONE='" + edit + "' ";
				else
					filter = filter + "AND PHONE='" + edit + "' ";
				break;
			}
			case 4:
			{
				if (filter == "")
					filter = filter + " EMAIL='" + edit + "' ";
				else
					filter = filter + "AND EMAIL='" + edit + "' ";
				break;
			}
			case 5:
			{
				for (int j = 0; edit[j] != 0; j++)
				{
					if (edit6[j] > '9' || edit6[j] < '0')
					{
						MessageBox(hwnd1, "年龄只能为数字", "输入出错", MB_OK);
						return "";
					}
				}
				if (filter == "")
					filter = filter + " AGE=" + edit;
				else
					filter = filter + "AND AGE=" + edit;
				break;
			}
			}
		}
	}
	return filter;
}
INT_PTR CALLBACK DlgProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	int ctrlID;
	static ListView* listView;
	static DAL* dal;
	switch(uMsg)
	{
		case WM_INITDIALOG:
			listView = new ListView(0x100,hwnd,WS_CHILD|WS_VISIBLE|LVS_SHOWSELALWAYS|LVS_REPORT,15,40,850,480,hInst);
			listView->AddColumn("Number",0);
			listView->AddColumn("Name",1);
			listView->AddColumn("Gender",2);
			listView->AddColumn("Phone",3);
			listView->AddColumn("Email",4);
			listView->AddColumn("Age",5);
			//TODO: 修改用户名、密码、数据库名
			dal=new DAL("scott","tiger","orcl");
			hwnd1 = hwnd;
		return TRUE;
		case WM_COMMAND:
			ctrlID=LOWORD(wParam);
			switch(ctrlID)
			{
				//TODO: 检查数据库操作的结果是否成功
				case IDC_BTNADD:
					listView->ClearContent();
					dal->Add(getStudentInfo());
					listView->Fill(dal->Get(""));//全部
				break;
				case IDC_BTNMODIFY:
					listView->ClearContent();
					dal->Update(getStudentInfo());
					listView->Fill(dal->Get(""));//全部
				break;
				case IDC_BTNSEL:
					listView->ClearContent();
					listView->Fill(dal->Get(genFilter()));
				break;
				case IDC_BTNDEL:
					listView->ClearContent();
					dal->Delete(genFilter());
					listView->Fill(dal->Get(""));//全部
				break;
			}
		return TRUE;
		case WM_CLOSE:
			EndDialog(hwnd,0);
		break;
	}
	return FALSE;
}

int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
	hInst = hInstance;
	DialogBox(NULL,MAKEINTRESOURCE(IDD_DLGMAIN),NULL,DlgProc);
	return 0;
}
