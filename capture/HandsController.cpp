#include "HandsController.h"

HandsController::HandsController(HandsModel* model, IView* view)
{
	m_model = model;
	m_view = view;
	m_skeletonTree = new Tree<PXCHandData::JointData>[MAX_NUMBER_OF_HANDS];
	m_skeletonTreeTmp = new Tree<PXCHandData::JointData>[MAX_NUMBER_OF_HANDS];
	m_model->initSkeletonTree(m_skeletonTree);
	m_model->initSkeletonTree(m_skeletonTreeTmp);
}

//===========================================================================//

void HandsController::updateView()
{
	// Pause the sequence if the user ordered the view to
	m_model->pause(m_view->pause());

	m_skeletonTreeTmp = m_model->getSkeletonTree();

	m_model->setSkeleton(m_skeletonTree);

	// Send skeleton to display
	m_view->display3DSkeleton(m_skeletonTreeTmp, m_model->hasLeftHand(), m_model->hasRightHand());

	m_skeletonTree = m_skeletonTreeTmp;

	int width = m_model->get2DImageWidth();
	int height = m_model->get2DImageHeight();

	pxcBYTE* image = new pxcBYTE[sizeof(pxcBYTE) * width * height * 4];

	m_model->get2DImage(image);

	// Send 2D image to display
	//m_view->display2DImage(image, width, height);

	m_view->displayFps(m_timer.Tick());

	delete[] image;
}

//===========================================================================//

HandsController::~HandsController()
{

}