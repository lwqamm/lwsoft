#pragma warning(disable:4996)
#include <iostream>
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define WIN32_MEAN_AND_LEAN

#include <winsock2.h>
#include <windows.h>

#include <time.h>
#pragma comment(lib,"ws2_32.lib")    //Winsock Library

class HRException{
public:
	HRException() :
		m_pMessage("") {}
	virtual ~HRException() {}
	HRException(const char *pMessage) :
		m_pMessage(pMessage) {}
	const char * what() { return m_pMessage; }
private:
	const char *m_pMessage;
};

const int  REQ_WINSOCK_VER = 2; // Minimum winsock version required
const char DEF_SERVER_NAME[] = "202.112.31.197";// "cn.pool.ntp.org";//ntp.ntsc.ac.cn   0.pl.pool.ntp.org cn.pool.ntp.org
const int  SERVER_PORT = 123; //NTP������Ĭ�϶˿���123
const int  REC_BUFFER_SIZE = 128;//���ջ����ڴ��С

const char msg[48] = { 010, 0, 0, 0, 0, 0, 0, 0, 0 };

// IP number typedef for IPv4
typedef unsigned long IPNumber;


//һЩ��������

//�����������IP��ַ
IPNumber FindHostIP(const char *pServerName);
//���socket��ַ
void FillSockAddr(sockaddr_in *pSockAddr, const char *pServerName, int portNumber);
//���ĺ���������ʱ�䣬��ָ�����������������ʱ��
bool RequestHeaders(const char *pServername, time_t *timeRecv);
//��time_t��ʽ��ʱ��ת����struct tm��ʽ��ʱ��
void time_t_2_tm(const time_t *tt, struct tm *tim);
//check windows socket�汾���������ʱ��
int get_internet_time(time_t *timeRecv);
//����ָ��ʱ�������IP,�������ȡ��ǰ����ʱ��.
int get_internet_timeip(time_t* timeRecv, const char* ips);
//���������ʹ�÷���demo
int demo();


