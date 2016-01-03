/****************************************************************/
/*	PageManager.h												*/
/*	From Rainue	2015/07/22										*/
/*	From														*/
/*	CopyRight													*/
/****************************************************************/

#ifndef   _PAGEMANAGER_
#define   _PAGEMANAGER_

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "TransmitionManager.h"
#include "ModelVideo.h"

using namespace std;

/****************************************************************/
//Defines
#define SUCCESS		0x00000000	//success!
#define MAXATONCE	4
/****************************************************************/
class PageManager
{
public:
	PageManager();
	void GetModelByUserID(vector<ModelVideo>&,string username,int index);
	//the func for get moleds by user id return void,will push the ModelVideo InTo vector
	void GetModelByFavor(vector<ModelVideo>&,string favorid,int index);
	//the func for get moleds by favorid return void
	void GetModel(vector<ModelVideo>&,int index);

	void GetModelByVideoID(vector<ModelVideo>&, string videoID);
};
#endif