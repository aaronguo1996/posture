
#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "stdafx.h"
#include "Vector3.h"                

/** ������� */
class CameraDisplay
{
public:

	/** ���캯������������ */
	CameraDisplay();
	~CameraDisplay();

	/** ��������״̬���� */
	Vector3 getPosition()   { return m_Position; }
	Vector3 getView()	    { return m_View; }
	Vector3 getUpVector()   { return m_UpVector; }
	float   getSpeed()      { return m_Speed; }
	float   getHeight()     { return m_Height; }

	/** �����ٶ� */
	void setSpeed(float speed)
	{
		m_Speed = speed;
	}

	void upHeight()
	{
		m_Height += 5.0f;
	}

	void downHeight()
	{
		m_Height -= 5.0f;
	}

	void accelerate()
	{
		if (m_Speed < 3.0f)
		    m_Speed += 0.1f;
	}

	void slow()
	{
		if (m_Speed > 0)
			m_Speed -= 0.1f;
	}

	/** �����������λ��, �۲����������� */
	void setCamera(float positionX, float positionY, float positionZ,
		float viewX, float viewY, float viewZ,
		float upVectorX, float upVectorY, float upVectorZ);

	/** ��ת��������� */
	void rotateView(float angle, float X, float Y, float Z);

	/** �����������������۲췽�� */
	void setViewByMouse();

	/** ����������ƶ� */
	void yawCamera(float speed);

	/** ǰ���ƶ������ */
	void moveCamera(float speed);

	/** ��������� */
	void setLook();

	//�õ������ָ��
	static CameraDisplay* GetCamera(void) { return m_pCamera; }


private:
	/** ��������� */
	static CameraDisplay  *m_pCamera;      /**< ��ǰȫ�������ָ�� */
	Vector3        m_Position;      /**< λ�� */
	Vector3        m_View;          /**< ���� */
	Vector3        m_UpVector;      /**< �������� */
	float          m_Speed;         /**< �ٶ� */
	float          m_Height;
};

#endif //__CAMERA_H__