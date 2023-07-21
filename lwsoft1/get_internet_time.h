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
const int  SERVER_PORT = 123; //NTP服务器默认端口是123
const int  REC_BUFFER_SIZE = 128;//接收缓冲内存大小

const char msg[48] = { 010, 0, 0, 0, 0, 0, 0, 0, 0 };

// IP number typedef for IPv4
typedef unsigned long IPNumber;


//一些函数声明

//根据域名获得IP地址
IPNumber FindHostIP(const char *pServerName);
//填充socket地址
void FillSockAddr(sockaddr_in *pSockAddr, const char *pServerName, int portNumber);
//核心函数：请求时间，从指定的域名处获得网络时间
bool RequestHeaders(const char *pServername, time_t *timeRecv);
//将time_t格式的时间转换成struct tm格式的时间
void time_t_2_tm(const time_t *tt, struct tm *tim);
//check windows socket版本，获得网络时间
int get_internet_time(time_t *timeRecv);
//根据指定时间服务器IP,从网络获取当前北京时间.
int get_internet_timeip(time_t* timeRecv, const char* ips);
//本函数库的使用方法demo
int demo();


