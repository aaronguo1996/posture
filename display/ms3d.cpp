#include "ms3d.h"

//-------------------------------------------------------------
//- Load
//- Loads an MS3D file into memory
//-------------------------------------------------------------
bool CMs3d::Load(const char * szFilename)
{
	unsigned char * ucpBuffer = 0;
	unsigned char * ucpPtr = 0;
	int offset = 0;
	//Open the file
	FILE * f = fopen(szFilename, "rb");
	if (!f)
	{

		return false;
	}

	//Get file size
	fseek(f, 0, SEEK_END);
	int iEnd = ftell(f);
	fseek(f, 0, SEEK_SET);
	int iStart = ftell(f);
	unsigned int uiSize = iEnd - iStart;
	//Allocate memory
	ucpBuffer = new unsigned char[uiSize];
	ucpPtr = ucpBuffer;
	if (!ucpBuffer)
	{

		return false;
	}
	//Read file into buffer
	if (fread(ucpBuffer, 1, uiSize, f) != uiSize)
	{

		delete[] ucpBuffer;
		return false;
	}
	fclose(f);

	//Check out the header, it should be 10 bytes, MS3D000000
	if (memcmp(ucpPtr, "MS3D000000", 10) != 0)
	{

		delete[] ucpBuffer;
		return false;
	}
	//Check the version (should be 3 or 4)
	ucpPtr += 10;
	if (*(int *)ucpPtr != 3 && *(int *)ucpPtr != 4)
	{

		delete[] ucpBuffer;
		return false;
	}
	ucpPtr += 4;

	//Read the vertices
	//Number of vertices
	m_usNumVerts = *(unsigned short *)ucpPtr; 
	ucpPtr += 2; offset += 16;
	//Allocate memory
	m_pVertices = new SMs3dVertex[m_usNumVerts];
	//Copy the vertices
	memcpy(m_pVertices, ucpPtr, m_usNumVerts * sizeof(SMs3dVertex));
	ucpPtr += m_usNumVerts * sizeof(SMs3dVertex);
	offset += m_usNumVerts * sizeof(SMs3dVertex);
	//Read the triangles
	m_usNumTriangles = *(unsigned short *)ucpPtr; 
	ucpPtr += 2; offset += 2;
	//Alloc memory for triangles
	m_pTriangles = new SMs3dTriangle[m_usNumTriangles];
	//Copy triangles
	memcpy(m_pTriangles, ucpPtr, m_usNumTriangles * sizeof(SMs3dTriangle));
	ucpPtr += m_usNumTriangles * sizeof(SMs3dTriangle);
	offset += m_usNumTriangles * sizeof(SMs3dTriangle); 
	//Load mesh groups
	m_usNumMeshes = *(unsigned short *)ucpPtr; 
	ucpPtr += 2; offset += 2;
	//Alloc memory for the mesh data
	m_pMeshes = new SMs3dMesh[m_usNumMeshes];
	//Copy the mesh data
	for (int x = 0; x < m_usNumMeshes; x++)
	{
		//Copy the first part of the data
		memcpy(&m_pMeshes[x], ucpPtr, 35);
		ucpPtr += 35; offset += 35;
		//Allocate triangle index memory
		m_pMeshes[x].m_uspIndices = new unsigned short[m_pMeshes[x].m_usNumTris];
		//Copy triangle index data, plus the material index
		memcpy(m_pMeshes[x].m_uspIndices, ucpPtr, m_pMeshes[x].m_usNumTris * 2);
		ucpPtr += m_pMeshes[x].m_usNumTris * 2; offset += m_pMeshes[x].m_usNumTris * 2;
		m_pMeshes[x].m_cMaterial = ucpPtr[0];
		ucpPtr++; offset++;
	}

	//Read material information
	m_usNumMaterials = *(unsigned short *)ucpPtr; 
	ucpPtr += 2; offset += 2;
	//Alloc memory
	m_pMaterials = new SMs3dMaterial[m_usNumMaterials];
	//Copy material information
	for (int x = 0; x < m_usNumMaterials; x++)
	{
		memcpy(&m_pMaterials[x], ucpPtr, 361);
		ucpPtr += 361; offset += 361;
		//Load the images
		if (m_pMaterials[x].m_cTexture[0] != '\0')
		{
			m_pMaterials[x].m_Texture.Load(&m_pMaterials[x].m_cTexture[2]);
		}
	}

	//Skip some data we do not need
	ucpPtr += 4;
	ucpPtr += 8;
	offset += 12;
	//Read in joint and animation info
	m_usNumJoints = *(unsigned short *)ucpPtr; 
	ucpPtr += 2;
	//Allocate memory
	m_pJoints = new SMs3dJoint[m_usNumJoints];
	//Read in joint info
	for (int x = 0; x < m_usNumJoints; x++)
	{
		memcpy(&m_pJoints[x], ucpPtr, 93);
		ucpPtr += 93;
		//Allocate memory 
		m_pJoints[x].m_RotKeyFrames = new SMs3dKeyFrame[m_pJoints[x].m_usNumRotFrames];
		m_pJoints[x].m_TransKeyFrames = new SMs3dKeyFrame[m_pJoints[x].m_usNumTransFrames];
		//copy keyframe information
		memcpy(m_pJoints[x].m_RotKeyFrames, ucpPtr, m_pJoints[x].m_usNumRotFrames * sizeof(SMs3dKeyFrame));
		ucpPtr += m_pJoints[x].m_usNumRotFrames * sizeof(SMs3dKeyFrame);
		memcpy(m_pJoints[x].m_TransKeyFrames, ucpPtr, m_pJoints[x].m_usNumTransFrames * sizeof(SMs3dKeyFrame));
		ucpPtr += m_pJoints[x].m_usNumTransFrames * sizeof(SMs3dKeyFrame);
		if (x == 0)
		{
			m_fTotalTime = m_pJoints[0].m_RotKeyFrames[m_pJoints[0].m_usNumRotFrames - 1].m_fTime;
		}
	}

	//Find the parent joint array indices
	for (int x = 0; x < m_usNumJoints; x++)
	{
		//If the bone has a parent
		if (m_pJoints[x].m_cParent[0] != '\0')
		{
			//Compare names of theparent bone of x with the names of all bones
			for (int y = 0; y < m_usNumJoints; y++)
			{
				//A match has been found
				if (strcmp(m_pJoints[y].m_cName, m_pJoints[x].m_cParent) == 0)
				{
					m_pJoints[x].m_sParent = y;
				}
			}
		}
		//The bone has no parent
		else
		{
			m_pJoints[x].m_sParent = -1;
		}
	}

	//Setup joints 
	Setup();

	//File loaded
	delete[] ucpBuffer;

	if (m_eDisplayMode == HANDNOBJECT)
	{
		m_pCard = new Card("joker.bmp");
		m_pCard->Load("card_info.txt");
	}
	
	return true;
}

//-------------------------------------------------------------
//- Render
//- Renders the model in its position at time 0
//-------------------------------------------------------------
void CMs3d::Render()
{
	//Note: This function really isn't needed, as it preforms the same basic function
	//      as the render function below.  It is included to provide an implementation of the
	//      Render() function put forth in the CModel class.
	float f;
	Animate(1.0f, 0.0f, 0.0f, false, &f);
}

//-------------------------------------------------------------
//- Render
//- Renders the model as it would be at time "fTime" (in seconds)
//-------------------------------------------------------------
void CMs3d::Render(float fTime)
{
	float f;
	Animate(1.0f, fTime, fTime, false, &f);
}

//-------------------------------------------------------------
//- Animate
//- Animates the model from start time to end time (in seconds)
//- at specified speed and can loop
//-------------------------------------------------------------
void CMs3d::Animate(float fSpeed, float fStartTime, float fEndTime, bool bLoop, float * fCurTime)
{
	static bool bFirstTime = true;
	//First time animate has been called
	if (bFirstTime)
	{
		Reset();
		bFirstTime = false;
	}

	static float fLastTime = fStartTime;

	float fTime = m_Timer.GetSeconds() * fSpeed;
	fTime += fLastTime;
	fLastTime = fTime;
	*fCurTime = fLastTime;

	//looping
	if (fTime > fEndTime)
	{
		if (bLoop)
		{
			Reset();
			fLastTime = fStartTime;
			fTime = fStartTime;
		}
		else
			fTime = fEndTime;
	}

	if (m_eDisplayMode == HANDNOBJECT)
	    m_pCard->Render(fTime);

	for (int x = 0; x < m_usNumJoints; x++)
	{
		//Transformation matrix
		CMatrix4X4 matTmp;
		//Current joint
		SMs3dJoint * pJoint = &m_pJoints[x];
		//Current frame
		unsigned int uiFrame = 0;

		//if there are no keyframes, don't do any transformations
		if (pJoint->m_usNumRotFrames == 0 && pJoint->m_TransKeyFrames == 0)
		{
			pJoint->m_matFinal = pJoint->m_matAbs;
			continue;
		}
		//Calculate the current frame
		//Translation
		while (uiFrame < pJoint->m_usNumTransFrames && pJoint->m_TransKeyFrames[uiFrame].m_fTime < fTime)
			uiFrame++;
		pJoint->m_usCurTransFrame = uiFrame;

		float fTranslation[3];
		float fDeltaT = 1;
		float fInterp = 0;

		//If its at the extremes
		if (uiFrame == 0)
			memcpy(fTranslation, pJoint->m_TransKeyFrames[0].m_fParam, sizeof(float[3]));
		else if (uiFrame == pJoint->m_usNumTransFrames)
			memcpy(fTranslation, pJoint->m_TransKeyFrames[uiFrame - 1].m_fParam, sizeof(float[3]));
		//If its in the middle of two frames
		else
		{
			SMs3dKeyFrame * pkCur = &pJoint->m_TransKeyFrames[uiFrame];
			SMs3dKeyFrame * pkPrev = &pJoint->m_TransKeyFrames[uiFrame - 1];

			fDeltaT = pkCur->m_fTime - pkPrev->m_fTime; animate_time = fTime;
			fInterp = (fTime - pkPrev->m_fTime) / fDeltaT;

			//Interpolate between the translations
			fTranslation[0] = pkPrev->m_fParam[0] + (pkCur->m_fParam[0] - pkPrev->m_fParam[0]) * fInterp;
			fTranslation[1] = pkPrev->m_fParam[1] + (pkCur->m_fParam[1] - pkPrev->m_fParam[1]) * fInterp;
			fTranslation[2] = pkPrev->m_fParam[2] + (pkCur->m_fParam[2] - pkPrev->m_fParam[2]) * fInterp;
		}
		//Calculate the current rotation
		uiFrame = 0;
		while (uiFrame < pJoint->m_usNumRotFrames && pJoint->m_RotKeyFrames[uiFrame].m_fTime < fTime)
			uiFrame++;


		//If its at the extremes
		if (uiFrame == 0)
			matTmp.SetRotation(pJoint->m_RotKeyFrames[0].m_fParam);
		else if (uiFrame == pJoint->m_usNumTransFrames)
			matTmp.SetRotation(pJoint->m_RotKeyFrames[uiFrame - 1].m_fParam);
		//If its in the middle of two frames, use a quaternion SLERP operation to calculate a new position
		else
		{
			SMs3dKeyFrame * pkCur = &pJoint->m_RotKeyFrames[uiFrame];
			SMs3dKeyFrame * pkPrev = &pJoint->m_RotKeyFrames[uiFrame - 1];

			fDeltaT = pkCur->m_fTime - pkPrev->m_fTime;
			fInterp = (fTime - pkPrev->m_fTime) / fDeltaT;

			//Create a rotation quaternion for each frame
			CQuaternion qCur;
			CQuaternion qPrev;
			qCur.FromEulers(pkCur->m_fParam);
			qPrev.FromEulers(pkPrev->m_fParam);
			//SLERP between the two frames
			CQuaternion qFinal = SLERP(qPrev, qCur, fInterp);

			//Convert the quaternion to a rotation matrix
			matTmp = qFinal.ToMatrix4();
		}

		//Set the translation part of the matrix
		matTmp.SetTranslation(fTranslation);

		//Calculate the joints final transformation
		CMatrix4X4 matFinal = pJoint->m_matLocal * matTmp;

		//if there is no parent, just use the matrix you just made
		if (pJoint->m_sParent == -1)
			pJoint->m_matFinal = matFinal;
		//otherwise the final matrix is the parents final matrix * the new matrix
		else
			pJoint->m_matFinal = m_pJoints[pJoint->m_sParent].m_matFinal * matFinal;
	}


	//Transform and render the meshes
	if (m_bDrawMesh)
		RenderT();

	if (m_bDrawBones)
	{
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_LIGHTING);
		glLineWidth(5);
		//Draw the bones
		glBegin(GL_LINES);
		for (int x = 1; x < m_usNumJoints; x++)
		{
			float * fMat = m_pJoints[x].m_matFinal.Get();
			float * fMatParent = m_pJoints[m_pJoints[x].m_sParent].m_matFinal.Get();
			glVertex3f(fMat[12], fMat[13], fMat[14]);
			glVertex3f(fMatParent[12], fMatParent[13], fMatParent[14]);
		}
		glEnd();
		glEnable(GL_DEPTH_TEST);
	}
}

//-------------------------------------------------------------
//- RenderT 
//- Transform and render the meshes
//-------------------------------------------------------------
void CMs3d::RenderT()
{
	glEnable(GL_TEXTURE_2D);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	for (int x = 0; x < m_usNumMeshes; x++)
	{
		//Set up materials
		if (m_pMeshes[x].m_cMaterial >= 0)
		{
			SMs3dMaterial * pCurMat = &m_pMaterials[m_pMeshes[x].m_cMaterial];
			//Set the alpha for transparency
			pCurMat->m_fDiffuse[3] = pCurMat->m_fTransparency;

			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, pCurMat->m_fAmbient);
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, pCurMat->m_fDiffuse);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, pCurMat->m_fSpecular);
			glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, pCurMat->m_fEmissive);
			glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, pCurMat->m_fShininess);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			//Texture map
			pCurMat->m_Texture.Bind();
		}
		else
			glDisable(GL_BLEND);

		//Draw mesh
		//Transformed vertices and normals
		CVector3 vecNormal;
		CVector3 vecVertex;

		glBegin(GL_TRIANGLES);
		//Loop through triangles
		for (int y = 0; y < m_pMeshes[x].m_usNumTris; y++)
		{
			//Set triangle pointer to triangle #1

			SMs3dTriangle * pTri = &m_pTriangles[m_pMeshes[x].m_uspIndices[y]];
			//Loop through each vertex 
			for (int z = 0; z < 3; z++)
			{
				//Get the vertex
				SMs3dVertex * pVert = &m_pVertices[pTri->m_usVertIndices[z]];

				//If it has no bone, render as is
				if (pVert->m_cBone == -1)
				{
					//Send all 3 components without modification
					glTexCoord2f(pTri->m_fTexCoords[0][z], pTri->m_fTexCoords[1][z]);
					glVertex3fv(pVert->m_vVert.Get());
					glNormal3fv(pTri->m_vNormals[z].Get());
				}
				//Otherwise, transform the vertices and normals before displaying them
				else
				{
					//Send the texture coordinates
					glTexCoord2f(pTri->m_fTexCoords[0][z], pTri->m_fTexCoords[1][z]);

					SMs3dJoint * pJoint = &m_pJoints[pVert->m_cBone];
					//Transform the normals
					vecNormal = pTri->m_vNormals[z];
					//Only rotate it, no translation
					vecNormal.Transform3(pJoint->m_matFinal);
					//Send the normal to OpenGL
					glNormal3fv(vecNormal.Get());

					//Transform the vertex
					vecVertex = pVert->m_vVert;
					//translate as well as rotate
					vecVertex.Transform4(pJoint->m_matFinal);
					//Send vertex to openGL
					glVertex3fv(vecVertex.Get());

				}
			}
		}

		glEnd();
	}
}

//-------------------------------------------------------------
//- Reset
//- Reset the model
//-------------------------------------------------------------
void CMs3d::Reset()
{
	m_Timer.Init();
	m_Timer.GetSeconds();
}

//-------------------------------------------------------------
//- SwapBoneDraw
//- Turn the display of bones on and off
//-------------------------------------------------------------
void CMs3d::SwapBoneDraw()
{
	m_bDrawBones = !m_bDrawBones;
}

//-------------------------------------------------------------
//- SwapMeshDraw
//- Turn the display of the meshes on and off
//-------------------------------------------------------------
void CMs3d::SwapMeshDraw()
{
	m_bDrawMesh = !m_bDrawMesh;
}

//-------------------------------------------------------------
//- AreBonesEnabled
//- Check if bones are being drawn
//-------------------------------------------------------------
bool CMs3d::AreBonesEnabled()
{
	return m_bDrawBones;
}


//-------------------------------------------------------------
//- AreMeshesEnabled
//- Check if meshes are being drawn
//-------------------------------------------------------------
bool CMs3d::AreMeshesEnabled()
{
	return m_bDrawMesh;
}

//-------------------------------------------------------------
//- Setup
//- Get the joints set up to their beggining positions
//-------------------------------------------------------------
void CMs3d::Setup()
{
	//Go through each joint
	for (int x = 0; x < m_usNumJoints; x++)
	{
		m_pJoints[x].m_matLocal.SetRotation(m_pJoints[x].m_fRotation);
		m_pJoints[x].m_matLocal.SetTranslation(m_pJoints[x].m_fPosition);

		//Set the Abs transformations to the parents transformations, combined with their own local ones
		if (m_pJoints[x].m_sParent != -1)
		{
			m_pJoints[x].m_matAbs = m_pJoints[m_pJoints[x].m_sParent].m_matAbs * m_pJoints[x].m_matLocal;

		}
		//		//If there is no parent
		else
		{
			m_pJoints[x].m_matAbs = m_pJoints[x].m_matLocal;
		}
		m_pJoints[x].m_matFinal = m_pJoints[x].m_matAbs;
	}
	//Go through each vertex
	for (int x = 0; x < m_usNumVerts; x++)
	{
		//If there is no bone..
		if (m_pVertices[x].m_cBone == -1)
			continue;

		CMatrix4X4 * mat = &m_pJoints[m_pVertices[x].m_cBone].m_matFinal;


		mat->InverseTranslateVec(m_pVertices[x].m_vVert.Get());
		mat->InverseRotateVec(m_pVertices[x].m_vVert.Get());
	}
	//Go through the normals and transform them
	for (int x = 0; x < m_usNumTriangles; x++)
	{
		SMs3dTriangle * pTri = &m_pTriangles[x];

		//Loop through each index
		for (int z = 0; z < 3; z++)
		{
			//Get the vertex so we can find out what joint we need to use to transform the normal
			SMs3dVertex * pVert = &m_pVertices[pTri->m_usVertIndices[z]];

			//if it is not attached to a bone, don't do any transforms
			if (pVert->m_cBone == -1)
				continue;

			SMs3dJoint * pJoint = &m_pJoints[pVert->m_cBone];

			//Transform the normal
			pJoint->m_matFinal.InverseRotateVec(pTri->m_vNormals[z].Get());

		}
	}
}

//-------------------------------------------------------------
//- Constructors
//- 1. Default contructor
//- 2. Destructor
//-------------------------------------------------------------
CMs3d::CMs3d(std::string displayMode)
{
	m_pVertices = 0;
	m_pTriangles = 0;
	m_pMeshes = 0;
	m_pMaterials = 0;
	m_bDrawMesh = true;
	m_bDrawBones = false;
	m_Timer.Init();
	animate_time = 0;
	m_pCard = 0;

	if (displayMode == "0")
		m_eDisplayMode = HAND;
	else if (displayMode == "1")
		m_eDisplayMode = HANDNOBJECT;
	else
		m_eDisplayMode = MINECRAFT;

}

//CMs3d::CMs3d(const char * szFilename)
//{
//	m_pVertices = 0;
//	m_pTriangles = 0;
//	m_pMeshes = 0;
//	m_pMaterials = 0;
//	m_bDrawMesh = true;
//	m_bDrawBones = false;
//	m_Timer.Init();
//	Load(szFilename);
//}

CMs3d::~CMs3d()
{
	if (m_pVertices)
	{
		delete[] m_pVertices;
		m_pVertices = 0;
	}
	if (m_pTriangles)
	{
		delete[] m_pTriangles;
		m_pTriangles = 0;
	}
	if (m_pMeshes)
	{
		delete[] m_pMeshes;
		m_pMeshes = 0;
	}
	if (m_pMaterials)
	{
		delete[] m_pMaterials;
		m_pMaterials = 0;
	}
	if (m_pCard)
		delete m_pCard;
}

float CMs3d::TotalTime()
{
	return m_fTotalTime;
}