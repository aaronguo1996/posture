
#ifndef __SKYBOX_H__
#define __SKYBOX_H__

#include "Vector3.h"
#include "CameraDisplay.h"
#include "CBMPLoader.h"

/** ��պ��� */
class CSkyBox
{
public:
	/** ���캯�� */
	CSkyBox();
	~CSkyBox();

	/** ��ʼ�� */
	bool init();

	/** ��Ⱦ */
	void render();

private:

	CBMPLoader m_texture[5];   /**< ��պ����� */
	Vector3    m_CameraPos;    /**< ��ǰ�����λ�� */
	float      length;         /**< ���� */
	float      width;          /**< ��� */
	float      height;         /**< �߶� */
	float      yRot;           /**< ��Y����ת */

};

#endif ///__SKY_BOX__