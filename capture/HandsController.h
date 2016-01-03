#pragma once

#ifndef HANDSCONTROLLER_H
#define	HANDSCONTROLLER_H

#include <thread>
#include <mutex>

#include "HandsModel.h"
#include "OpenGlView.h"

#include "timer.h"

class HandsController
{
public:
	HandsController(HandsModel* model, IView* view);
	void updateView();
	~HandsController();
private:
	HandsModel* m_model;
	IView *m_view;

	Tree<PXCHandData::JointData>* m_skeletonTree;
	Tree<PXCHandData::JointData>* m_skeletonTreeTmp;

	std::mutex m_mutex;

	FPSTimer m_timer;
};

#endif // HANDSCONTROLLER_H