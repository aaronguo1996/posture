/****************************************************************/
/*	SourceManager.h												*/
/*	From FDK  2015/07/22										*/
/*	From Rainue 2015/07/24										*/
/*	CopyRight													*/
/****************************************************************/
#ifndef   _SourceManager_
#define   _SourceManager_

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "ModelVideo.h"
#include "UserPro.h"
#include "json\json.h"
#include "TransmitionManager.h"
#include "UserManager.h"

using namespace std;
using namespace Json;

#define SUCCESS			0x00000000	//success!
#define TRANS_NETERROR	0x00010004	//network error
class SourceManager
{
public:
	SourceManager();
	ModelVideo GetModelVideo(string messageJSON);

	//the func for put into source pool
	int PutSource(string, string);

	//the func for get profile
	void GetUserProfile(UserPro &userpro);
	void GetUserProfile(UserPro &userpro,string username);

	//the func for get model from server
	int GetModel(ModelVideo &modelvideo,int request,string msg);

	//the func for get lastchangedvideo
	void GetLastVideo(ModelVideo &modelvideo);

	//the func for clear source pool
	int FlushOutRequest(int request);
	int FlushOutRequest(string request);
	void Flush(string key);
private:

};
static map<string, string>sourcePool;

#endif