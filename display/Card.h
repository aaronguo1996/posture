
#ifndef CARD_H
#define CARD_H

#include "CBMPLoader.h"
#include "capture/CaptureDataStructure.h"

//-------------------------------------------------------------
//                        Object Frame
//-------------------------------------------------------------
//const int OBJECT_VERTICES_NUM = 4;
//typedef float ObjectPosition[OBJECT_VERTICES_NUM][3];

struct ObjectFrame
{
	float m_fTime;
	ObjectPosition m_Position;
};

class Card
{
public:

	Card(const char * szFilename);
	~Card();

	bool Load(const char * szFilename);
	void Render(float fTime);

	void setLimitTime(float fLimitTime);

private:

	unsigned short m_usNumFrames;
	float m_fLimitTime;
	ObjectFrame * m_pFrames;
	CBMPLoader * m_pTexture;

};

#endif // CARD_H