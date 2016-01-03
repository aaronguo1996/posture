
#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "stdafx.h"
#include "Vector3.h"                

/** 摄像机类 */
class CameraDisplay
{
public:

	/** 构造函数和析构函数 */
	CameraDisplay();
	~CameraDisplay();

	/** 获得摄像机状态方法 */
	Vector3 getPosition()   { return m_Position; }
	Vector3 getView()	    { return m_View; }
	Vector3 getUpVector()   { return m_UpVector; }
	float   getSpeed()      { return m_Speed; }
	float   getHeight()     { return m_Height; }

	/** 设置速度 */
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

	/** 设置摄像机的位置, 观察点和向上向量 */
	void setCamera(float positionX, float positionY, float positionZ,
		float viewX, float viewY, float viewZ,
		float upVectorX, float upVectorY, float upVectorZ);

	/** 旋转摄像机方向 */
	void rotateView(float angle, float X, float Y, float Z);

	/** 根据鼠标设置摄像机观察方向 */
	void setViewByMouse();

	/** 左右摄像机移动 */
	void yawCamera(float speed);

	/** 前后移动摄像机 */
	void moveCamera(float speed);

	/** 放置摄像机 */
	void setLook();

	//得到摄像机指针
	static CameraDisplay* GetCamera(void) { return m_pCamera; }


private:
	/** 摄像机属性 */
	static CameraDisplay  *m_pCamera;      /**< 当前全局摄像机指针 */
	Vector3        m_Position;      /**< 位置 */
	Vector3        m_View;          /**< 朝向 */
	Vector3        m_UpVector;      /**< 向上向量 */
	float          m_Speed;         /**< 速度 */
	float          m_Height;
};

#endif //__CAMERA_H__