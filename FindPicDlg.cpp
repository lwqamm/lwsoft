
// FindPicDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "FindPic.h"
#include "FindPicDlg.h"
#include "afxdialogex.h"
#include "atlcomcli.h"
//#include "obj.h"
//#include "../lwsoft1/lwsoft1_i.h"
#include "lwsoft.h"
#include "Shmem.h"

//#import "FirstATL.dll" no_namespace

#include "mybmp.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//定义创建内存映射的名字宏
#define TS_MAPVIEW_NAME	 "TSMAPVIEW:REMOTECTRL"
//#pragma comment(lib,"lwsoftpuls.tlb")
//#import "x64/Release/lwsoft.dll" no_namespace

Shmem g_mem;
HMODULE g_mod = 0;
HRESULT g_closee = 0;
// CFindPicDlg 对话框

bool ReadBMP(const char* file, PBITMAPS bmph, PBITINFO bmpi, unsigned char** data);

CFindPicDlg::CFindPicDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FINDPIC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFindPicDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CFindPicDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CFindPicDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CFindPicDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CFindPicDlg::OnBnClickedButton3)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON4, &CFindPicDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CFindPicDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CFindPicDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CFindPicDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CFindPicDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CFindPicDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON10, &CFindPicDlg::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON11, &CFindPicDlg::OnBnClickedButton11)
END_MESSAGE_MAP()


// CFindPicDlg 消息处理程序
//#pragma pack(1)
//typedef struct _Mycpu1
//{
//	//存4个寄存器值
//	DWORD eax = 0;
//	DWORD ebx = 0;
//	DWORD ecx = 0;
//	DWORD edx = 0;
//}Mycpu1, * PMycpu1, * LPMycpu1;
//#pragma pack(0)
lwsoft* g_lw = NULL;
typedef HRESULT(*SetDllPathA)(LPCTSTR aaf);
SetDllPathA SetDllPath = 0;

//窗口句柄_取进程pid
long GetWindowProcessId(long h)
{
	if (h <= 110)
	{
		return 0;
	}
	DWORD dword = 0;;
	::GetWindowThreadProcessId((HWND)h, &dword);
	return dword;
}

BOOL CFindPicDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	SetDlgItemText(EDIT2, "21");
	SetDlgItemText(EDIT3, "H:\\VS1\\FindPic\\res\\1234.bmp");
	SetDlgItemText(EDIT4, "000000");
	SetDlgItemText(EDIT5, "0.8");
	//HRESULT hr = CoInitialize(NULL); 
	//	LPARAM  lParam =(LPARAM)0x0249027A;
	//POINT p;//GetMessage() //GameMsg=(LPMSG)lParam;//获取游戏内部PeekMessage中的MSG指针

	//p.x = GET_X_LPARAM(lParam);
	//p.y = GET_Y_LPARAM(lParam);
	//if (SUCCEEDED(hr))
	//{
	//	g_mod = LoadLibrary("lwReg.dll");
	//	SetDllPath = (SetDllPathA)GetProcAddress(g_mod, "SetDllPathA");
	//	//int eroo = GetLastError();
	//	if (SetDllPath)
	//	{
	//		if (sizeof(LPVOID)==8)
	//		{
	//			bool g_closee = SetDllPath("H:\\VS1\\FindPic\\x64\\Release\\lwsoft.dll");
	//		}
	//		else
	//		{
	//			bool g_closee = SetDllPath("H:\\VS1\\FindPic\\Release\\lwsoft.dll");
	//		}
	//		//PeekMessage
	//		//SendMessage
	//		g_lw = new lwsoft;
	//
	//	if (g_lw&& g_lw->Ver()!="")
	//	{
	//		g_lw->BindWindow(264276,0);
	//		g_lw->SetDict("H:\\VS1\\FindPic\\res\\123.txt");
	//		g_lw->SetPath("H:\\VS1\\FindPic\\res");
	//	}
	//	
	//		
	//	
	//}
	//}

	long hwnd = (long)394790;
	DWORD t_Pid = GetWindowProcessId(hwnd);
	if (!t_Pid)
	{
		return TRUE;
	}
	char pszMapName[MAX_PATH] = { 0 };
	sprintf(pszMapName, "%s%d", TS_MAPVIEW_NAME, t_Pid);
	g_mem.Create(pszMapName, pszMapName, sizeof(HookData));
	if (!g_mem.GetBuffer())
	{
		return false;
	}

	
	PHookData pdata = (PHookData)g_mem.GetBuffer();
	pdata->m_hwnd = hwnd;
	pdata->m_pid = t_Pid;


	
	/*LoadLibraryA("H:\\VS1\\FindPic\\Release\\Hook.dll");
	return TRUE;*/
	HANDLE  hadle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pdata->m_pid);
	if (!hadle)
	{
		return FALSE;
	}
	sprintf(pszMapName, "%s","H:\\VS1\\FindPic\\Release\\Hook.dll");
	int strL = strlen(pszMapName);
	void* pRemoteAdrr = VirtualAllocEx(hadle, NULL, strL, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	if (pRemoteAdrr == NULL)
	{
		//AfxMessageBox("在目标进程申请内存失败！");
		CloseHandle(hadle);
		return FALSE;
	}

	if (!WriteProcessMemory(hadle, pRemoteAdrr, pszMapName, strL, NULL))
	{
		//AfxMessageBox("在目标进程内存写DLL路径失败！");
	//	g_dlg3->SetAsmShowText("在目标进程内存写DLL路径失败！");
		CloseHandle(hadle);
		return FALSE;
	}

	DWORD dwpid = 0;
	HANDLE the1 = CreateRemoteThread(hadle, NULL, 0, (LPTHREAD_START_ROUTINE)LoadLibraryA, pRemoteAdrr, 0, &dwpid);
	WaitForSingleObject(the1, INFINITE);
	//GetExitCodeThread(the1, &g_undll);
	if (VirtualFreeEx(hadle, pRemoteAdrr, 0, MEM_RELEASE))
	{
		dwpid = dwpid;
	}
	CloseHandle(the1);
	CloseHandle(hadle);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CFindPicDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CFindPicDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void IntToHex(char* str,UCHAR ch)
{
	if (ch<=0xF)
	{
		str[0] = '0';
		if (ch>=0&&ch<=9)
		{
			str[1] = ch + '0';
			return;
		}
		else if (ch >= 0xA && ch <= 0xF)
		{
			str[1] = ch + 'A'-10;
			return;
		}
	}

		char car = ch / 0x10;
		if (car >= 0 && car <= 9)
		{
			str[0] = car + '0';
			
		}
		else if (car >= 0xA && car <= 0xF)
		{
			str[0] = car + 'A' - 10;
			
		}

		ch = ch % 0x10;
		if (ch<0)
		{
			ch = 0;
		}
		if (ch >= 0 && ch <= 9)
		{
			str[1] = ch + '0';
			
		}
		else if (ch >= 0xA && ch <= 0xF)
		{
			str[1] = ch + 'A' - 10;
			
		}

}

void CFindPicDlg::OnBnClickedButton1()
{

	// TODO: 在此添加控件通知处理程序代码

//	SetDllPath("E:\\VIP Tools\\ABC\\大漠类库生成工具V23\\dm.dll",0);

	CString str;
	GetDlgItemText(EDIT3, str);

	int x = 0, y = 0;
	if (g_lw)
	{
		//g_lw->FindPic(731, 144, 43, 16, str.GetBuffer(), (char*)"050505",0.8,&x,&y);
	
		//str.Format("%d,%d", x, y);
		//	SetDlgItemText(EDIT1, str);
		//g_lw->MoveTo(100,200);
		g_lw->SetWindowState(723334, 1);
		g_lw->Delay(1500);
		//g_lw->SendString(265850,"lwqwdzt");
		g_lw->Delay(6000);
		for (size_t i = 0; i < 10; i++)
		{

			g_lw->Delay(1000);
		}

		//g_lw->SetWindowState(265850, 1);
		return;
	}
	
	
}

void CFindPicDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str, str1, str2, str3;
	GetDlgItemText(EDIT2, str);
	GetDlgItemText(EDIT3, str1);
	GetDlgItemText(EDIT4, str2);
	GetDlgItemText(EDIT5, str3);
	int x = 0, y = 0;
	if (g_lw)
	{
		g_lw->UnBindWindow();
			return;
	}
		
	
}


void CFindPicDlg::OnBnClickedButton3()
{
	
	AfxMessageBox("大家好");
	return;
	// TODO: 在此添加控件通知处理程序代码
	//g_lw->SetWindowState(265850, 1);
	g_lw->SendString(265850, "Lwqamm12580");
	//g_lw->SetWindowState(265850, 1);

	return;
	CString str,str2;

	GetDlgItemText(EDIT2, str);
	GetDlgItemText(EDIT3, str2);
	//GetDlgItemText(EDIT5, str3);
	int x = 0, y = 0;
	if (g_lw)
	{
		
		//https://blog.51cto.com/u_15127623/3581647
		//MessageBox("123");
		int type=StrToInt(str);
		switch (type)
		{
		case 0:
		{
			str.Format("%s", g_lw->GetDiskSerial(0));
			break;
		}
		case 1:
		{
			str.Format("%d", g_lw->GetHDiskCode());
			break;
		}
		case 2:
		{
			str.Format("%s", g_lw->GetCpuCode());
			break;
		}
		case 3:
		{
			str.Format("%I64d", g_lw->GetMainBoardInfoByCmd());
			break;
		}
		case 4:
		{
			str.Format("%s", g_lw->GetMachineCode());
			break;
		}
		case 5:
		{
			str.Format("%s", g_lw->GetDisplayInfo());
			break;
		}
		case 6:
		{
			str.Format("%s", g_lw->GetMachineCodeNoMac());
			break;
		}
		case 7:
		{
			str.Format("%s", g_lw->GetNetTime());
			break;
		}
		case 8:
		{
			str.Format("%s", g_lw->GetNetTimeByIp(str2.GetBuffer()));
			str2.ReleaseBuffer();
			break;
		}
		case 9:
		{
			str.Format("%d", g_lw->GetOsBuildNumber());

			break;
		}
		case 10:
		{
			str.Format("%d", g_lw->GetOsType());

			break;
		}
		case 11:
		{
			str.Format("%d", g_lw->IsSurrpotVt());

			break;
		}
		case 12:
		{
			str.Format("%d", g_lw->GetScreenDepth());

			break;
		}
		case 13:
		{
			str.Format("%d", g_lw->GetScreenHeight());

			break;
		}
		case 14:
		{
			str.Format("%d", g_lw->GetScreenWidth());

			break;
		}
		case 15:
		{
			str.Format("%d", g_lw->SetScreen(800,600));

			break;
		}
		case 16:
		{
			str.Format("%d", g_lw->GetLastError());

			break;
		}
		case 17:
		{
			str.Format("%d", g_lw->SetScreen(1920, 1080));

			break;
		}
		case 18:
		{
			str.Format("%d", g_lw->SetDict((TCHAR*)"H:\\VS1\\FindPic\\res\\123.txt"));

			break;
		}
		case 19:
		{
			g_lw->FindStr(0, 0, 2000, 2000, (TCHAR*)"玩", (TCHAR*)"fffefe-202020", 1.0, &x, &y);
			str.Format("%d,%d",x,y);

			break;
		}
		case 20:
		{
			str = g_lw->FindStrEx(0, 0, 2000, 2000, (TCHAR*)"玩", (TCHAR*)"fffefe-202020", 1.0);
			

			break;
		}
		case 21:
		{
			str = g_lw->Ocr(714, 32, 68, 127, (TCHAR*)"fbff00-202020", 1.0);


			break;
		}
		case 22:
		{
			str = g_lw->Ocr(28, 61, 35, 20, (TCHAR*)"10100C-0A0A08|0D0D0A-0D0D0A", 1.0);


			break;
		}
		str = "";
		default:
			break;
		}

		
		
    //g_lw->RunApp("F:\\Program Files (x86)\\刀剑Online\\BoOnline.exe");
	SetDlgItemText(EDIT1,str );
	return;
    }
	//SetDlgItemText(EDIT1, "-1");
}


void CFindPicDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CoFreeUnusedLibraries();
	CoUninitialize();
	
		CoRevokeClassObject(g_closee);
		FreeLibrary(g_mod);
	CDialogEx::OnClose();
}


void CFindPicDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	CString  x, y;
	GetDlgItemText(EDIT6, x);
	GetDlgItemText(EDIT7, y);
	if (g_lw)
	{
		
		SetDlgItemText(EDIT1, g_lw->GetColor(StrToInt(x), StrToInt(y)));
	}

	if (g_lw)
	{
		g_lw->SetPath((TCHAR*)"D:\\123.BMP");
		
	}
	


}


void CFindPicDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	//CString  x, y;
	//GetDlgItemText(EDIT6, x);
	//GetDlgItemText(EDIT7, y);
	//if (g_lw)
	//{
	//	long len = g_lw->GetColorNum(StrToInt(x), StrToInt(y), 24, 14, "393939-020202", 1);
	//	x.Format("颜色数量=%d个", len);
	//	SetDlgItemText(EDIT1,x );
	//}
	//INPUT inputs = { 0 };
	//inputs.type = INPUT_MOUSE;
	//inputs.mi.dwFlags = MOUSEEVENTF_MOVE;
	//inputs.mi.dx = 100;
	//inputs.mi.dy = 100;
	//inputs.mi.dwExtraInfo = GetMessageExtraInfo();
	//SendInput(1, &inputs, sizeof(INPUT));
	SetCursorPos(100,100);
}


void CFindPicDlg::OnBnClickedButton6()
{
	g_lw->LeftClick();

	return;
	// TODO: 在此添加控件通知处理程序代码
	CDC* dc = GetDC();
	CDC  pdc;
	pdc.CreateCompatibleDC(dc);
	HBITMAP HEditBmp = CreateCompatibleBitmap(dc->m_hDC, 255, 255); //内存编辑框位图
	HBITMAP pOHEditmap = (HBITMAP)::SelectObject(pdc, HEditBmp);        //内存画编辑框位图

	RECT rct;
	rct.left = 0;
	rct.top = 0;
	rct.right =255;
	rct.bottom = 255;
	pdc.FillSolidRect( &rct, RGB(0xFF, 0xFF, 0xFF));
	for (size_t i = 0; i < 255; i++)
	{
		CPen pen(PS_SOLID,1,RGB(i,i,i));
		HGDIOBJ Obpen =pdc.SelectObject(pen);
		pdc.MoveTo(i, 0);
		pdc.LineTo(i, 255);
		pdc.SelectObject(Obpen);
		pen.DeleteObject();

	}
	CImage age;
    age.Attach(HEditBmp);
    age.Save("H:\\VS1\\FindPic\\res\\123.bmp");
    age.Destroy();
	DeleteObject(HEditBmp);
	DeleteDC(pdc);


}


void CFindPicDlg::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
	if (g_lw)
	{
		//int ret=g_lw->IsDisplayDead(733, 146, 43, 12,5);
		//if (ret)
		//{
		//	SetDlgItemText(EDIT1, "卡屏了！");
		//	return;
		//}
		//SetDlgItemText(EDIT1, "没卡屏");
		g_lw->SetWindowState(265850, 1);
		::SendMessageA((HWND)265850, WM_KEYUP, VK_TAB, 0);
		g_lw->SetWindowState(265850, 1);
	}
}


void CFindPicDlg::OnBnClickedButton8()
{
	// TODO: 在此添加控件通知处理程序代码
	CString  hw, sim;
	if (g_lw)
	{
		GetDlgItemText(EDIT2, hw);
		GetDlgItemText(EDIT5, sim);
		g_lw->SetWindowState(StrToInt(hw), StrToInt(sim));
	}
}


void CFindPicDlg::OnBnClickedButton9()
{
	// TODO: 在此添加控件通知处理程序代码
	CString  str;
	if (g_lw)
	{
		int x=100, y=150;
		g_lw->ScreenToClient(132716,&x,&y);
		str.Format("%d,%d", x, y);
		SetDlgItemText(EDIT1, str);
	}
}


void CFindPicDlg::OnBnClickedButton10()
{
	// TODO: 在此添加控件通知处理程序代码
	CString  hw, sim;
	if (g_lw)
	{
		GetDlgItemText(EDIT2, hw);
		GetDlgItemText(EDIT5, sim);
		g_lw->SetWindowText(StrToInt(hw),sim.GetBuffer());

	}
}


void CFindPicDlg::OnBnClickedButton11()
{
	// TODO: 在此添加控件通知处理程序代码
	CString  hw;
	if (g_lw)
	{

	
		GetDlgItemText(EDIT5, hw);
		
		g_lw->ExitOs(StrToInt(hw));
		

	}


	//LARGE_INTEGER start, end;
	//LARGE_INTEGER pers;
	//QueryPerformanceFrequency(&pers);
	//double dff = pers.QuadPart;
	//QueryPerformanceCounter(&start);
	//
	//Sleep(2805);
	//QueryPerformanceCounter(&end);
	//hw.Format("%I64f", (end.QuadPart - start.QuadPart) * 1000 / dff);
	//SetDlgItemText(EDIT1, hw);
}
