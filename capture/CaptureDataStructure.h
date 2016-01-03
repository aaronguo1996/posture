
#ifndef _CAPTUREDATASTRUCTURE_
#define _CAPTUREDATASTRUCTURE_

const int JOINTS_NUM = 21;
const int OBJECT_VERTICES_NUM = 4;

typedef float Positions[JOINTS_NUM][3];
typedef float ObjectPosition[OBJECT_VERTICES_NUM][3];

enum { BOTTOM_LEFT, BOTTOM_RIGHT, TOP_LEFT, TOP_RIGHT };

struct Frame
{
	float m_fTime;
	Positions m_Positions;
};

struct FrameObject
{
	float m_fTime;
	ObjectPosition m_Position;
};

#endif // _CAPTUREDATASTRUTURE_