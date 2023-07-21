#pragma once

#ifndef __INCLUDE_OBJ_H__I
#define __INCLUDE_OBJ_H__I
//���崴���ڴ�ӳ������ֺ�
#define TS_MAPVIEW_NAME	 "TSMAPVIEW:REMOTECTRL"
#define LW_MESSAGE        (WM_USER+2000)
//����������
#define  LW_MOVETO      (LW_MESSAGE+1)   //������ƶ���Ŀ�ĵ�(x,y)
#define  LW_LEFTCLICK   (LW_MESSAGE+2)   //����������

#include <time.h>
#include "Shmem.h"
#pragma warning(disable:4996)

#pragma pack(push,1)
typedef struct _IDSECTOR
{
	WORD wGenConfig = 0;
	WORD wNumCyls = 0;
	WORD wReserved = 0;
	WORD wNumHeads = 0;
	WORD wBytesPerTrack = 0;
	WORD wBytesPerSector = 0;
	WORD wSectorsPerTrack = 0;
	WORD wVendorUnique[3] ={0};
	char sSerialNumber[20] = { 0 };
	WORD wBufferType = 0;
	WORD wBufferSize = 0;
	WORD wECCSize = 0;
	char sFirmwareRev[8] = { 0 };
	char sModelNumber[40] = { 0 };
	WORD wMoreVendorUnique = 0;
	WORD wDoubleWordIO = 0;
	WORD wCapabilities = 0;
	WORD wReserved1 = 0;
	WORD wPIOTiming = 0;
	WORD wDMATiming = 0;
	WORD wBS = 0;
	WORD wNumCurrentCyls = 0;
	WORD wNumCurrentHeads = 0;
	WORD wNumCurrentSectorsPerTrack = 0;
	DWORD ulCurrentSectorCapacity = 0;
	WORD wMultSectorStuff = 0;
	DWORD ulTotalAddressableSectors = 0;
	WORD wSingleWordDMA = 0;
	WORD wMultiWordDMA = 0;
	char bReserved[128] = { 0 };
}IDSECTOR,*PIDSECTOR,*LPIDSECTOR;

typedef struct _SRB_IO_CONTROL
{
	DWORD HeaderLength = 0;
	char  Signature[8] = { 0 };
	DWORD Timeout = 0;
	DWORD ControlCode = 0;
	DWORD ReturnCode = 0;
	DWORD Length = 0;
	DWORD cBufferSize = 0;
	char  bFeaturesReg = 0;
	char  bSectorCountReg = 0;
	char  bSectorNumberReg = 0;
	char  bCylLowReg = 0;
	char  bCylHighReg = 0;
	char  bDriveHeadReg = 0;
	char  bCommandReg = 0;
	char  bReserved1 = 0;
	char  bDriveNumber = 0;
	char  bReserved[3] = { 0 };
	DWORD  dwReserved[4] = {0};
	char  bBuffer[1] = { 0 };
}SRB_IO_CONTROL,*PSRB_IO_CONTROL,*LPSRB_IO_CONTROL;

#include "pch.h"
typedef struct _MyRGB
{
	UCHAR R = 0;
	UCHAR G = 0;
	UCHAR B = 0;
	UCHAR Rp = 0;
	UCHAR Gp = 0;
	UCHAR Bp = 0;
	/*bool operator == (const _MyRGB& rhs)
	{
		return ((R == rhs.R) && (G == rhs.G) && (B == rhs.B));
	}*/
	void operator = (const _MyRGB& rhs)
	{
		R = rhs.R;
		G = rhs.G;
		B = rhs.B;
		Rp = rhs.Rp;
		Gp = rhs.Gp;
		Bp = rhs.Bp;
		return;
	}
}MyRGB, * PMyRGB, * LPMyRGB;

//#define  LPCSTR  LPCSTR

typedef class _MyRGBARR
{
public:
	_MyRGBARR()
	{
	}

	_MyRGBARR(const char* strp)
	{
		AddArr(strp);
	}

	~_MyRGBARR()
	{
		ClearArr();
	}
	int GetArrLen()//���������С
	{
		return len;
	}
	BOOL AddArr(PMyRGB p)
	{
		if (!p)
		{
			return FALSE;
		}
		if (len == 0)
		{
			len++;
			arr = new MyRGB;
			*arr = *p;
			return len;
		}
		len++;
		arrbak = new MyRGB[len];
		for (size_t i = 0; i < len; i++)
		{
			if (i == len - 1)
			{
				arrbak[i] = *p;
				break;
			}
			arrbak[i] = arr[i];
		}
		delete[] arr;
		arr = 0;
		arr = arrbak;
		arrbak = 0;
		return len;
	}
	//����һ������ָ��
	PMyRGB GetDxArr(int dx)
	{
		if (len == 0 || dx<0 || dx>len - 1)
		{
			return 0;
		}
		return &arr[dx];
	}

	//�������
	void ClearArr()
	{
		if (arr)
		{
			delete[] arr;
			arr = 0;
		}
		if (arrbak)
		{
			delete[] arrbak;
			arrbak = 0;
		}
		len = 0;
	}

	void operator = (const _MyRGBARR& rhs)
	{
		if (rhs.len == 0)
		{
			return;
		}
		if (len)
		{
			ClearArr();
		}
		len = rhs.len;
		arr = new MyRGB[len];
		for (size_t i = 0; i < len; i++)
		{
			arr[i] = rhs.arr[i];
		}
		delete[] rhs.arr;
		return;
	}

	//ֱ������ַ���
	BOOL operator = (const char* strp)
	{
		return AddArr(strp);
	}
	BOOL AddArr(const char* strp)
	{
		if ((ULONG_PTR)strp <= 0x10000)
		{
			return FALSE;
		}
		int stlen = strlen(strp);
		if (len)
		{
			ClearArr();
		}
		char tch[20] = { 0 };
		for (size_t i = 0; i < stlen; i++)
		{
			if (strp[i] != '|' && strp[i] != ' ' && strp[i] != ' ')
			{
				tch[strlen(tch)] = strp[i];
			}
			if (strp[i] == '|' || i == stlen - 1)
			{
				if (strlen(tch) != 13)
				{
					ClearArr();
					return FALSE;
				}
				char t_ch[3] = { 0 };
				MyRGB tmy = { 0 };
				memcpy(t_ch, tch, 2);
				tmy.R = HexToInt(t_ch);

				memset(t_ch, 0, 3);
				memcpy(t_ch, tch + 2, 2);
				tmy.G = HexToInt(t_ch);

				memset(t_ch, 0, 3);
				memcpy(t_ch, tch + 4, 2);
				tmy.B = HexToInt(t_ch);

				memset(t_ch, 0, 3);
				memcpy(t_ch, tch + 7, 2);
				tmy.Rp = HexToInt(t_ch);

				memset(t_ch, 0, 3);
				memcpy(t_ch, tch + 9, 2);
				tmy.Gp = HexToInt(t_ch);

				memset(t_ch, 0, 3);
				memcpy(t_ch, tch + 11, 2);
				tmy.Bp = HexToInt(t_ch);
				AddArr(&tmy);
				memset(tch, 0, sizeof(tch));
				memset(t_ch, 0, sizeof(t_ch));
			}
		}

		return len;
	}

private:
	int len = 0;             //�����С
	PMyRGB   arr = 0;        //��������
	PMyRGB   arrbak = 0;	 //�������ݱ���


}MyRGBARR, * PMyRGBARR, * LPMyRGBARR, * NPMyRGBARR;

typedef struct _MyPid
{
public:
	void operator = (const _MyPid& rhs)
	{
		Clear();
		len = rhs.len;
		arr = new long[len];
		for (size_t i = 0; i < len; i++)
		{
			arr[i] = rhs.arr[i];
		}
		return;
	}
	void operator = (const int& rhs)
	{
		AddPid(rhs);
		return;
	}

	long SetPid(int dx, int vae1)
	{
		if (dx<0 || dx>len - 1)
		{
			return 0;
		}
		arr[dx] = vae1;
	}

	long AddPid(int vae1)
	{
		if (len == 0)
		{
			arr = new long;
			*arr = vae1;
			len++;
			return len;
		}

		for (size_t i = 0; i < len; i++)
		{
			if (vae1 == arr[i])
			{
				return 0;
			}
		}
		len++;
		arrbak = new long[len];
		for (size_t i = 0; i < len; i++)
		{
			if (i == len - 1)
			{
				arrbak[i] = vae1;
				continue;
			}
			arrbak[i] = arr[i];
		}

		delete[] arr;
		arr = arrbak;
		arrbak = 0;
		return len;
	}

	long GetPid(int dx)
	{
		if (dx<0 || dx>len - 1)
		{
			return 0;
		}
		return arr[dx];
	}

	void Clear()
	{
		if (arr)
		{
			delete[] arr;
			arr = 0;
		}
		if (arrbak)
		{
			delete[] arrbak;
			arrbak = 0;
		}
		len = 0;
	}

	int GetPidLen()
	{
		return len;
	}
	inline  __int64  systemtime_to_time_t(SYSTEMTIME  st)
	{

		struct tm gm = { st.wSecond, st.wMinute, st.wHour, st.wDay, st.wMonth - 1, st.wYear - 1900, st.wDayOfWeek, 0, 0 };
		ULONGLONG  lLMinllis = mktime(&gm);
		//https://blog.csdn.net/hellokandy/article/details/51329446
		//https://blog.csdn.net/hellokandy/article/details/51329183
		return  (lLMinllis);  //�˴����غ��룬���ø����Լ��ĸ�ʽ��Ҫ����ת������ʱ����
	}

	//ȡ��������ʱ��
	long GetPidTime(int pid, PSYSTEMTIME p)
	{
		if (!p)
		{
			return 0;
		}
		HANDLE process = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, 22396);
		if (process != NULL) {
			FILETIME ftCreation, ftExit, ftKernel, ftUser;
			SYSTEMTIME stCreation/*, lstCreation*/;
			int ret = 0;
			if (GetProcessTimes(process, &ftCreation, &ftExit, &ftKernel, &ftUser)) {
				FileTimeToSystemTime(&ftCreation, &stCreation);
				SystemTimeToTzSpecificLocalTime(NULL, &stCreation, p);
				ret = 1;
			}
			CloseHandle(process);

			return ret;
		}
		return 0;
	}
	//����ʱ��ð������
	int BubbleSort()
	{
		if (len <= 1)
		{
			return 1;
		}

		while (1)
		{
			int aet = 0;
			for (size_t i = 0; i < len; i++)
			{
				SYSTEMTIME t1, t2;
				if (!GetPidTime(arr[i], &t1) || !GetPidTime(arr[i + 1], &t2))
				{
					return 0;
				}
				ULONGLONG t_1 = systemtime_to_time_t(t1);
				ULONGLONG t_2 = systemtime_to_time_t(t2);
				if (t_1 > t_2)
				{
					long tt_1 = arr[i];
					arr[i] = arr[i + 1];
					arr[i + 1] = tt_1;
					aet = 1;
				}
			}
			if (aet == 0)
			{
				break;
			}
		}

		return 1;
	}


public:
	_MyPid() {}
	~_MyPid() { Clear(); }

private:
	long len = 0;
	long* arr = 0;
	long* arrbak = 0;


}MyPid, * PMyPid, * LPMyPid;

typedef struct _MyPath//�����ļ�����
{
	char m_path[MAX_PATH] = { 0 };
	DWORD m_len = 0;
}MyPath, * PMyPath, * LPMyPath;

typedef struct _MyPathArr
{
public:
	void operator = (const char*& rhs)
	{
		SetPathFile(rhs);
		return;
	}
	int SetPathFile(const char* str)
	{
		if (!str)
		{
			return 0;
		}
		char t_ch[MAX_PATH] = { 0 };
		int tlen = strlen(str);

		PUCHAR p = (PUCHAR)str;

		for (size_t i = 0; i < tlen; i++)
		{
			if (p[i] != '|')
			{
				t_ch[strlen(t_ch)] = p[i];
			}
			if (p[i] == '|' || i == tlen - 1)
			{
				if (len == 0)
				{
					len++;
					arr = new MyPath[len];
					sprintf(arr[0].m_path, "%s", t_ch);
					arr[0].m_len = strlen(t_ch);
					memset(t_ch, 0, MAX_PATH);
					continue;
				}
				len++;
				arrbak = new MyPath[len];
				for (size_t k = 0; k < len; k++)
				{
					if (k == len - 1)
					{
						sprintf(arrbak[k].m_path, "%s", t_ch);
						arrbak[k].m_len = strlen(t_ch);
						memset(t_ch, 0, MAX_PATH);
						continue;
					}
					sprintf(arrbak[k].m_path, "%s", arr[k].m_path);
					arrbak[k].m_len = strlen(arr[k].m_path);
				}
				delete[] arr;
				arr = arrbak;
				arrbak = 0;
			}
		}
		return len;
	}
	PMyPath GetPathFile(const int dx)
	{
		if (dx<0 || dx>len - 1)
		{
			return 0;
		}
		return &arr[dx];
	}

	void Clear()
	{
		if (arr)
		{
			for (size_t i = 0; i < len; i++)
			{
				memset(arr[i].m_path, 0, MAX_PATH);
			}
			delete[] arr;
			arr = 0;
		}
		if (arrbak)
		{
			delete[] arrbak;
			arrbak = 0;
		}
		len = 0;
	}
	int GetPathFileLen()
	{
		return len;
	}

public:
	_MyPathArr() {}
	_MyPathArr(const char* str) { SetPathFile(str); }
	~_MyPathArr() { Clear(); }
private:
	UINT len = 0;
	PMyPath arr = 0;     //���ݱ����
	PMyPath arrbak = 0;
}MyPathArr,*PMyPathArr,*LPMyPathArr;

//�ֿ�����
typedef struct _MyDict
{
	PTCHAR  m_dir = 0;        //�����ֿ�
	TCHAR   m_dirChar[32] = {0}; //��������
	ULONG   m_dirlen = 0;	  //�����ֿⳤ��
	ULONG   m_row = 0;        //��Ч����
	int     m_have = 0;		  //��Ч����
	int     m_lef = 0;        //����11�к���߳�������������
	int     m_right = 0;      //����11�к��ұ߳�������������
	int     m_linek = 0;      //��������
	void operator = (const _MyDict& rhs)
	{
		m_dir = rhs.m_dir;
		sprintf(m_dirChar, "%s", rhs.m_dirChar);
		m_dirlen = rhs.m_dirlen;
		m_row = rhs.m_row;
		m_have = rhs.m_have;
		m_lef = rhs.m_lef;
		m_right = rhs.m_right;
		m_linek = rhs.m_linek;
		return;
	}
}MyDict,*PMyDict,*LPMyDict;

//�ֿ���������
typedef struct _MyDictArr
{
public:
	_MyDictArr() {}
	~_MyDictArr() { Clear(); }
	BOOL OpenFile(LPCSTR dirPath,LPCSTR retPath)
	{
		if ((ULONGLONG)dirPath<=0x10000)
		{
			return FALSE;
		}
		char stpath[MAX_PATH] = { 0 };
		sprintf(stpath, "%s", dirPath);
		if (!file_exist(stpath))
		{
			if ((ULONGLONG)retPath <= 0x10000)
			{
				return FALSE;
			}
			sprintf(stpath, "%s\\%s", dirPath, retPath);
			if (!file_exist(stpath))
			{
				return FALSE;
			}
		}
		HANDLE hFile = CreateFile(stpath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hFile== INVALID_HANDLE_VALUE)
		{
			return FALSE;
		}
		DWORD fileSize = GetFileSize(hFile, NULL);    //����ļ���С�ĵ����ֽ�
		char* fileBuff = new char[fileSize];    //����������
		DWORD realRead = 0;
		BOOL ret = false;
		ret = ReadFile(hFile, fileBuff, fileSize, &realRead, NULL);    //�����ļ������ݸ�������fileBuff
		CloseHandle(hFile);
		if (!ret)
		{
			delete[] fileBuff;
			return FALSE;
		}
		Clear();//�������
		//delete[] fileBuff;
		int dyc = 0;
		char t_chr[MAX_PATH * 2] = { 0 };
		memset(t_chr, 0, MAX_PATH * 2);
		PUCHAR p = (PUCHAR)fileBuff;
		for (size_t i = 0; i < fileSize; i++)
		{
			if (p[i]!='\r'&& p[i+1] != '\n' && p[i] != '\n')
			{
				t_chr[strlen(t_chr)] = p[i];
			}
			if (p[i] == '\r')
			{
				continue;
			}
			if (p[i] == '\n'||i==fileSize-1)
			{
				int len1 = strlen(t_chr);
				if (len1==0)
				{
					ret = FALSE;
					if (len)
					{
						ret = TRUE;
					}
					delete[] fileBuff;
					return ret;
				}
				char t_ch[MAX_PATH * 2] = { 0 };
				memset(t_ch, 0, MAX_PATH * 2);
				dyc = 0;
				for (size_t j = 0; j < len1; j++)
				{
					if (t_chr[j]!='$')
					{
						t_ch[strlen(t_ch)] = t_chr[j];
					}
					if (t_chr[j] == '$'||j==len1-1)
					{
						dyc++;
						if (dyc==1)//�ַ�����������ȥת���ɶ�����
						{
							if (len==0)
							{
								arr = new MyDict;
								HexToBin(t_ch,&arr->m_dir);
								if (arr->m_dir==0)
								{
									delete[] fileBuff;
									return FALSE;
								}
								arr->m_dirlen = strlen(arr->m_dir);
								arr->m_linek = (int)(strlen (t_ch)*4 / 11);


								memset(t_ch, 0, MAX_PATH * 2);
								len++;
								continue;
							}
							len++;
							arrbak = new MyDict[len];
							for (size_t k = 0; k < len; k++)
							{
								if (k==len-1)
								{
									
									HexToBin(t_ch, &arrbak[k].m_dir);
									if (arrbak[k].m_dir == 0)
									{
										ret = FALSE;
										if (len)
										{
											ret = TRUE;
										}
										delete[] fileBuff;
										return ret;
									}
									arrbak[k].m_dirlen = strlen(arrbak[k].m_dir);

									arrbak[k].m_linek = (int)(strlen(t_ch) * 4 / 11);

									continue;
								}
								arrbak[k] = arr[k];
							}
							delete[] arr;
							arr = arrbak;
							arrbak = 0;
							
						}
						if (dyc == 2)//�����ַ�����
						{
							sprintf(arr[len-1].m_dirChar, "%s", t_ch);
						}

						if (dyc == 3)//�ַ�����
						{
							char sii[6] = { 0 };
							memset(sii, 0, 6);
							int derc = 0;
							int len2 = strlen(t_ch);
							for (size_t f = 0; f < len2; f++)
							{
								if (t_ch[f]!='.')
								{
									sii[strlen(sii)] = t_ch[f];
								}
								if (t_ch[f] == '.'||f==len2-1)
								{
									if (derc==0)
									{
										arr[len - 1].m_lef = StrToInt(sii);
										memset(sii, 0, 6);
										derc++;
										continue;
									}
									if (derc == 1)
									{
										arr[len - 1].m_right = StrToInt(sii);
										memset(sii, 0, 6);
										derc++;
										continue;
									}
									if (derc == 2)
									{
										arr[len - 1].m_have = StrToInt(sii);
										memset(sii, 0, 6);
										derc++;
										continue;
									}
								}
							}							
						}

						if (dyc == 4)//�ַ���������
						{
							arr[len - 1].m_row = StrToInt(t_ch);
							if (arr[len - 1].m_row> m_size)
							{
								m_size = arr[len - 1].m_row;
							}							
						}

						memset(t_ch, 0, MAX_PATH * 2);
					}

				}
				memset(t_chr, 0, MAX_PATH * 2);
			}

		}
		ret = FALSE;
		if (len)
		{
			ret = TRUE;
		}
		delete[] fileBuff;
		return ret;
	}
	void Clear()
	{
		if (len)
		{
			for (size_t i = 0; i < len; i++)
			{
				delete[] arr[i].m_dir;
				
			}
			delete[] arr;
			arr = 0;
			len = 0;
			m_size = 0;
		}



	}
	PMyDict GetDirDx(int dx)
	{
		if (dx<0||dx>len-1)
		{
			return 0;
		}
		return &arr[dx];
	}
	int GetDirLen()
	{
		return len;
	}
public:
	int m_size = 0;
private:
	PMyDict arr;	  //�ֿ���
	PMyDict arrbak;  //�ֿ��������

	ULONG  len = 0;	  //�����ֿⳤ��
}MyDictArr, * PMyDictArr, * LPMyDictArr;

//ocr����
typedef struct _MyOcr
{
	int m_row = 0;      //��
	int m_dx = 0;		//λ��
	char m_char[32] = { 0 };//�ַ�
	char m_len;            //�ַ�����
	POINT m_pos = { 0 };//�ַ���������
	void operator = (const _MyOcr& rhs)
	{
		sprintf(m_char, "%s", rhs.m_char);
		m_row = rhs.m_row;
		m_dx = rhs.m_dx;
		m_pos = rhs.m_pos;
		m_len = rhs.m_len;
		return;
	}
}MyOcr,*PMyOcr;

typedef struct _MyOcrArr
{
public:
	_MyOcrArr() {};
	~_MyOcrArr() { Clear(); };
	void Clear()
	{
		if (len)
		{
			delete[] arr;
			arr = 0;
			len = 0;
			m_row = 0;
			m_Size = 0;
		}

	}

	//����ַ�
	int AddOcrChar(LPCSTR str,int x,int y,int ize=0)
	{
		if (m_Size==0)
		{
			m_Size = ize;
		}
		if (m_pt.x==-1)
		{
			m_pt.x = x;
			m_pt.y = y;
			m_MaxPos = y;
		}
		if (len==0)
		{
			len++;
			arr = new MyOcr;
			arr[0].m_pos = m_pt;
			sprintf(arr[0].m_char, "%s", str);
			arr[0].m_len = strlen(str);
			arr[0].m_dx = 0;
			arr[0].m_row = 0;
			return len;
		}
		len++;
		arrbak = new MyOcr[len];
		for (size_t i = 0; i < len; i++)
		{
			if (i==len-1)
			{
				arrbak[i].m_pos.x = x;
				arrbak[i].m_pos.y = y;
				sprintf(arrbak[i].m_char, "%s", str);
				arrbak[i].m_len = strlen(str);
				arrbak[i].m_dx = i;
				if (abs(y-m_pt.y)>m_Size&&y>m_MaxPos)
				{
					m_row++;
				}
				arrbak[i].m_row = m_row;
				continue;
			}
			arrbak[i] = arr [i] ;
		}

		if (y > m_MaxPos)
		{
			m_MaxPos = y;
		}
		m_pt.x = x;
		m_pt.y = y;
		delete[] arr;
		arr = arrbak;
		arrbak = 0;

		paixi();//ð������

		return len;
	}

	char* GetOcrStr()
	{
		if (!len)
		{
			return 0;
		}
		int tlen = 0;
		for (size_t i = 0; i < len; i++)
		{
			tlen += arr[i].m_len;
		}
		tlen += m_row*2+1;
		char* retstr = new char[tlen];
		memset(retstr,0, tlen);
		m_row += 1;

		for (size_t i = 0; i < m_row; i++)
		{
			if (i>0)
			{
				sprintf(retstr, "%s\r\n", retstr);
			}
			for (size_t j = 0; j < len; j++)
			{
				if (arr[j].m_row==i)
				{
					sprintf(retstr + strlen(retstr), "%s", arr[j].m_char);
				}	
			}
		}

		//sprintf(retstr+strlen(retstr),"%s",arr[i].m_char);
		return retstr;

	}

	int GetOcrLen()
	{
		return len;
	}
private:
	void paixi()
	{
		if (len<=1)
		{
			return;
		}
		BOOL ret = FALSE;
			while (1)
			{
				ret = FALSE;
				for (size_t i = 0; i < len-1; i++)
				{
					if (arr[i].m_pos.x> arr[i+1].m_pos.x)
					{
						MyOcr  t_ch = arr[i];
						arr[i] = arr[i + 1];
						arr[i].m_dx = i;
						arr[i + 1] = t_ch;
						arr[i + 1].m_dx = i+1;
						ret = TRUE;
					}

				}
				if (!ret)
				{
					break;
				}

			}
	}


private:

	POINT m_pt = {-1,-1};//��¼�ϴ�����
	int m_MaxPos = 0;    //��¼���Y����

	int len = 0;//�ַ�����
	int m_row = 0;   //����
	PMyOcr arr = 0;
	PMyOcr arrbak = 0;
public:
	int m_Size = 0;//�����ַ� �߶�

}MyOcrArr,*PMyOcrArr;

typedef struct tagWNDINFO
{
	DWORD dwProcessId;
	HWND hWnd;
}WNDINFO, * LPWNDINFO;

typedef struct _MyProc
{
	UINT64 X64 = 0;                  //X64LoadLibraryA  ������ַ
	UINT X86 = 0;					 //X86LoadLibraryA  ������ַ
}MyProc,*PMyProc,*LPMyProc;

typedef struct _OCRTYPE
{
	TCHAR m_str[32] = { 0 };
	int  pos = 0;
	int  x = 0;
	int  y = 0;
	int  len = 0;
	void operator = (const _OCRTYPE& rhs)
	{
		sprintf(m_str, "%s", rhs.m_str);
		pos = rhs.pos;
		x = rhs.x;
		y = rhs.y;
		len = rhs.len;
		return;
	}
}OCRTYPE, * POCRTYPE, * LPOCRTYPE;

typedef struct _OCRTYPEARR
{
public:
	long	AddOcr(const char* str, long x, long y)
	{
		if (!str)
		{
			return -1;
		}
		if (len == 0)
		{


			arr = new OCRTYPE;
			arr[0].pos = len;
			sprintf(arr[0].m_str, "%s", str);
			arr[0].x = x;
			arr[0].y = y;
			arr[0].len = strlen(str);
			len++;
			return len;
		}
		len++;
		arrbak = new OCRTYPE[len];
		for (size_t i = 0; i < len; i++)
		{
			if (i == len - 1)
			{
				arrbak[i].pos = len - 1;
				sprintf(arrbak[i].m_str, "%s", str);
				arrbak[i].x = x;
				arrbak[i].y = y;
				arrbak[i].len = strlen(str);
				continue;
			}
			arrbak[i] = arr[i];
		}

		delete[] arr;
		arr = arrbak;
		arrbak = 0;

		//ð������

		return len;

	}

	_OCRTYPEARR() {};
	~_OCRTYPEARR() { Clear(); };
	void Clear()
	{
		if (len)
		{
			delete[] arr;
			arr = 0;
			len = 0;

		}
	}
	POCRTYPE GetOcr(long dx)
	{
		if (dx<0 || dx>len - 1)
		{
			return 0;
		}
		return &arr[dx];
	}

	long GetLen()
	{
		return len;
	}

private:
	long len = 0;
	POCRTYPE arr = 0;
	POCRTYPE arrbak = 0;

}OCRTYPEARR, * POCRTYPEARR, * LPOCRTYPEARR;


typedef struct _POINTP
{
public:
	int x = 0;
	int y = 0;
	int w = 0;
	int h = 12;
	void operator = (const _POINTP& rhs)
	{
		x = rhs.x;
		y = rhs.y;
		w = rhs.w;
		h = rhs.h;
		return;
	}

}POINTP, * PPOINTP;


typedef struct _POINTARR
{
public:
	_POINTARR() {};
	~_POINTARR() { Clear(); };

	void Clear()
	{
		if (len)
		{
			delete[] arr;
			arr = 0;
			len = 0;

		}
	}

	long AddPoint(int x, int y, int w)
	{
		if (GetPos(x, y))
		{
			return len;
		}

		if (len == 0)
		{
			len++;
			arr = new POINTP;
			arr[0].x = x;
			arr[0].y = y;
			arr[0].w = w;
			arr[0].h = 12;
			return len;
		}
		len++;
		arrbak = new POINTP[len];
		for (size_t i = 0; i < len; i++)
		{
			if (i == len - 1)
			{
				arrbak[i].x = x;
				arrbak[i].y = y;
				arrbak[i].w = w;
				arrbak[i].h = 12;
				continue;
			}
			arrbak[i] = arr[i];
		}

		delete[] arr;
		arr = arrbak;
		arrbak = 0;

		return len;
	}


	BOOL GetPos(int x, int y)
	{
		bool ret = false;
		for (size_t i = 0; i < len; i++)
		{
			if ((x >= arr[i].x && x <= arr[i].x + arr[i].w) && (y >= arr[i].y && y <= arr[i].y + arr[i].h))
			{
				ret = true;
				break;
			}
		}
		return ret;
	}


private:
	int len = 0;
	PPOINTP arr = 0;
	PPOINTP arrbak = 0;
}POINTARR, * PPOINTARR, * LPPOINTARR;

#pragma pack(push,1)
#include "X64asm.h"
typedef long(*sethook)(HWND , UINT);
typedef long(*uhook)(HWND);

class DXBind
{
public:
	//����Ĭ�ϲ���·��
	long  lwSetpath(const char* path);
	//��ͼ��������
	long lwFindPic(long x_1, long y_1, long w_1, long  h_1, LPCSTR pic_name, LPCSTR delta_color, double sim, long* longX, long* longY);
	//��ͼ��������ϵ��
	long lwFindPicEx(long x_1, long y_1, long w_1, long h_1, LPCSTR pic_name, LPCSTR delta_color, double sim, LPVOID otbf);
	//��ɫ��������
	long lwFindColor(long x1, long y1, long w1, long h1, LPCSTR color, double sim, long* longX, long* longY);
	//����ָ�������ڵ���ɫ��,��ɫ��ʽ"RRGGBB-DRDGDB",ע��,�Ͱ�������ɫ��ʽ�෴
	long FindColorBlock(long x_1, long y_1, long w_1, long h_1,LPCSTR color,double sim, long count, long width, long height, long* intX, long* intY);
	//�Ƚ�ָ�������(x,y)����ɫ
	long CmpColor(long x, long y, LPCSTR color, double sim);
	//ץȡָ������(x1, y1, x2, y2)��ͼ��,����Ϊfile(24λλͼ)
	long Capture(long x, long y, long w, long h, LPCSTR file);
	//��ȡ(x,y)����ɫ,��ɫ���ظ�ʽ"RRGGBB",ע��,�Ͱ�������ɫ��ʽ�෴
	long GetColor(long x, long  y,LPCSTR* oft);
	//��ȡָ���������ɫ����, ��ɫ��ʽ"RRGGBB-DRDGDB", ע��, �Ͱ�������ɫ��ʽ�෴
	long GetColorNum(long x_1, long y_1, long w_1, long h_1, LPCSTR color, double sim);
	//32λλͼת��24λ
	long lwBmp32To24(LPCSTR Filepath, LPCSTR FilepathBak, bool ret=true);
	//�ж�ָ����������ָ����ʱ����(��),ͼ�������Ƿ�һֱ����.(����). (���߰󶨵Ĵ��ڲ�����Ҳ����1)
	long IsDisplayDead(long x, long y, long w, long h, long t);
	//���ں���
	//�󶨴���
	long Bind(LONG hwnd,ULONG KeyMouse);
	//����󶨴���,���ͷ�ϵͳ��Դ.һ����
	long UnBindWindow();
	//���ô��ڵ�״̬
	long SetWindowState(long hwnd, long flag);
	//���ô��ڵ�͸����
	bool SetWindowTransparent(long hwnd, long trans);
	//���ô��ڵĴ�С
	long SetWindowSize(long hwnd, long width, long hight, int type = 0);
	//��ָ�����ڷ���ճ������. �Ѽ���������ݷ��͵�Ŀ�괰��.
	long SendPaste(LONG hwnd);
	//���ü����������
	long SetClipboard(LPCSTR values);
	//��ȡ�����������
	long GetClipboard(LPCSTR* retstr);
	//��ָ�����ڷ����ı�����
	long SendString(long hwnd, LPCSTR str);
	//���ھ��_ȡ����pid
	long GetWindowProcessId(long h);
	//��ȡָ���������ڵĽ��̵�exe�ļ�ȫ·��.
	long GetWindowProcessPath(LONG hwnd, LPCSTR* retstring);
	//��ȡָ�����ڵ�һЩ����
	long GetWindowState(LONG hwnd, LONG flag);
	//��ȡ���ָ��Ŀɼ����ھ��,���Ի�ȡ�������Դ��Ĳ���޷���ȡ���ľ��
	long GetMousePointWindow(LONG x=-1, LONG y=-1);
	//��ȡ�����ھ��
	HWND  GetProcessMainWnd(DWORD  dwProcessId);	 
	//���ҷ����������߱������Ķ���ɼ�����
	long FindWindow(LPCSTR class_name, LPCSTR title);
	//����ָ�������Լ���������,ö��ϵͳ�з��������Ĵ���,����ö�ٵ������Դ����޷�ö�ٵ��Ĵ���
	long lwEnumWindow(LPCSTR process_name, LPCSTR title, LPCSTR class_name, LONG filter, LPCSTR* otbuff);
	//����ָ������pid�Լ���������,ö��ϵͳ�з��������Ĵ���,����ö�ٵ������Դ����޷�ö�ٵ��Ĵ���
	long lwEnumWindowId(long pid, LPCSTR title, LPCSTR class_name, LONG filter, LPCSTR* otbuff);
	//����ָ��������,ö��ϵͳ�з��������Ľ���PID,���Ұ��ս��̴�˳������.
	long EnumProcess(LPCSTR name, LPCSTR* otbuff);
	//����ָ������,ö��ϵͳ�з��������Ĵ���,����ö�ٵ������Դ����޷�ö�ٵ��Ĵ���
	long EnumWindow(LONG parent, LPCSTR title, LPCSTR class_name, LONG filter, LPCSTR* retstr);
	//ϵͳƪ
	//��ʱָ���ĺ���,�����в�����UI����. һ��߼�����ʹ��.�����ò���.
	long mysleep(DWORD delaytime);
	//�õ�ϵͳ��·�� 
	long GetDir(long type, LPCSTR* oubuf);
	//��ȡ��ǰCPU����(intel����amd).
	long GetCpuType();
	//��ȡ��ǰCPU��ʹ����. �ðٷֱȷ���.
	long GetCpuUsage();
	//��ȡ������ָ��Ӳ�̵����к�. Ҫ����ý��̱����й���ԱȨ��. ���򷵻ؿմ�.
	long GetDiskSerial(long index,LPCSTR* outbuf);
	//��ȡ�������Կ���Ϣ.
	long GetDisplayInfo(LPCSTR* outbuf);
	//�жϵ�ǰϵͳ��DPI(��������)�ǲ���100%����.
	long GetDPI();
	//����ָ����Ӧ�ó���.���ؽ���PID
	long RunApp(LPCSTR path, long type=0);
	//ȡӲ��������
	long long GetHDiskCode();
	//��ȡCPU���к�
	long GetCpuCode(LPCSTR* str);
	//��ȡBOIS��������
	LONGLONG GetMainBoardInfoByCmd();
	//��ȡ�����Ļ�����.(������). 
	long GetMachineCode(LPCSTR* outstr);
	//��ȡ�����Ļ�����.(������). 
	long GetMachineCodeNoMac(LPCSTR* outstr);
	//�������ȡ��ǰ����ʱ��.
	char* GetNetTime();
	//����ָ��ʱ�������IP,�������ȡ��ǰ����ʱ��.
	long GetNetTimeByIp(LPCSTR ip,LPCSTR* outstr);
	//�жϵ�ǰϵͳ�Ƿ�Ϊ64λ
	BOOL Is64BitSystem();
	//�жϵ�ǰ���ھ���Ƿ�Ϊ64λ
	BOOL Is64WindowSystem(long hwnd);
	//��ȡ��Ļ��ɫ��
	long GetScreenDepth();
	//������Ļ��ɫ��
	long SetScreenDepth(long dmBitsPerPel);
	//����ʶ��
	//�����ֿ��ļ�
	BOOL SetDict(LPCSTR file);
	//����Ļ��Χ(x1,y1,x2,y2)��,����string(������������ַ��������),�����ط���color_format������λ��
	long FindStr(long x1, long y1, long w,long h,LPCSTR str,LPCSTR color_format,double sim, long* intX,long* intY);
	//����Ļ��Χ(x1,y1,x2,y2)��,����string(�����������ַ��������),�����ط���color_format����������λ��,���ƶ�simͬOcr�ӿ�����.
	long FindStrEx(long x1, long y1, long w, long h, LPCSTR str, LPCSTR color_format, double sim, LPCSTR* outstr);
	//ʶ����Ļ��Χ(x1,y1,x2,y2)�ڷ���color_format���ַ���,�������ƶ�Ϊsim,simȡֵ��Χ(0.1-1.0),
	long Ocr(long x_1, long y_1, long w_1, long h_1,LPCSTR color_format,double  sim, LPCSTR* outstr);

	//�������·��
	CHAR* GetModuleFile();
	//������
	//������ƶ���Ŀ�ĵ�(x,y)
	long MoveTo(long x,long y);
	//����������
	long LeftClick();

private:
	//��������Ƿ�Խ��
	bool SetXy(long* x, long* y, long* w, long* h);
	//��ɫ��䱳��
	bool FillSolidRect(HDC dc, LPCRECT lpRect, COLORREF clr);
	//���ļ�����24λͼ
	bool loadBitmap(LPCSTR strPath, LPVOID outdata, PBITMAPINFO PP);
	//���λͼBUFF
	LPVOID BmpTo24Data(const LPVOID src, PBITMAPINFO p2, DWORD dwStyle);
	//�Ӵ��ڼ���λͼ
	bool GetDcPic(DWORD x, DWORD y, DWORD w, DWORD h, LPVOID outdata, PBITMAPINFO PP);
	//ͼ�񻺳����Ƚ�
	long CmpBmpData(const LPVOID pic, const LPVOID pic1, LPCSTR delta_color, double sim, long x, long y, PBITMAPINFO PP);
	//����ϵ���ַ�����Ҫ�Ŀռ�
	long  GetStrPosLen(long* dx, long* x, long* y);
	//��ȡ���ƶ�
	long GetSimLen(double sim);
     //����:32λλͼת��24
	bool BmpTo24DataFile(const char* Filepath, const char* src, PBITMAPINFO bmp);
	//������ͼ�����̺���
	bool IsDisplayDead_bak(DWORD x, DWORD y, DWORD w, DWORD h, LPVOID outdata, PBITMAPINFO PP);

	//���õ���Ȩ��
	bool EnablePrivilege(LPCTSTR pszPrivName, bool fEnable);
	//�жϴ������ڽ����ǲ���64λ
	BOOL IsWow64ProcessEx(HWND h);

private:
	//ȡС�����ֱ�����������λ
	int fractional_part_as_int(double number) {

		return	(int)((number - (int)number) * 100); // y => 4567
	   //https://ask.csdn.net/questions/7618162
	}
	//ö�����н���pid
	bool EnumProcessbyName(LPCSTR process_name ,PMyPid p);
	//ȡӲ�������ֽ���
	LONGLONG IDE(int iDrive=0);
	//ȡӲ�������ֽ���
	LONGLONG SCSI(int iDrive = 0);
	//�����ּ���
	LONGLONG Characteristic_character(PIDSECTOR p);
	//��ȡ��һ����̫��������MAC��ַ
	char* GetMac();
	//��������ܹ��̴�����
	UCHAR CharToInt_bak(UCHAR p);
	//��������ܹ��̲�������
	UCHAR CharToInt_bakOnMac(UCHAR p);
	//����CPIU����
	void SetCpuidStr(LPCVOID pp, int dx,PMycpu p,int* ret);
	//ȡOcr�ַ�����λ��
	int GetStrPos(LPVOID pl,int pos);
	//������Ϣ
	LRESULT SndMeage(_In_ UINT Msg, _Pre_maybenull_ _Post_valid_ WPARAM wParam, _Pre_maybenull_ _Post_valid_ LPARAM lParam) {return ::SendMessageA(m_hwnd, Msg, wParam, lParam); }
	//
	sethook m_HOOK = 0;
	uhook   m_unHOOK = 0;
private:
	MyProc m_MyProc;           //LoadLibraryA  ������ַ
	DWORD nPid=0;
	HWND m_hwnd=0;            //���󶨵Ĵ��ڵľ��
	DWORD m_Pid=0;               //�󶨵Ľ���pid
	Shmem m_pData;               //�����ڴ������
	CHAR m_SetPath[MAX_PATH * 2] = { 0 };//Ĭ�ϲ�����
	BOOL m_SetPathRet = FALSE;//�Ƿ�������ȫ��Ĭ��·��
	Shmem  m_poc;             //poc�����ڴ�
private:
		const UCHAR  g_incpu[58] = {
        0x48,0x33,0xC0,0x48,0xB8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0xA2,0x49,0xB8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x41,0x89,0x00,0x41,0x89,0x58,0x04,0x41,0x89,0x48,0x08,0x41,0x89,0x50,0x0C,0x48,0xBF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x48,0xC7,0x07,0x01,0x00,0x00,0x00,0xC3};
		MyDictArr    m_Dict;//�ֿ�����

public:
	DXBind(void);
	~DXBind(void);
};

#endif

