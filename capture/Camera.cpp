#include <iostream>

#include "camera.h"


const static float StepScale = 0.1f;

const float M_PI = 3.1415926535;

float Camera::rad2deg(float rad)
{
	return (float)(rad*180.0 / M_PI);
}

//===========================================================================//

void Camera::translate(const float x, const float y, const float z, float mat4x4[16])
{
	indentity(mat4x4);
	mat4x4[12] = x;
	mat4x4[13] = y;
	mat4x4[14] = z;
}

//===========================================================================//

void Camera::scale(const float x, const float y, const float z, float mat4x4[16])
{
	indentity(mat4x4);
	mat4x4[0] = x;
	mat4x4[5] = y;
	mat4x4[10] = z;
}

//===========================================================================//

void  Camera::multMat(float lhsmat4x4[16], float rhsmat4x4[16], float outmat4x4[16]) const
{
	// c1
	outmat4x4[0] = lhsmat4x4[0] * rhsmat4x4[0] + lhsmat4x4[4] * rhsmat4x4[1] + lhsmat4x4[8] * rhsmat4x4[2] + lhsmat4x4[12] * rhsmat4x4[3];
	outmat4x4[1] = lhsmat4x4[1] * rhsmat4x4[0] + lhsmat4x4[5] * rhsmat4x4[1] + lhsmat4x4[9] * rhsmat4x4[2] + lhsmat4x4[13] * rhsmat4x4[3];
	outmat4x4[2] = lhsmat4x4[2] * rhsmat4x4[0] + lhsmat4x4[6] * rhsmat4x4[1] + lhsmat4x4[10] * rhsmat4x4[2] + lhsmat4x4[14] * rhsmat4x4[3];
	outmat4x4[3] = lhsmat4x4[3] * rhsmat4x4[0] + lhsmat4x4[7] * rhsmat4x4[1] + lhsmat4x4[11] * rhsmat4x4[2] + lhsmat4x4[15] * rhsmat4x4[3];

	//c2
	outmat4x4[4] = lhsmat4x4[0] * rhsmat4x4[4] + lhsmat4x4[4] * rhsmat4x4[5] + lhsmat4x4[8] * rhsmat4x4[6] + lhsmat4x4[12] * rhsmat4x4[7];
	outmat4x4[5] = lhsmat4x4[1] * rhsmat4x4[4] + lhsmat4x4[5] * rhsmat4x4[5] + lhsmat4x4[9] * rhsmat4x4[6] + lhsmat4x4[13] * rhsmat4x4[7];
	outmat4x4[6] = lhsmat4x4[2] * rhsmat4x4[4] + lhsmat4x4[6] * rhsmat4x4[5] + lhsmat4x4[10] * rhsmat4x4[6] + lhsmat4x4[14] * rhsmat4x4[7];
	outmat4x4[7] = lhsmat4x4[3] * rhsmat4x4[4] + lhsmat4x4[7] * rhsmat4x4[5] + lhsmat4x4[11] * rhsmat4x4[6] + lhsmat4x4[15] * rhsmat4x4[7];

	//c3
	outmat4x4[8] = lhsmat4x4[0] * rhsmat4x4[8] + lhsmat4x4[4] * rhsmat4x4[9] + lhsmat4x4[8] * rhsmat4x4[10] + lhsmat4x4[12] * rhsmat4x4[11];
	outmat4x4[9] = lhsmat4x4[1] * rhsmat4x4[8] + lhsmat4x4[5] * rhsmat4x4[9] + lhsmat4x4[9] * rhsmat4x4[10] + lhsmat4x4[13] * rhsmat4x4[11];
	outmat4x4[10] = lhsmat4x4[2] * rhsmat4x4[8] + lhsmat4x4[6] * rhsmat4x4[9] + lhsmat4x4[10] * rhsmat4x4[10] + lhsmat4x4[14] * rhsmat4x4[11];
	outmat4x4[11] = lhsmat4x4[3] * rhsmat4x4[8] + lhsmat4x4[7] * rhsmat4x4[9] + lhsmat4x4[11] * rhsmat4x4[10] + lhsmat4x4[15] * rhsmat4x4[11];

	//c4
	outmat4x4[12] = lhsmat4x4[0] * rhsmat4x4[12] + lhsmat4x4[4] * rhsmat4x4[13] + lhsmat4x4[8] * rhsmat4x4[14] + lhsmat4x4[12] * rhsmat4x4[15];
	outmat4x4[13] = lhsmat4x4[1] * rhsmat4x4[12] + lhsmat4x4[5] * rhsmat4x4[13] + lhsmat4x4[9] * rhsmat4x4[14] + lhsmat4x4[13] * rhsmat4x4[15];
	outmat4x4[14] = lhsmat4x4[2] * rhsmat4x4[12] + lhsmat4x4[6] * rhsmat4x4[13] + lhsmat4x4[10] * rhsmat4x4[14] + lhsmat4x4[14] * rhsmat4x4[15];
	outmat4x4[15] = lhsmat4x4[3] * rhsmat4x4[12] + lhsmat4x4[7] * rhsmat4x4[13] + lhsmat4x4[11] * rhsmat4x4[14] + lhsmat4x4[15] * rhsmat4x4[15];
}

void Camera::resetGlobalTransformation()
{
	m_xMov = 0;
	m_yMov = 0;
	m_zMov = 0;

	m_scaleFactor = 1;
	m_zoomFactor = 1;

	m_xTrans = 0;
	m_yTrans = 0;

	indentity(m_globalTransformation);
	indentity(m_rotMatrix);
}

//===========================================================================//

Camera::Camera()
{
	resetGlobalTransformation();
	rotate = false;

	m_zoom = -0.2f;
}

//===========================================================================//

void Camera::indentity(float mat4x4[16])
{
	memset(mat4x4, 0, 16 * sizeof(float));
	mat4x4[0] = 1;
	mat4x4[5] = 1;
	mat4x4[10] = 1;
	mat4x4[15] = 1;

}

//===========================================================================//

void Camera::rotX(float angle, float mat4x4[16])
{
	float s = sin(angle);
	float c = cos(angle);

	indentity(mat4x4);

	mat4x4[5] = c;  mat4x4[9] = -s;
	mat4x4[6] = s; mat4x4[10] = c;
}

//===========================================================================//

void Camera::rotY(float angle, float mat4x4[16])
{
	float s = sin(angle);
	float c = cos(angle);

	indentity(mat4x4);

	mat4x4[0] = c;  mat4x4[8] = s;
	mat4x4[2] = -s; mat4x4[10] = c;
}

//===========================================================================//

void Camera::rotZ(float angle, float mat4x4[16])
{
	float s = sin(angle);
	float c = cos(angle);

	indentity(mat4x4);

	mat4x4[0] = c;  mat4x4[4] = -s;
	mat4x4[1] = s; mat4x4[5] = c;
}

//===========================================================================//

void Camera::setXRotation(const float angle)
{
	float sourceRot[16], rotXMat[16];
	memcpy_s(sourceRot, sizeof(float) * 16, m_rotMatrix, sizeof(float) * 16);
	rotX(rad2deg(m_yMov), rotXMat);
	multMat(rotXMat, sourceRot, m_rotMatrix);
}

//===========================================================================//

void Camera::setYRotation(const float angle)
{
	float sourceRot[16], rotYMat[16];
	memcpy_s(sourceRot, sizeof(float) * 16, m_rotMatrix, sizeof(float) * 16);
	rotY(rad2deg(m_xMov), rotYMat);
	multMat(rotYMat, sourceRot, m_rotMatrix);
}

//===========================================================================//

void Camera::setZRotation(const float angle)
{
	float sourceRot[16], rotZMat[16];
	memcpy_s(sourceRot, sizeof(float) * 16, m_rotMatrix, sizeof(float) * 16);
	rotZ(rad2deg(m_zMov), rotZMat);
	multMat(rotZMat, sourceRot, m_rotMatrix);
}

//===========================================================================//

void Camera::OnMouseMove(int x, int y)
{
	// The movement
	int dx = x - m_lastPosX;
	int dy = y - m_lastPosY;

	float divAngle = 5000.0f;

	m_xMov = (float)dx / divAngle;
	m_yMov = (float)dy / divAngle;

	setYRotation(m_yMov);
	setXRotation(m_xMov);

	m_lastPosX = x;
	m_lastPosY = y;
}

//===========================================================================//

void Camera::OnMouseDown(int button, int state, int x, int y)
{
	// Right Mouse Button
	if (button == GLUT_RIGHT_BUTTON)
	{
		resetGlobalTransformation();
	}

	//Scroll up
	if (button == 3)
	{
		// Disregard redundant GLUT_UP events
		if (state == GLUT_UP) return;
		m_zoomFactor += 0.05f;
	}

	//Scroll down
	if (button == 4)
	{
		// Disregard redundant GLUT_UP events
		if (state == GLUT_DOWN) return;
		m_zoomFactor -= 0.05f;
	}

	if (m_zoomFactor < 0.4f)
		m_zoomFactor = 0.4f;

	if (m_zoomFactor >= 3.f)
		m_zoomFactor = 3.f;


	m_lastPosX = x;
	m_lastPosY = y;
}

//===========================================================================//

void Camera::computeGlobalTransformation(float x, float y, float z)
{
	float transMat4x4[16];
	float tempMat4x4[16];
	// Move to skeleton center of mass
	translate(x, y, z, transMat4x4);

	// Apply viewing transformations
	multMat(transMat4x4, m_rotMatrix, tempMat4x4);

	// Move back to the original position
	translate(-x, -y, -z, transMat4x4);
	multMat(tempMat4x4, transMat4x4, m_globalTransformation);

	// Apply zoom
	scale(m_zoomFactor, m_zoomFactor, m_zoomFactor, transMat4x4);
	multMat(tempMat4x4, transMat4x4, m_globalTransformation);
}

//===========================================================================//

void Camera::getGlobalTransformation(float mat4x4[16])
{
	memcpy_s(mat4x4, sizeof(float) * 16, m_globalTransformation, sizeof(float) * 16);
}

