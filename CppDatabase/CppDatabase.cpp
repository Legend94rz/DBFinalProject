#include <iostream>
#include "ListView.h"
#include <windows.h>
#include <commctrl.h>
#include "resource.h"
#include "DAL.h"
#include "StudentInfo.h"
#pragma comment(linker, "/MANIFESTDEPENDENCY:\" type='Win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595B64144CCF1DF'\" ")
using namespace std;
HINSTANCE hInst;
StudentInfo getStudentInfo()
{
	//TODO: 从UI上读取数据构造StudentInfo
	return StudentInfo();
}
//会用到GetDlgItemText
string genFilter()
{
	//Todo: 从UI上构造过滤条件。注意处理条件格式不对的情况
	return "";
}
INT CALLBACK DlgProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
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
		return TRUE;
		case WM_COMMAND:
			ctrlID=LOWORD(wParam);
			switch(ctrlID)
			{
				//TODO: 检查数据库操作的结果是否成功
				case IDC_BTNADD:
					dal->Add(getStudentInfo());
				break;
				case IDC_BTNMODIFY:
					dal->Update(getStudentInfo());
				break;
				case IDC_BTNSEL:
					dal->Get(genFilter());
				break;
				case IDC_BTNDEL:
					dal->Delete(genFilter());
				break;
			}
			listView->ClearContent();
			listView->Fill(dal->Get(""));//全部
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
