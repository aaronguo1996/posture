/****************************************************************/
/*	TransitionManager.h											*/
/*	From FDK  2015/07/22										*/
/*	From Rainue 2015/07/22										*/
/*	CopyRight													*/
/****************************************************************/

#ifndef   _TRANMANAGER_
#define   _TRANMANAGER_
#include <Winsock2.h>
#include "SourceManager.h"
#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <Map>
#include <string>
#include <sstream>

using namespace std;

/****************************************************************/
//Defines
#define SUCCESS		0x00000000	//success!
//Error For Transmit
#define TRANS_UNKNOWERR	0x00010001	//UNKNOW NETWORK ERROR
#define TRANS_USEREXIST	0x00010002	//the user is already exist
#define TRANS_LOGINERR	0x00010003	//error while login
#define TRANS_NETERROR	0x00010004	//network error

//Service Flag
#define SERVICE_REGISTER	0x10000001	//Register
#define SERVICE_LOGIN		0x10000002	//Login
#define SERVICE_LOGOUT		0x10000003	//Logout
#define SERVICE_CHANGE_PRO	0x10000004	//Change Profile
#define SERVICE_SHARE		0x10000005	//Share
#define SERVICE_UNSHARE		0x10000006	//Remove Share
#define SERVICE_COMMEND		0x10000007	//Commend
#define SERVICE_UNCOMMEND	0x10000008	//UnCommend
#define SERVICE_COMMENT		0x10000009	//Comment
#define SERVICE_UNCOMMENT	0x1000000a	//UnComment
#define SERVICE_FAVOR		0x1000000b	//Favor
#define SERVICE_UNFAVOR		0x1000000c	//UnFavor
#define SERVICE_FOLLOW		0x1000000d	//Follow
#define SERVICE_UNFOLLOW	0x1000000e	//UnFollow
#define SERVICE_GMBU		0x10000011	//Get Models By Username
#define SERVICE_GMBF		0x10000012	//Get Models By Favor
#define SERVICE_GM			0x10000013	//Get Models
#define SERVICE_GMBV		0x10000014	//Get Models By VideoID

#define SERVICE_GPBU		0x10000021	//Get Profile By Username
#define SERVICE_GFILE		0x10000031	//Get Model File
#define SERVICE_GIMAGE		0x10000032	//Get Image
#define SERVICE_GOBJ		0X10000033	//Get Object
#define SERVICE_GCARD		0X10000034	//Get Card

#define SERVICE_UPLOAD		0x10000041	//upload the video
#define SERVICE_REMOVE		0x10000042	//remove the video
#define SERVICE_CGMPRO		0x10000043	//change model profile
static string IPADDRS;
#define PORT	39998
#define WAITTIME	10
#define BUFFERSIZE	4096
/****************************************************************/
class TransmitionManager
{
public:
	TransmitionManager();

	//the func for login
	static int TransmitLogin(int, string);

	//the func for file
	static int TransmitSendFile(int, string,string path);
	static int TransmitRecvFile(int, string,string);

	//the func for transmit message 2 & from the server
	static int TransmitMessage(int, string);
	static int TransmitGetMessage(int, string msg,string key);


	static string Transmit(string);
private:
	friend class SourceManager;
	static wstring StringToWString(const std::string &str);
	static string _ToUTF8(const wchar_t* buffer, int len);
	static string ToUTF8(string str);
	static string int2bytes(int num);

};
#endif