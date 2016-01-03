#include "SourceManager.h"
SourceManager::SourceManager()
{
}
int SourceManager::PutSource(string key,string sourceJSON)
{
	sourcePool[key] = sourceJSON;
	return 0;
}
void SourceManager::GetUserProfile(UserPro &userpro)
{
	UserManager um;
	string JSON=sourcePool["profile"];//get JSON From sourcepool
	//cout<<JSON<<endl;
	Reader reader;Value value;//the JSON Reader and Json value
	if (reader.parse(JSON,value)) 
	{
		if (!value["userID"].isNull())
		{
			userpro.m_sUserID = value["userID"].asString();
			//cout << userpro.m_sUserID << endl;
		}
		if (!value["email"].isNull())
		{
			userpro.m_sEmail= value["email"].asString();
			//cout << userpro.m_sEmail << endl;
		}
		if (!value["username"].isNull())
		{
			string username = value["username"].asString();
			um.Recover(username);
			userpro.m_sUserName = username;
			//cout << userpro.m_sUserName << endl;
		}
		Value val_array = value["tags"];
		int iSize = val_array.size();
		for (int nIndex = 0; nIndex < iSize; ++nIndex)
		{
			string tag = val_array[nIndex].asString();
			um.Recover(tag);
			userpro.addFavors(tag);
			//add favor into userprofile
			//cout <<"Add user favors:"<< val_array[nIndex].asString() << endl;
		}
		val_array = value["follows"];
		iSize = val_array.size();
		for (int nIndex = 0; nIndex < iSize; ++nIndex)
		{
			string follow = val_array[nIndex].asString();
			um.Recover(follow);
			userpro.addFollows(follow);
			//add favor into userprofile
			//cout <<"Add user Follows:"<< val_array[nIndex].asString() << endl;
		}
	}
	//userpro.m_sUserID=JSON.substr(JSON.find("\"userID\":\"")+10,JSON.find("\",\"email\"")-JSON.find("\"userID\":\"")-10);
	return;
}
void SourceManager::GetUserProfile(UserPro &userpro,string username)
{
	UserManager um;
	um.Replace(username);

	string key="Userprofile["+username+"]";
	map<string,string>::iterator it =sourcePool.find(key);
	if (it==sourcePool.end())
		//if there's no userProfile in it then get through transmition manager
	{
		string msg="{'username':'"+username+"'}";
		TransmitionManager trans;
		if(trans.TransmitGetMessage(SERVICE_GPBU,msg,key)!=SUCCESS)
			return;
	}
	string JSON=sourcePool[key];//get JSON From sourcepool
	//cout<<JSON<<endl;
	Reader reader;Value value;//the JSON Reader and Json value
	if (reader.parse(JSON,value))
	{
		if (!value["userID"].isNull())
		{
			userpro.m_sUserID = value["userID"].asString();
			//cout << userpro.m_sUserID << endl;
		}
		if (!value["email"].isNull())
		{
			userpro.m_sEmail= value["email"].asString();
			//cout << userpro.m_sEmail << endl;
		}
		if (!value["username"].isNull())
		{
			string urname = value["username"].asString();
			um.Recover(urname);
			userpro.m_sUserName = urname;
			//cout << userpro.m_sUserName << endl;
		}
		Value val_array = value["tags"];
		int iSize = val_array.size();
		for (int nIndex = 0; nIndex < iSize; ++nIndex)
		{
			string tag = val_array[nIndex].asString();
			um.Recover(tag);
			userpro.addFavors(tag);
			//add favor into userprofile
			//cout <<"Add user favors:"<< val_array[nIndex].asString() << endl;
		}
		val_array = value["follows"];
		iSize = val_array.size();
		for (int nIndex = 0; nIndex < iSize; ++nIndex)
		{
			string follow = val_array[nIndex].asString();
			um.Recover(follow);
			userpro.addFollows(follow);
			//add favor into userprofile
			//cout <<"Add user Follows:"<< val_array[nIndex].asString() << endl;
		}
	}
	//userpro.m_sUserID=JSON.substr(JSON.find("\"userID\":\"")+10,JSON.find("\",\"email\"")-JSON.find("\"userID\":\"")-10);
	return;
}
void SourceManager::GetLastVideo(ModelVideo &modelvideo)
{
	UserManager um;
	string JSON = sourcePool["lastvideo"];//get JSON From sourcepool
	if (JSON.size() == 0)
		return;
	//cout<<JSON<<endl;
	Reader reader; Value value;//the JSON Reader and Json value
	if (reader.parse(JSON, value))
	{
		if (!value["videoID"].isNull())
		{
			modelvideo.m_sVideoID = value["videoID"].asString();
		}
		if (!value["outline"].isNull())
		{
			string outline = value["outline"].asString();
			um.Recover(outline);
			modelvideo.m_sOutLine = outline;
		}
		if (!value["directory"].isNull())
		{
			modelvideo.m_sDirectory = value["directory"].asString();
		}
		if (!value["mode"].isNull())
		{
			modelvideo.m_sMode = value["mode"].asString();
		}
		if (!value["describe"].isNull())
		{
			string describe = value["describe"].asString();
			um.Recover(describe);
			modelvideo.m_sDescribe = describe;
		}
		if (!value["username"].isNull())
		{
			string publisher = value["username"].asString();
			um.Recover(publisher);
			modelvideo.m_sPublisher = publisher;
		}
		if (!value["tag"].isNull())
		{
			string tag = value["tag"].asString();
			um.Recover(tag);
			modelvideo.m_sFavor = tag;
		}
		if (!value["date"].isNull())
		{
			modelvideo.m_sDate = value["date"].asString();
		}
		Value val_array = value["comments"];
		int iSize = val_array.size();
		modelvideo.m_vComments.clear();
		for (int nIndex = 1; nIndex < iSize; ++nIndex)
		{
			Comment cmt;
			if (!val_array[nIndex]["commentID"].isNull())
				cmt.m_sCommentID = val_array[nIndex]["commentID"].asString();
			if (!val_array[nIndex]["username"].isNull())
			{
				string comment = val_array[nIndex]["username"].asString();
				um.Recover(comment);
				cmt.m_sCosID = comment;
			}
			if (!val_array[nIndex]["content"].isNull())
			{
				string content = val_array[nIndex]["content"].asString();
				um.Recover(content);
				cmt.m_sContains = content;
			}
			if (!val_array[nIndex]["date"].isNull())
				cmt.m_sDate = val_array[nIndex]["date"].asString();
			modelvideo.addComments(cmt);
			//add favor into userprofile
			//cout <<"Add user favors:"<< val_array[nIndex].asString() << endl;
		}
		val_array = value["commends"];
		iSize = val_array.size();
		modelvideo.m_vCommendsName.clear();
		for (int nIndex = 0; nIndex < iSize; ++nIndex)
		{
			if (!val_array[nIndex].isNull())
			{
				string username = val_array[nIndex].asString();
				um.Recover(username);
				modelvideo.addCommendsName(username);
			}
			//add favor into userprofile
			//cout <<"Add user favors:"<< val_array[nIndex].asString() << endl;
		}
	}
	//userpro.m_sUserID=JSON.substr(JSON.find("\"userID\":\"")+10,JSON.find("\",\"email\"")-JSON.find("\"userID\":\"")-10);
	return;
}
int SourceManager::GetModel(ModelVideo &modelvideo,int request,string messageJSON)
{
	UserManager um;
	stringstream ss;ss <<hex<< request;string requeststr;ss >> requeststr;
	string key = "{'STATE':'" + requeststr + "','VALUE':" + messageJSON + "}";
	map<string,string>::iterator it =sourcePool.find(key);
	if (it==sourcePool.end())
		//if there's no userProfile in it then get through transmition manager
	{
		TransmitionManager trans;
		if(trans.TransmitGetMessage(request,messageJSON,key)!=SUCCESS)
			return TRANS_NETERROR;
	}
	string JSON=sourcePool[key];//get JSON From sourcepool
	//cout<<JSON<<endl;
	Reader reader;Value value;//the JSON Reader and Json value
	if (reader.parse(JSON, value))
	{
		if (!value["videoID"].isNull())
		{
			modelvideo.m_sVideoID = value["videoID"].asString();
		}
		if (!value["outline"].isNull())
		{
			string outline = value["outline"].asString();
			um.Recover(outline);
			modelvideo.m_sOutLine = outline;
		}
		if (!value["directory"].isNull())
		{
			modelvideo.m_sDirectory = value["directory"].asString();
		}
		if (!value["mode"].isNull())
		{
			modelvideo.m_sMode = value["mode"].asString();
		}
		if (!value["describe"].isNull())
		{
			string describe = value["describe"].asString();
			um.Recover(describe);
			modelvideo.m_sDescribe = describe;
		}
		if (!value["username"].isNull())
		{
			string publisher = value["username"].asString();
			um.Recover(publisher);
			modelvideo.m_sPublisher = publisher;
		}
		if (!value["date"].isNull())
		{
			modelvideo.m_sDate = value["date"].asString();
		}
		if (!value["tag"].isNull())
		{
			string tag = value["tag"].asString();
			um.Recover(tag);
			modelvideo.m_sFavor = tag;
		}
		Value val_array = value["comments"];
		int iSize = val_array.size();
		for (int nIndex = 1; nIndex < iSize; ++nIndex)
		{
			Comment cmt;
			if (!val_array[nIndex]["commentID"].isNull())
				cmt.m_sCommentID = val_array[nIndex]["commentID"].asString();
			if (!val_array[nIndex]["username"].isNull())
			{
				string comment = val_array[nIndex]["username"].asString();
				um.Recover(comment);
				cmt.m_sCosID = comment;
			}
			if (!val_array[nIndex]["content"].isNull())
			{
				string content = val_array[nIndex]["content"].asString();
				um.Recover(content);
				cmt.m_sContains = content;
			}
			if (!val_array[nIndex]["date"].isNull())
				cmt.m_sDate = val_array[nIndex]["date"].asString();
			modelvideo.addComments(cmt);
			//add favor into userprofile
			//cout <<"Add user favors:"<< val_array[nIndex].asString() << endl;
		}
		val_array = value["commends"];
		iSize = val_array.size();
		for (int nIndex = 0; nIndex < iSize; ++nIndex)
		{
			if (!val_array[nIndex].isNull())
			{
				string username = val_array[nIndex].asString();
				um.Recover(username);
				modelvideo.addCommendsName(username);
			}
			//add favor into userprofile
			//cout <<"Add user favors:"<< val_array[nIndex].asString() << endl;
		}
		TransmitionManager trans;
		//map<string, string>::iterator it = sourcePool.find("{'videoID':'" + modelvideo.m_sVideoID + "'}" + "M");
		//if (it == sourcePool.end())
		//	//if there's no userProfile in it then get through transmition manager
		//{
		//	if (trans.TransmitRecvFile(SERVICE_GIMAGE, "{'videoID':'" + modelvideo.m_sVideoID + "'}", "/image/" + modelvideo.m_sVideoID) != SUCCESS)
		//		return TRANS_NETERROR;
		//	else
		//		sourcePool["{'videoID':'" + modelvideo.m_sVideoID + "'}" + "M"] = "";
		//}
		map<string, string>::iterator it = sourcePool.find("{'videoID':'" + modelvideo.m_sVideoID + "'}" + "I");
		if (it == sourcePool.end())
		{
			if (trans.TransmitRecvFile(SERVICE_GFILE, "{'videoID':'" + modelvideo.m_sVideoID + "'}", "/model/" + modelvideo.m_sVideoID) != SUCCESS)
				return TRANS_NETERROR; 
			else
				sourcePool["{'videoID':'" + modelvideo.m_sVideoID + "'}"+"I"] = "";
		}
		/*it = sourcePool.find("{'videoID':'" + modelvideo.m_sVideoID + "'}" + "O");
		if (it == sourcePool.end())
		{
			if (trans.TransmitRecvFile(SERVICE_GOBJ, "{'videoID':'" + modelvideo.m_sVideoID + "'}", "/obj/" + modelvideo.m_sVideoID) != SUCCESS)
				return TRANS_NETERROR;
			else
				sourcePool["{'videoID':'" + modelvideo.m_sVideoID + "'}"+"O"] = "";
		}*/
		if (modelvideo.m_sMode == MODE_CARD)
		{
			it = sourcePool.find("{'videoID':'" + modelvideo.m_sVideoID + "'}" + "C");
			if (it == sourcePool.end())
			{
				if (trans.TransmitRecvFile(SERVICE_GCARD, "{'videoID':'" + modelvideo.m_sVideoID + "'}", "/card/" + modelvideo.m_sVideoID) != SUCCESS)
					return TRANS_NETERROR;
				else
					sourcePool["{'videoID':'" + modelvideo.m_sVideoID + "'}" + "C"] = "";
			}
		}
	}
	//userpro.m_sUserID=JSON.substr(JSON.find("\"userID\":\"")+10,JSON.find("\",\"email\"")-JSON.find("\"userID\":\"")-10);
	return SUCCESS;
}
int SourceManager::FlushOutRequest(int request)
{
	string requeststr;
	if(request!=0)//if the request is 0 then flush all
	{
		stringstream ss;ss <<hex<< request;ss >> requeststr;
	}
	else
		requeststr="";
	map<string, string>::iterator iter = sourcePool.begin();
	for (;iter != sourcePool.end();)//while!
	{
		if (iter->first.find("{'STATE':'"+requeststr)!=string::npos)
		{
			sourcePool.erase(iter++);
		}
		//do not need to clear the viodeos in memory
		/*else if(iter->first.find("{'videoID':")!=string::npos)
		 {
			 //cout<<iter->first<<endl;
			 //cout<<"{'videoID':'"+requeststr<<endl;
			sourcePool.erase(iter++);
		 }*/
		 else
		 {
			++iter;
		 }
	}
	return SUCCESS;
}
int SourceManager::FlushOutRequest(string request)
{
	map<string, string>::iterator iter = sourcePool.begin();
	for (;iter != sourcePool.end();)//while!
	{
		if (iter->first.find(request)!=string::npos)
		{
			sourcePool.erase(iter++);
		}
		//do not need to clear the viodeos in memory
		/*else if(iter->first.find("{'videoID':")!=string::npos)
		 {
			 //cout<<iter->first<<endl;
			 //cout<<"{'videoID':'"+requeststr<<endl;
			sourcePool.erase(iter++);
		 }*/
		 else
		 {
			++iter;
		 }
	}
	return SUCCESS;
}