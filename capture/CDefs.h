/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2011-2015 Intel Corporation. All Rights Reserved.

*******************************************************************************/
#pragma once

#ifndef DEFS_HPP
#define DEFS_HPP

#include "pxcsensemanager.h"



// per-finger joint arrays to build bones
PXCHandData::JointType fingers[5][4][2] = {
		{
			{ PXCHandData::JointType::JOINT_WRIST, PXCHandData::JointType::JOINT_THUMB_BASE },
			{ PXCHandData::JointType::JOINT_THUMB_BASE, PXCHandData::JointType::JOINT_THUMB_JT1 },
			{ PXCHandData::JointType::JOINT_THUMB_JT1, PXCHandData::JointType::JOINT_THUMB_JT2 },
			{ PXCHandData::JointType::JOINT_THUMB_JT2, PXCHandData::JointType::JOINT_THUMB_TIP },
		},
		{
			{ PXCHandData::JointType::JOINT_WRIST, PXCHandData::JointType::JOINT_INDEX_BASE },
			{ PXCHandData::JointType::JOINT_INDEX_BASE, PXCHandData::JointType::JOINT_INDEX_JT1 },
			{ PXCHandData::JointType::JOINT_INDEX_JT1, PXCHandData::JointType::JOINT_INDEX_JT2 },
			{ PXCHandData::JointType::JOINT_INDEX_JT2, PXCHandData::JointType::JOINT_INDEX_TIP },
		},
		{
			{ PXCHandData::JointType::JOINT_WRIST, PXCHandData::JointType::JOINT_MIDDLE_BASE },
			{ PXCHandData::JointType::JOINT_MIDDLE_BASE, PXCHandData::JointType::JOINT_MIDDLE_JT1 },
			{ PXCHandData::JointType::JOINT_MIDDLE_JT1, PXCHandData::JointType::JOINT_MIDDLE_JT2 },
			{ PXCHandData::JointType::JOINT_MIDDLE_JT2, PXCHandData::JointType::JOINT_MIDDLE_TIP },
		},
		{
			{ PXCHandData::JointType::JOINT_WRIST, PXCHandData::JointType::JOINT_RING_BASE },
			{ PXCHandData::JointType::JOINT_RING_BASE, PXCHandData::JointType::JOINT_RING_JT1 },
			{ PXCHandData::JointType::JOINT_RING_JT1, PXCHandData::JointType::JOINT_RING_JT2 },
			{ PXCHandData::JointType::JOINT_RING_JT2, PXCHandData::JointType::JOINT_RING_TIP },
		},
		{
			{ PXCHandData::JointType::JOINT_WRIST, PXCHandData::JointType::JOINT_PINKY_BASE },
			{ PXCHandData::JointType::JOINT_PINKY_BASE, PXCHandData::JointType::JOINT_PINKY_JT1 },
			{ PXCHandData::JointType::JOINT_PINKY_JT1, PXCHandData::JointType::JOINT_PINKY_JT2 },
			{ PXCHandData::JointType::JOINT_PINKY_JT2, PXCHandData::JointType::JOINT_PINKY_TIP },
		}
};

#endif