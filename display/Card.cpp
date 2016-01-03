
#include <fstream>
#include <sstream>
#include "Card.h"

Card::Card(const char * fileName)
{
	m_pFrames = NULL;
	// Load Texture
	m_pTexture = new CBMPLoader();
	m_pTexture->Load(fileName);

	m_usNumFrames = 0;
	m_fLimitTime = 0.0f;
}

Card::~Card()
{
	delete[] m_pFrames;
	//delete m_pTexture;
}

bool Card::Load(const char * szFilename)
{
	std::ifstream ifs(szFilename);
	std::string line;
	std::stringstream ss;

	getline(ifs, line);
	ss << line;
	ss >> m_usNumFrames;
	m_pFrames = new ObjectFrame[m_usNumFrames];
	int tmpInt;
	float tmpFloat;
	for (int i = 0; i < m_usNumFrames; i++)
	{
		getline(ifs, line);
		ss.clear();
		ss << line;
		ss >> tmpInt;
		ss >> tmpFloat;
		m_pFrames[i].m_fTime = tmpFloat;
		for (int j = 0; j < 4; j++)
		{
			getline(ifs, line);
			ss.clear();
			ss << line;
			ss >> tmpInt;
			for (int k = 0; k < 3; k++)
			{
				ss >> tmpFloat;
				m_pFrames[i].m_Position[j][k] = tmpFloat;
			}
		}
	}

	return true;
}

void Card::Render(float fTime)
{
	glEnable(GL_TEXTURE_2D);
	//Move to current frame
	unsigned int uiFrame = 0;

	while (uiFrame < m_usNumFrames && m_pFrames[uiFrame].m_fTime < fTime)
		uiFrame++;
	if (uiFrame >= m_usNumFrames || m_pFrames[uiFrame].m_fTime > m_fLimitTime)
		uiFrame = m_usNumFrames - 1;

	ObjectFrame middleFrame;

	if (uiFrame == 0)
		middleFrame = m_pFrames[uiFrame];
	else
	{
		ObjectFrame prevFrame = m_pFrames[uiFrame - 1];
		ObjectFrame curFrame = m_pFrames[uiFrame];
		float fDeltaT = curFrame.m_fTime - prevFrame.m_fTime;
		float fInterp = (fTime - prevFrame.m_fTime) / fDeltaT;
		middleFrame.m_fTime = fTime;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 3; j++)
				middleFrame.m_Position[i][j] = prevFrame.m_Position[i][j] +
				(curFrame.m_Position[i][j] - prevFrame.m_Position[i][j]) * fInterp;
	}

	float scale = 0.20f;
	
	//Draw rectangle
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, m_pTexture->ID);
	glTranslatef(0.0f, 0.0f, -15.0f);
	glScalef(0.2f, 0.2f, 0.2f);
	glBegin(GL_QUADS);
	//glColor3f(0.0f,1.0f,0.0f);
	////glVertex3f(112.0f * scale, 70.0f* scale, 98.0f* scale);
	//for (int i = 0;i < 2;i++) {
	//	glVertex3f(middleFrame.m_Position[i][0] * scale, middleFrame.m_Position[i][1] * scale, middleFrame.m_Position[i][2] * scale);
	//    //APP->Log(COLOR_BLUE, "%f %f %f", currentFrame.m_Position[i][0],
	//		//currentFrame.m_Position[i][1], currentFrame.m_Position[i][2]);
	//}
	//glVertex3f(middleFrame.m_Position[3][0] * scale, middleFrame.m_Position[3][1] * scale, middleFrame.m_Position[3][2] * scale);
	//glVertex3f(middleFrame.m_Position[2][0] * scale, middleFrame.m_Position[2][1] * scale, middleFrame.m_Position[2][2] * scale);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(middleFrame.m_Position[0][0] * scale, middleFrame.m_Position[0][1] * scale, middleFrame.m_Position[0][2] * scale);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(middleFrame.m_Position[1][0] * scale, middleFrame.m_Position[1][1] * scale, middleFrame.m_Position[1][2] * scale);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(middleFrame.m_Position[3][0] * scale, middleFrame.m_Position[3][1] * scale, middleFrame.m_Position[3][2] * scale);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(middleFrame.m_Position[2][0] * scale, middleFrame.m_Position[2][1] * scale, middleFrame.m_Position[2][2] * scale);
	glEnd();
	
	glPopMatrix();
}

void Card::setLimitTime(float LimitTime)
{
	m_fLimitTime = LimitTime;
}