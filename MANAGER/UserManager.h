/****************************************************************/
/*	UserManager.h												*/
/*	From Rainue	2015/07/21										*/
/*	CopyRight													*/
/****************************************************************/

#ifndef   _USERMANAGER_
#define   _USERMANAGER_

#include <iostream>
#include <string>

#include "TransmitionManager.h"
#include "SourceManager.h"
using namespace std;

/****************************************************************/
//Defines
#define SUCCESS		0x00000000	//success!
#define USEREXIST	0x00000001	//the user is already exist
#define PWDNOTCON	0x00000002	//the password is not Consistent
#define PWDTOOSIM	0x00000003	//the password is too simple
#define EMAILFAIL	0x00000004	//the email address is not right
#define	EMPTYINFO	0x00000005	//the information is empty
#define NOLOGINED	0x00000006	//user not login
#define LOGINFAIL	0x00000007	//cannot login
#define SHAREFAIL	0x00000008	//fail while sharing
#define COMMEFAIL	0x00000009	//fail while commend or comment
#define FOLLOWERR	0x0000000a	//fail while follow others
#define ILEGALUSR	0x0000000b	//illegal char in username
#define FAVORERRO	0x0000000c	//choose favor failed
#define UPLOADERR	0x0000000d	//error when upload
#define USERNAME2L	0x0000000e	//the username is too long
#define PASSWORD2L	0x0000000f	//the password is too long

#define HAND_BOTH	0x100
#define HAND_LEFT	0x101
#define HAND_RIGHT	0x102
#define MODE_REAL	"0"
#define MODE_CARD	"1"
#define MODE_STORY	"2"

#define PASSWORDMAX		32
#define USERNAMEMAX		32
#define PASSWORDLENGTH	6	//the min size of the password
#define ILLEGAL "-_=+|[]{};':,./\">~`!@#$%^&*()_+|-=[]{};':,./<>?"
/****************************************************************/
class UserManager
{
public:
	UserManager();

	void SetUserid(string userid);
	//the func for set userid
	string GetUserid();
	//the func for get userid

	void SetUsername(string username);
	//the func for set userid
	string GetUsername();
	//the func for get userid

	int Login(string username,string pwd);
	//the func for login
	int Logout();
	//the func for logout

	int Register(string username,string pwd,string pwdc,string email);
	//the func for register
	int ChangeProfile(string pwd,string pwdc,string email);
	//the func for change profile

	int Share(string videoid);
	int RemoveShare(string videoid);
	//the func for share

	int Commend(string videoid);
	int UnCommend(string videoid);
	//the func for commend

	int Comment(string videoid,string comment);
	int RemoveComment(string commentid);
	//the func for commentid

	void GetLastVideo(ModelVideo &modelvideo);

	int Follow(string id);
	int UnFollow(string id);
	//the func for follow

	int AddFavor(string favor);
	int RemoveFavor(string favor);
	//the func for favor

	int upload(string outline,string describe,string tag,string path,string mode);
	int remove(string videoid);
	int ChangeVideoProfile(string videoID,string describe, string tag);
	//the func for upload

	void Recover(string &in);
	void Replace(string& in);
private:
	string m_luserId;		//	user id
	string m_susername;
	bool m_bifLogin;		//	flag for if login

	static bool IsValidEmail(string strEmail);
	static bool IsValidChar(char ch);

	
	void StringReplace(string &strBase, string strSrc, string strDes);
};
#endif

/*
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
*/