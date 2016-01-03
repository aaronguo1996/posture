#ifndef OPENGLVIEW_H
#define	OPENGLVIEW_H

#pragma once
#include "Texture.hpp"
#include <iostream>
#include <mutex>
#include <string>


#include <gl/freeglut.h>
#include <gl/glew.h>
#include "IView.h"
#include "camera.h"


class OpenGLView : public IView
{
public:
	OpenGLView();
	~OpenGLView();
	virtual void renderScene();
	virtual void display3DSkeleton(Tree<PXCHandData::JointData>* skeletonTree, bool hasLeftHand, bool hasRightHand);
	virtual void display3DSpace();
	virtual void display2DImage(pxcBYTE* image, pxcI32 width, pxcI32 height);
	virtual void displayFps(pxcI32 fps);
	virtual bool pause();
	virtual bool stop();

    bool isPause() { return m_pause;  }
	void setCardCaptured(bool b) { m_isCardCaptured = b; }
	bool getCardCaptured() const { return m_isCardCaptured; }
private:
	void Init();
	static void RenderSceneCB();
	void InitializeGlutCallbacks();
	static void draw3DSkeleton(int index, bool applyTransformFlag);
	static void drawBones(int index, bool applyTransformFlag);
	static void drawJoints(int index, bool applyTransformFlag);
	static void drawFps();
	static void recursiveDrawJoints(Node<PXCHandData::JointData> node, PXCPoint3DF32 pGlobal);
	static void recursiveDrawBones(Node<PXCHandData::JointData> node, PXCPoint3DF32 pGlobal);

	static void renderBitmapString(float x, float y, void *font, const char *string);
	static void printInstructions();

	static bool OnKeyboard(int Key);
	static void SpecialKeyboardCB(int Key, int x, int y);
	static void setVSync(bool sync);

	static PXCHandData::JointData m_skeletonsData[2][22];

	static pxcBYTE* m_image;
	static Texture* DepthTex;

	static bool m_hasLeftHand;
	static bool m_hasRightHand;

	static bool m_pause;

	static Tree<PXCHandData::JointData>* m_skeletonTree;

	static std::mutex m_mutex;

	static bool m_isBones;

	static int m_fps;
	static bool m_isCardCaptured;

	bool m_stop;
};

#endif	/* OPENGLVIEW_H */