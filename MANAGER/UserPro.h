/****************************************************************/
/*	UserPro.h													*/
/*	From Rainue	2015/07/23										*/
/*	CopyRight													*/
/****************************************************************/

#ifndef   _USERPRO_
#define   _USERPRO_

#include <string>
#include <vector>
using namespace std;

class UserPro
{
public:
	string m_sUserName;			//username
	string m_sUserID;			//userID
	string m_sEmail;			//e-mail
	vector<string> m_vFavors;	//favors
	vector<string> m_vFollows;	//follows

	//favor
	void addFavors(string fav)
	{
		m_vFavors.push_back(fav);
	}
	//followers
	void addFollows(string fol)
	{
		m_vFollows.push_back(fol);
	}
};
#endif