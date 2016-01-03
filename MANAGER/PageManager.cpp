#include "PageManager.h"

PageManager::PageManager(){}

 void PageManager::GetModelByUserID(vector<ModelVideo> &result,string username,int index)
{
	SourceManager sm;
	if(index==-1)
	{
		sm.FlushOutRequest(SERVICE_GMBU);
		index=0;
	}
	for(int i=index;i<index+MAXATONCE;i++)
		//ask for moodels from index to index+ MAX AT ONCE
	{
		stringstream ss;
		ss<<i;string strindex;ss>>strindex;
		string msg="{'username':'"+username+"','index':'"+strindex+"'}";
		
		ModelVideo mv;
		if(sm.GetModel(mv,SERVICE_GMBU, msg)!=SUCCESS)
			return;
		if (mv.m_sVideoID!="")
			result.push_back(mv);
	}
	return;
}
void PageManager::GetModelByFavor(vector<ModelVideo> &result,string favorid,int index)
{
	SourceManager sm;
	if(index==-1)//if the index is -1 then fflush all from source pool
	{
		sm.FlushOutRequest(SERVICE_GMBF);
		index=0;
	}
	for(int i=index;i<index+MAXATONCE;i++)
		//ask for moodels from index to index+ MAX AT ONCE
	{
		stringstream ss;
		ss<<i;string strindex;ss>>strindex;
		string msg="{'tag':'"+favorid+"','index':'"+strindex+"''}";

		ModelVideo mv;
		if(sm.GetModel(mv,SERVICE_GMBF, msg)!=SUCCESS)
			return;
		if (mv.m_sVideoID != "")
			result.push_back(mv);
	}
	return;
}
void PageManager::GetModel(vector<ModelVideo> &result,int index)
{
	SourceManager sm;
	if(index==-1)
	{
		sm.FlushOutRequest(SERVICE_GM);
		index=0;
	}
	for(int i=index;i<index+MAXATONCE;i++)
		//ask for moodels from index to index+ MAX AT ONCE
	{
		stringstream ss;
		ss<<i;string strindex;ss>>strindex;
		string msg="{'index':'"+strindex+"'}";
		ModelVideo mv;
		if(sm.GetModel(mv,SERVICE_GM, msg)!=SUCCESS)
			return;
		if (mv.m_sVideoID != "")
			result.push_back(mv);
	}
	return;
}
void PageManager::GetModelByVideoID(vector<ModelVideo>&result , string videoID)
{
	SourceManager sm;
	string msg = "{'videoID':'" + videoID + "'}";
	ModelVideo mv;
	if (sm.GetModel(mv, SERVICE_GMBV, msg) != SUCCESS)
		return;
	if (mv.m_sVideoID != "")
		result.push_back(mv);
}
