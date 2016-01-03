/****************************************************************/
/*	ModelVideo.h												*/
/*	From Rainue	2015/07/23										*/
/*	CopyRight													*/
/****************************************************************/

#ifndef   _ModelVideo_
#define   _ModelVideo_

#include <string>
#include <vector>
using namespace std;
struct Comment
{
	string m_sCommentID;	//comments ID
	string m_sCosID;		//costomer ID
	string m_sDate;			//comment date
	string m_sContains;		//comments
	
};
class ModelVideo
{
public:
	string m_sVideoID;		//video ID
	string m_sOutLine;		//video OUTLINE
	string m_sPublisher;	//video po name
	string m_sDescribe;		//video Describes
	string m_sDirectory;	//video Directory
	string m_sDate;			//video Date
	string m_sMode;			//video Mode
	string m_sFavor;
	vector<string> m_vCommendsName;
	vector<Comment> m_vComments;
							//video Comments
	void addComments(Comment cmt)
	{
		m_vComments.push_back(cmt);
	}
	void addCommendsName(string cmdsname)
	{
		m_vCommendsName.push_back(cmdsname);
	}
	bool ifCommend(string username)
	{
		for(int i=0;i<m_vCommendsName.size();i++)
		{
			if(username==m_vCommendsName[i])
				return true;
		}
		return false;
	}
};

#endif