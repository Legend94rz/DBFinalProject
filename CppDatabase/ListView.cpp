#include "ListView.h"
ListView::ListView(INT id,HWND parent,DWORD dwStyle,UINT x, UINT y,UINT width,UINT height,HINSTANCE hInst)
{
	handle=CreateWindow(TEXT("SysListView32"),NULL,dwStyle,x,y,width,height,parent,(HMENU)id,hInst,0);
	SendMessage(handle,LVM_SETEXTENDEDLISTVIEWSTYLE,0,LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_DOUBLEBUFFER);
}

ListView::~ListView(void)
{
}
void ListView::ClearContent()
{
	SendMessage(handle,LVM_DELETEALLITEMS,0,0);
}
void ListView::AddColumn(char* colName,int i)
{
	LVCOLUMN lvc;
	lvc.mask = LVCF_FMT|LVCF_SUBITEM|LVCF_WIDTH|LVCF_TEXT;
	lvc.fmt=LVCFMT_LEFT;
	lvc.cx=140;
	lvc.pszText=colName;
	lvc.iSubItem=i;
	SendMessage(handle,LVM_INSERTCOLUMN,i,(LPARAM)&lvc);
}
void ListView::Fill(vector<StudentInfo>& v)
{
	LVITEM lvi;
	lvi.mask = LVIF_TEXT;
	for(size_t i=0;i<v.size();i++)
	{
		lvi.iItem = i;
		for(int j=0;j<v[i].getPropertyCount();j++)
		{
			lvi.iSubItem = j;
			char buf[255];
			strncpy_s(buf,v[i].IthPropertyToString(j).c_str(),255);
			lvi.pszText=buf;
			SendMessage(handle,LVM_INSERTITEM,0,(LPARAM)&lvi);
			SendMessage(handle,LVM_SETITEM,0,(LPARAM)&lvi);
		}
	}
}