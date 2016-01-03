/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2014 Intel Corporation. All Rights Reserved.

*******************************************************************************/

#pragma once
#include "pxctracker.h"
#include <vector>

class Model
{
public:
	Model()
	{
		model_filename[0] = '\0';
		pxcCHAR *filename = L"jiaotongka.png";
		wcsncpy_s<1024>(model_filename, filename, 1024);
	}

	Model(pxcCHAR *filename)
	{
		filename = L"jiaotongka.png";
		wcsncpy_s<1024>(model_filename, filename, 1024);
	}

	struct TrackingState
	{
		pxcUID	cosID;
		pxcCHAR friendlyName[256];
		bool	isTracking;
	};

	void addCosID(pxcUID cosID, pxcCHAR *friendlyName)
	{
		TrackingState state;
		state.cosID = cosID;
		wcscpy_s<256>(state.friendlyName, friendlyName);
		state.isTracking = false;

		cosIDs.push_back(state);
	}

	pxcCHAR  model_filename[1024];
	std::vector<TrackingState> cosIDs;
};

typedef std::vector<Model>::iterator				TargetIterator;
typedef std::vector<Model::TrackingState>::iterator TrackingIterator;

typedef enum
{
	TRACKING_2D,
	TRACKING_3D,
	TRACKING_INSTANT,
} TrackingType;

typedef enum
{
	MAP_CREATE,
	MAP_EXTEND,
	MAP_ALIGN,
} MapOperation;
