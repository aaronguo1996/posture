#include "UserManager.h"

UserManager::UserManager()
	:m_luserId(""),m_bifLogin(false)
{
}

void UserManager::SetUserid(string userid)
{
	this->m_luserId=userid;
}

string UserManager::GetUserid()
{
	return m_luserId;
}

void UserManager::SetUsername(string username)
{
	this->m_susername=username;
}

string UserManager::GetUsername()
{
	return m_susername;
}

int UserManager::Login(string username,string pwd)
{
	Replace(username);
	Replace(pwd);

	if(username.size()>USERNAMEMAX)
		return  USERNAME2L;
	if(pwd.size()>PASSWORDMAX)
		return PASSWORD2L;

	//create json
	string msg="{'username':'"+username+"','password':'"+pwd+"'}";

	TransmitionManager trans;
	if(trans.TransmitLogin(SERVICE_LOGIN, msg)==SUCCESS)
	{
		m_bifLogin=true;
		UserPro us; SourceManager sm;
		sm.GetUserProfile(us);

		//set the userid and the username
		m_luserId=us.m_sUserID;
		m_susername=us.m_sUserName;
		//cout<<m_luserId<<endl;
		return SUCCESS;
	}
	return LOGINFAIL;
}

int UserManager::Logout()
{
	this->m_luserId="";
	this->m_susername="";
	this->m_bifLogin=	false;
	sourcePool.clear();
	return SUCCESS;
}

int UserManager::Register(string username,string pwd,string pwdc,string email)
{
	Replace(username);
	Replace(pwd);
	Replace(pwdc);
	if(username.length()==0||pwd.length()==0||pwdc.length()==0||email.length()==0)
		//IF THE input is empty
	{
		return EMPTYINFO;
	}
	//to find if the input is too long
	if(username.size()>USERNAMEMAX)
		return  USERNAME2L;
	if(pwd.size()>PASSWORDMAX)
		return PASSWORD2L;
	if(pwdc.size()>PASSWORDMAX)
		return PASSWORD2L;
	if(username.find_first_of(ILLEGAL)!=string::npos)
	{
		return ILEGALUSR;
	}
	if(pwd!=pwdc)//if the password not consist
	{
		return PWDNOTCON;
	}

	if(pwd.length()<PASSWORDLENGTH)//if the password is too short
	{
		return PWDTOOSIM;
	}

	if(!this->IsValidEmail(email))
		return EMAILFAIL;

	//create json
	string msg="{'username':'"+username+"','password':'"+pwd+"','email':'"+email+"'}";
	TransmitionManager trans;
	if(trans.TransmitMessage(SERVICE_REGISTER, msg)!=SUCCESS)
		return USEREXIST;
	//[TODO]comfirm the message to the server 

	return SUCCESS;
}
bool UserManager::IsValidChar(char ch) 
{
	if( (ch>=97) && (ch<=122) ) //a~z
		return true;
	if( (ch>=65) && (ch<=90) ) //A~Z
		return true;
	if((ch>=48) && (ch<=57)) //0~9
		return true;
	if( ch==95 || ch==45 || ch==46 || ch==64 ) //_-.@
		return true;
	return false;
}
bool UserManager::IsValidEmail(string strEmail)
{
	if( strEmail.length()<5 )
		return false;

	char ch = strEmail[0];
	if( ch!='@'&&ch!='.')//the first char is @ or . then return false;
	{
		int atCount =0;
		int atPos = 0;
		int dotCount = 0;
		for(int i=1;i<strEmail.length();i++)
		{
			ch = strEmail[i];
			if(IsValidChar(ch))
			{
				if(ch==64) //"@"
				{
					atCount ++;
					atPos = i;
				}
				else if( (atCount>0) && (ch==46) )//after@is.
					dotCount ++;
			}
			else
				return false;
		}
		//end is not @ or .
		if( ch == 46 )
			return false;
		if( (atCount!=1) || (dotCount<1) || (dotCount>3) )
			return false;
		//"@."pr".@"
		int x,y;
		x=strEmail.find("@.");
		y=strEmail.find(".@");
		if( x>0 || y>0 )
		{
			return false;
		}
		return true;
	}
	return false;
}

int UserManager::ChangeProfile(string pwd,string pwdc,string email)
{
	Replace(pwd);
	Replace(pwdc);

	if (pwd.size()>PASSWORDMAX)
		return PASSWORD2L;

	if(this->m_bifLogin==false)//check if login
		return NOLOGINED;

	if(pwd.length()==0||pwdc.length()==0||email.length()==0)
		//IF THE input is empty
	{
		return EMPTYINFO;
	}

	if(pwd!=pwdc)//if the password not consist
	{
		return PWDNOTCON;
	}

	if(pwd.length()<PASSWORDLENGTH)//if the password is too short
	{
		return PWDTOOSIM;
	}

	if(!this->IsValidEmail(email))
		return EMAILFAIL;

	//[TODO]comfirm the message to the server return USEREXIST
	string msg="{'userID':'"+m_luserId+"','username':'"+m_susername+"','password':'"+pwd+"','email':'"+email+"'}";
	TransmitionManager trans;
		
	if (trans.TransmitGetMessage(SERVICE_CHANGE_PRO, msg, "profile") != SUCCESS)
		return TRANS_NETERROR;
	return SUCCESS;
}

int UserManager::Share(string videoid)
{
	string msg="{'userID':'"+m_luserId+"','username':'"+m_susername+"','videoID':'"+videoid+"'}";
	TransmitionManager trans;
	if(trans.TransmitMessage(SERVICE_SHARE, msg)!=SUCCESS)
		return SHAREFAIL;
	return SUCCESS;
}

int UserManager::RemoveShare(string videoid)
{
	string msg="{'userID':'"+m_luserId+"','username':'"+m_susername+"','videoID':'"+videoid+"'}";
	TransmitionManager trans;
	if(trans.TransmitMessage(SERVICE_UNSHARE, msg)!=SUCCESS)
		return SHAREFAIL;
	return SUCCESS;
}
int UserManager::Commend(string videoid)
{
	string msg="{'userID':'"+m_luserId+"','username':'"+m_susername+"','videoID':'"+videoid+"'}";
	TransmitionManager trans;
	//if(trans.TransmitMessage(SERVICE_COMMEND, msg)!=SUCCESS)
	if (trans.TransmitGetMessage(SERVICE_COMMEND, msg, "lastvideo") != SUCCESS)
		return COMMEFAIL;
	return SUCCESS;
}
int UserManager::UnCommend(string videoid)
{
	string msg="{'userID':'"+m_luserId+"','username':'"+m_susername+"','videoID':'"+videoid+"'}";
	TransmitionManager trans;
	//if(trans.TransmitMessage(SERVICE_UNCOMMEND, msg)!=SUCCESS)
	if (trans.TransmitGetMessage(SERVICE_UNCOMMEND, msg, "lastvideo") != SUCCESS)
		return COMMEFAIL;
	return SUCCESS;
}
int UserManager::Comment(string videoid,string comment)
{
	Replace(comment);
	string msg="{'userID':'"+m_luserId+"','username':'"+m_susername+"','videoID':'"+videoid+"','content':'"+comment+"'}";
	TransmitionManager trans;
	//if(trans.TransmitMessage(SERVICE_COMMENT, msg)!=SUCCESS)
	if (trans.TransmitGetMessage(SERVICE_COMMENT, msg, "lastvideo") != SUCCESS)
		return COMMEFAIL;
	return SUCCESS;
}
int UserManager::RemoveComment(string commentid)
{
	string msg="{'userID':'"+m_luserId+"','username':'"+m_susername+"','commentID':'"+commentid+"'}";
	TransmitionManager trans;
	//if(trans.TransmitMessage(SERVICE_UNCOMMENT, msg)!=SUCCESS)
	if (trans.TransmitGetMessage(SERVICE_UNCOMMENT, msg, "lastvideo") != SUCCESS)
		return COMMEFAIL;
	return SUCCESS;
}
void UserManager::GetLastVideo(ModelVideo &modelvideo)
{
	SourceManager sm;
	sm.GetLastVideo(modelvideo);
}
int UserManager::Follow(string othername)
{
	Replace(othername);
	string msg="{'userID':'"+m_luserId+"','username':'"+m_susername+"','name':'"+othername+"'}";
	TransmitionManager trans;
	if(trans.TransmitGetMessage(SERVICE_FOLLOW,msg,"profile")!=SUCCESS)
		return FOLLOWERR;
	return SUCCESS;
}
int UserManager::UnFollow(string othername)
{
	Replace(othername);
	SourceManager sm; UserPro up;
	sm.GetUserProfile(up);
	for(int i=0;i<up.m_vFollows.size();i++)
	{
		if(up.m_vFollows[i]==othername)
		{
			stringstream ss;ss<<i;
			string index;ss>>index;
			string msg="{'userID':'"+m_luserId+"','username':'"+m_susername+"','index':'"+index+"','name':'"+othername+"'}";
			TransmitionManager trans;
			if(trans.TransmitGetMessage(SERVICE_UNFOLLOW,msg,"profile")!=SUCCESS)
				return FOLLOWERR;
			return SUCCESS;
		}
	}
	return FOLLOWERR;
}

int UserManager::AddFavor(string favor)
{
	Replace(favor);
	string msg="{'userID':'"+m_luserId+"','username':'"+m_susername+"','tag':'"+favor+"'}";
	TransmitionManager trans;
	if(trans.TransmitGetMessage(SERVICE_FAVOR,msg,"profile")!=SUCCESS)
		return FAVORERRO;
	return SUCCESS;
}
int UserManager::RemoveFavor(string favor)
{
	Replace(favor);
	SourceManager sm; UserPro up;
	sm.GetUserProfile(up);
	for(int i=0;i<up.m_vFavors.size();i++)
	{
		if(up.m_vFavors[i]==favor)
		{
			stringstream ss;ss<<i;
			string index;ss>>index;
			string msg="{'userID':'"+m_luserId+"','username':'"+m_susername+"','index':'"+index+"','tag':'"+favor+"'}";
			TransmitionManager trans;
			if(trans.TransmitGetMessage(SERVICE_UNFAVOR,msg,"profile")!=SUCCESS)
				return FAVORERRO;
			return SUCCESS;
		}
	}
	return FAVORERRO;
}

//the func for upload the modelvideo
int UserManager::upload(string outline,string describe,string tag,string path,string mode)
{
	Replace(outline);
	Replace(describe);
	Replace(tag);
	//stringstream sshand; string handstr;
	//sshand<<hand; sshand>>hex>>handstr;
	//stringstream ssmodel; string modestr;
	//ssmodel<<model; ssmodel>>hex>>modestr;

	string msg="{'userID':'"+m_luserId+"','username':'"+m_susername+"','outline':'"+outline+"','tag':'"+tag+"','mode':'"+mode+"','describe':'"+describe+"'}";
	TransmitionManager trans;
	if(trans.TransmitSendFile(SERVICE_UPLOAD,msg,path)!=SUCCESS)
		return UPLOADERR;
	return SUCCESS;
}

int UserManager::remove(string videoid)
{
	string msg="{'userID':'"+m_luserId+"','username':'"+m_susername+"','videoID':'"+videoid+"'}";
	TransmitionManager trans;
	if(trans.TransmitMessage(SERVICE_REMOVE, msg)!=SUCCESS)
		return UPLOADERR;

	//___________________________________________________________________________
	//____delete the user's home page and flush again____________________________
	string requeststr;
	stringstream ss;ss <<hex<< SERVICE_GMBU;
	ss >> requeststr;
	string messageJSON="{'username':'"+this->m_susername+"'";
	string key = "{'STATE':'" + requeststr + "','VALUE':" + messageJSON;
	SourceManager sm; sm.FlushOutRequest(key);
	return SUCCESS;
}

int UserManager::ChangeVideoProfile(string videoID, string describe, string tag)
{
	Replace(describe);
	Replace(tag);
	string msg = "{'userID':'" + m_luserId + "','username':'" + m_susername + "','tag':'" + "','videoID':" + videoID + "','describe':'" + describe + "'}";
	TransmitionManager trans;
	if (trans.TransmitGetMessage(SERVICE_CGMPRO, msg, "[videotmp]") != SUCCESS)
		return UPLOADERR;
	//___________________________________________________________________________
	//____delete the user's home page and flush again____________________________
	string requeststr;
	stringstream ss; ss << hex << SERVICE_GMBU;
	ss >> requeststr;
	string messageJSON = "{'username':'" + this->m_susername + "'";
	string key = "{'STATE':'" + requeststr + "','VALUE':" + messageJSON;
	SourceManager sm; sm.FlushOutRequest(key);
	return SUCCESS;
}

void UserManager::Replace(string& in)
{
	StringReplace(in, "#", "#&35");
	StringReplace(in, "'", "#&100");
	StringReplace(in, "\"", "#&34");
	StringReplace(in, "(", "#&40");
	StringReplace(in, ")", "#&41");
	StringReplace(in, "<", "#&60");
	StringReplace(in, ">", "#&62");
	StringReplace(in, "{", "#&123");
	StringReplace(in, "}", "#&125");
	StringReplace(in, "[", "#&91");
	StringReplace(in, "]", "#&93");
}
void UserManager::Recover(string& in)
{
	StringReplace(in, "#&93", "]");
	StringReplace(in, "#&91", "[");
	StringReplace(in, "#&125", "}");
	StringReplace(in, "#&123", "{");
	StringReplace(in, "#&62", ">");
	StringReplace(in, "#&60", "<");
	StringReplace(in, "#&41", ")");
	StringReplace(in, "#&40", "(");
	StringReplace(in, "#&34", "\"");
	StringReplace(in, "#&100", "'");
	StringReplace(in, "#&35", "#");
}
void UserManager::StringReplace(string &strBase, string strSrc, string strDes)
{
	string::size_type pos = 0;
	string::size_type srcLen = strSrc.size();
	string::size_type desLen = strDes.size();
	pos = strBase.find(strSrc, pos);
	while ((pos != string::npos))
	{
		strBase.replace(pos, srcLen, strDes);
		pos = strBase.find(strSrc, (pos + desLen));
	}
}
