#pragma once

#ifndef IVIEW_H
#define	IVIEW_H

#include "pxcsensemanager.h"

#include "Tree.h"

class IView
{
public:
	virtual void renderScene() = 0;
	virtual void display3DSkeleton(Tree<PXCHandData::JointData>* skeletonTree, bool hasLeftHand, bool hasRightHand) = 0;
	virtual void display3DSpace() = 0;
	virtual void displayFps(pxcI32 fps) = 0;
	virtual void display2DImage(pxcBYTE* image, pxcI32 width, pxcI32 height) = 0;
	virtual bool pause() = 0;
	virtual bool stop() = 0;
	virtual bool isPause() = 0;
	virtual ~IView() {}
};


#endif	/* IVIEW_H */