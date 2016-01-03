#include "TransmitionManager.h"
TransmitionManager::TransmitionManager()
{
		ifstream ifs("ip.cfg");
		ifs>>IPADDRS;
		ifs.close();
};

int TransmitionManager::TransmitLogin(int request, string messageJSON)
{
	stringstream ss; ss <<hex<< request;
	string requeststr;ss >> requeststr;
	messageJSON = "{'STATE':'" + requeststr + "','VALUE':" + messageJSON + "}";

	string recvStr=Transmit(messageJSON);
	if(recvStr=="") return TRANS_NETERROR;

	int loginStat = 0;
	if (recvStr[0]!='{')
		loginStat = -1;
	else
	{
		SourceManager sm;
		sm.PutSource("profile", recvStr);
	}
	return loginStat;
}


int TransmitionManager::TransmitSendFile(int request, string userMessage, string path)
{
	stringstream ss; ss <<hex<< request;
	string requeststr; ss >> requeststr;
	//userMessage = "{'STATE':'" + requeststr + "','VALUE':" + userMessage + "}";

	ifstream  in(path,ios::binary);
	string file((istreambuf_iterator<char>(in)), (istreambuf_iterator<char>()));
	int filelength= file.length();
	int jsonlength= userMessage.length();
	//request
	string messageJSON="";

	messageJSON+=int2bytes(request);
	messageJSON+=int2bytes(jsonlength);
	messageJSON+=int2bytes(filelength);

	messageJSON+=userMessage+file;

	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD(1, 1);

	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) {
		return -1;
	}

	if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1) {
		WSACleanup();
		return -1;
	}
	SOCKET sockClient = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = inet_addr(IPADDRS.c_str());
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(PORT);
	connect(sockClient, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));
	string str = messageJSON;
	//string UTF8_str = ToUTF8(str);
	//send(sockClient, UTF8_str.c_str(), messageJSON.length() + 1, 0);
	send(sockClient, messageJSON.c_str(), messageJSON.length() + 1, 0);
	Sleep(WAITTIME);
	//send(sockClient, "", 1, SD_SEND);
	shutdown(sockClient,SD_SEND);

	char recvBuf[4096]={'\0'};
	recv(sockClient, recvBuf, 4096, 0);
	string recvStr(recvBuf);
	//cout << recvStr << endl;
	int Stat=SUCCESS;
	if (recvStr == "fail" || recvStr == "serverdown")
		Stat = TRANS_NETERROR;
	closesocket(sockClient);
	WSACleanup();
	return Stat;
}

int TransmitionManager::TransmitRecvFile(int request, string userMessage, string filename)
{
	stringstream ss; ss <<hex<< request;
	string requeststr; ss >> requeststr;
	userMessage = "{'STATE':'" + requeststr + "','VALUE':" + userMessage + "}";

	string recvStr=Transmit(userMessage);
	if(recvStr=="") return TRANS_NETERROR;
	int loginStat = SUCCESS;
	if (recvStr == "fail")
		loginStat =	TRANS_LOGINERR;

	//write file out
	ofstream ofs("tmp/"+filename,ios::binary);
	ofs<<recvStr;
    ofs.close();

	return loginStat;
}

int TransmitionManager::TransmitMessage(int request, string userMessage)
{
	stringstream ss;
	ss <<hex<< request;
	string requeststr;
	ss >> requeststr;
	userMessage = "{'STATE':'" + requeststr + "','VALUE':" + userMessage + "}";
	//cout<<userMessage<<endl;
	string recvStr=Transmit(userMessage);
	if(recvStr=="") return TRANS_NETERROR;
	//cout << recvStr << endl;
	int loginStat = SUCCESS;
	if (recvStr == "userexist")
		loginStat =	TRANS_LOGINERR;
	
	return loginStat;
}

int TransmitionManager::TransmitGetMessage(int request, string messageJSON, string key)
{
	stringstream ss;
	ss <<hex<< request;
	string requeststr;
	ss >> requeststr;
	messageJSON = "{'STATE':'" + requeststr + "','VALUE':" + messageJSON + "}";
	
	string recvStr=Transmit(messageJSON);
	if(recvStr=="") return TRANS_NETERROR;

	int loginStat = 0;
	if (recvStr == "fail" || recvStr == "serverdown")
		loginStat = -1;
	else
	{
		SourceManager sm;
		sm.PutSource(key, recvStr);
	}
	return loginStat;
}

string TransmitionManager::Transmit(string str)
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD(1, 1);

	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) {
		return "";
	}

	if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1) {
		WSACleanup();
		return "";
	}
	SOCKET sockClient = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = inet_addr(IPADDRS.c_str());
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(PORT);
	connect(sockClient, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));
	//string str = messageJSON;
	string UTF8_str = ToUTF8(str);
	send(sockClient, UTF8_str.c_str(), strlen(str.c_str()) + 1, 0);
	//std::cout << UTF8_str << endl;
	Sleep(WAITTIME);

	char recvBuf[BUFFERSIZE]={'\0'};
	string recvStr="";
	int buflen=0;
	buflen = recv(sockClient, recvBuf, BUFFERSIZE, 0);
	int length=0; int recevelength=0;

	for(int k=0;k<4;k++)
	{
		//cout<<"length0:"<<(int)recvBuf[k]<<" ";
		length|=(0xff&(int)recvBuf[k])<<k*8;
	}
	//cout<<"length:"<<(unsigned int)length<<endl;
	for(int j=4;j<buflen;j++)
		recvStr+=recvBuf[j];
	recevelength+=buflen-4;
	while(1)
	{
		if(recevelength>=length)
			break;
		Sleep(WAITTIME);
		buflen = recv(sockClient, recvBuf, BUFFERSIZE, 0);
		if(buflen < 0)
		{
			if(errno == EAGAIN) break;
			else return "";
		}
		else if(buflen == 0)
		{
			break;
		}

		for(int j=0;j<buflen;j++)
			recvStr+=recvBuf[j];
		recevelength+=buflen;
		//cout<<"recevelength:"<<recevelength<<endl;
	}
	closesocket(sockClient);
	WSACleanup();
	return recvStr;
}

wstring TransmitionManager::StringToWString(const std::string &str)
{
	std::wstring wstr(str.length(), L' ');
	std::copy(str.begin(), str.end(), wstr.begin());
	return wstr;
}
string TransmitionManager::_ToUTF8(const wchar_t* buffer, int len)
{
	int size = ::WideCharToMultiByte(CP_UTF8, 0, buffer, len, NULL, 0, NULL, NULL);
	if (size == 0)
		return "";

	std::string newbuffer;
	newbuffer.resize(size);
	::WideCharToMultiByte(CP_UTF8, 0, buffer, len, const_cast<char*>(newbuffer.c_str()), size, NULL, NULL);

	return newbuffer;
}
//std::string ToUTF8(const std::wstring& str)  
string TransmitionManager::ToUTF8(string str)
{
	return _ToUTF8((StringToWString(str)).c_str(), (int)(StringToWString(str)).size());
}
string TransmitionManager::int2bytes(int num)
{
	//cout<<num<<":";
	string result="";
	for(int i=0;i<4;i++)
	{
		//cout<<(int)((num>>8*i)&0xff)<<"\t";
		result+=(char)((num>>8*i)&0xff);
		//cout<<result<<endl;
	}
	//cout<<endl;
	return result;
}