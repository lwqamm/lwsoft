#include "get_internet_time.h"

using namespace std;
#include "DXBind.h"
/*
Name:		FindHostIP
Function:	get IP address across ServerName
params:		const char *pServerName
return:		IPNumber
*/

IPNumber FindHostIP(const char *pServerName)
{
	HOSTENT *pHostent;

	// Get hostent structure for hostname:
	if (!(pHostent = gethostbyname(pServerName)))
		throw HRException("could not resolve hostname.");

	// Extract primary IP address from hostent structure:
	if (pHostent->h_addr_list && pHostent->h_addr_list[0])
		return *reinterpret_cast<IPNumber*>(pHostent->h_addr_list[0]);

	return 0;
}


/*
Name:		FillSockAddr
Function:	Fill socket with address(serverName)
params:		sockaddr_in *pSockAddr, const char *pServerName, int portNumber
return:		None
*/
void FillSockAddr(sockaddr_in *pSockAddr, const char *pServerName, int portNumber)
{
	// Set family, port and find IP
	pSockAddr->sin_family = AF_INET;
	pSockAddr->sin_port = htons(portNumber);
	pSockAddr->sin_addr.S_un.S_addr = FindHostIP(pServerName);
}




/*
名称：RequestHeaders
功能：关键功能，从时间服务器请求时间
参数：const char*pServername，time_t*timeRecv
return：bool，如果成功获取网络时间，则返回true，否则返回false
*/
bool RequestHeaders(const char *pServername, time_t *timeRecv)
{
	int slen = 0;
	//time_t timeRecv;
	SOCKET      hSocket = INVALID_SOCKET;
	char        recvBuf[REC_BUFFER_SIZE];
	sockaddr_in sockAddr = { 0 };
	bool        bSuccess = true;


	try{
		// Lookup hostname and fill sockaddr_in structure:
		FillSockAddr(&sockAddr, pServername, SERVER_PORT);
		/*sockAddr.sin_family = AF_INET;
		sockAddr.sin_port = htons(123);
		sockAddr.sin_addr.S_un.S_addr=inet_addr("202.112.31.197");*/
		// Create socket
		if ((hSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == INVALID_SOCKET)
			throw HRException("could not create socket.");


		// Connect to server
		if (connect(hSocket, reinterpret_cast<sockaddr*>(&sockAddr), sizeof(sockAddr)) != 0)
			throw HRException("could not connect.");
		//cout << "connected " << inet_ntoa(sockAddr.sin_addr) << ":" << SERVER_PORT << endl;


		// send request part 1
		if (send(hSocket, msg, sizeof(msg), 0) == SOCKET_ERROR)
			throw HRException("failed to send data.");

		//timeval timeout = { 3,0 };
		//设置接收超时
	   timeval tv_out;
		tv_out.tv_sec = 1500;
		tv_out.tv_usec = 1500;
	
	 //setsockopt(hSocket, SOL_SOCKET, SO_SNDTIMEO,(char*) &tv_out, sizeof(tv_out));
	 setsockopt(hSocket, SOL_SOCKET, SO_RCVTIMEO, (char*)&tv_out, sizeof(tv_out));
		//cout << "Dumping received data...\n\n";
		// Loop to print all data
		int elen = 0;
		slen = recv(hSocket, recvBuf, REC_BUFFER_SIZE, 0);
		int eroo = GetLastError();
		if (eroo!=0)
		{
			*timeRecv = -1;
			throw HRException("failed to send data.");
		}
		//part where we take time out of recvBuf       
		*timeRecv = ntohl(((time_t*)recvBuf)[4]);
		if (*timeRecv>0)*timeRecv -= 2208988800U;

	}
	catch (HRException e){
		//cerr << "\nError: " << e.what() << endl;
		bSuccess = false;
	}


	if (hSocket != INVALID_SOCKET){
		closesocket(hSocket);
	}

	return bSuccess;
}



/*
Name:		time_t_2_tm
Function:	Transfer time_t to tm
params:		const time_t *tt, struct tm *tim
return:		None
Author:		Leo Ma
Date:		2019.09.17
*/
void time_t_2_tm(const time_t *tt, struct tm *tim)
{
	tim = localtime(tt);
	tim->tm_year += 1900;
	tim->tm_mon += 1;
}



/*
名称：getinternettime
函数：通过调用RequestHeaders（）检查windows套接字版本并获取internet时间
参数：time_t*timeRecv
return：int，获取上网时间的状态
作者：Leo Ma
日期：2019.09.17
*/
int get_internet_time(time_t *timeRecv)
{
	int iRet = 1;
	WSADATA wsaData;
	//struct tm *tim = new struct tm;//定义一个tm结构体的指针

	if (WSAStartup(MAKEWORD(REQ_WINSOCK_VER, 0), &wsaData) != 0){
		//cerr << "startup failed!\n";
		return iRet;
	}


	// Check if major version is at least REQ_WINSOCK_VER
	if (LOBYTE(wsaData.wVersion) >= REQ_WINSOCK_VER){

		// Set default hostname:
		const char *pHostname = DEF_SERVER_NAME;
		iRet = !RequestHeaders(pHostname, timeRecv);//用这个函数填充tim指针的内容，因此要传参进去tim指针的地址

	}
	else{
		//cerr << "required winsocket version not supported!";
	}


	// Cleanup winsock
	if (WSACleanup() != 0){
		//cerr << "cleanup failed!\n";
		iRet = 1;
	}

	return iRet;

}

int get_internet_timeip(time_t* timeRecv,const char* ips)
{


	MyPathArr  t_ip = ips;
	if (!t_ip.GetPathFileLen())
	{
		return 1;
	}
	int iRet = 1;
	WSADATA wsaData;
	//struct tm *tim = new struct tm;//定义一个tm结构体的指针

	if (WSAStartup(MAKEWORD(REQ_WINSOCK_VER, 0), &wsaData) != 0) {
		//cerr << "startup failed!\n";
		return iRet;
	}


	// Check if major version is at least REQ_WINSOCK_VER
	if (LOBYTE(wsaData.wVersion) >= REQ_WINSOCK_VER) {

		// Set default hostname:
		//const char* pHostname = DEF_SERVER_NAME;
		PMyPath p = 0;
		for (size_t i = 0; i < t_ip.GetPathFileLen(); i++)
		{
			p = t_ip.GetPathFile(i);
			iRet = !RequestHeaders(p->m_path, timeRecv);//用这个函数填充tim指针的内容，因此要传参进去tim指针的地址
			if (!iRet)
			{
				break;
			}
		}
		

	}
	else {
		//cerr << "required winsocket version not supported!";
	}


	// Cleanup winsock
	if (WSACleanup() != 0) {
		//cerr << "cleanup failed!\n";
		iRet = 1;
	}

	return iRet;

}

//char* GetNetTime()
//{
//	struct tm* tim = new struct tm;
//	time_t timeRecv1, timeRecv2;
//	if (get_internet_time(&timeRecv1))
//	{
//		return 0;
//	}
//	tim = localtime(&timeRecv1);//这个函数返回了一个指向struct tm类型的地址
//	tim->tm_year += 1900;
//	tim->tm_mon += 1;
//	char* bfu = new char[50];
//	memset(bfu, 0, 50);
//
//	sprintf(bfu, "%d-%02d-%02d %02d:%02d:%02d", tim->tm_year, tim->tm_mon, tim->tm_mday, tim->tm_hour, tim->tm_min, tim->tm_sec);
//	return bfu;
//}
/*
Name:		demo
Function:	a demo shows how to use this API to get internet time
params:		None
return:		None
Author:		Leo Ma
Date:		2019.09.17
*/
//just rename this function to main(),and test this API
//int main()
//{
//	char* str = GetNetTime();
//	if (str)
//	{
//		printf("%s\n", str);
//		Sleep(500);
//		delete[] str;
//	}
//	
//	system("pause");
//	return 0;
//}