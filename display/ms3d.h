
#ifndef MS3D_H
#define MS3D_H

//-------------------------------------------------------------
//                       INCLUDES                             -
//-------------------------------------------------------------
#include "image.h"
#include "timer.h"
#include "math.h"
#include "model.h"
#include "Card.h"
#include "Vector3.h"
#include "matrix.h"
#include <string>

#pragma pack(push, packing)
#pragma pack(1)
//-------------------------------------------------------------
//- SMs3dVertex
//- A single vertex 
struct SMs3dVertex
{
	unsigned char m_ucFlags; //Editor flags, unused for the loader
	CVector3 m_vVert;       //X,Y,Z coordinates
	char m_cBone;            //Bone ID (-1 = no bone)
	unsigned char m_ucUnused;
};

//-------------------------------------------------------------
//- SMs3dTriangle
//- Triangle data structure
struct SMs3dTriangle
{
	unsigned short m_usFlags;          //Editor flags (unused for loader)
	unsigned short m_usVertIndices[3]; //Vertex indices
	CVector3 m_vNormals[3];            //Vertex normals;
	float m_fTexCoords[2][3];          //Texture coordinates
	unsigned char m_ucSmoothing;       //Smoothing group
	unsigned char m_ucGroup;           //Group index
};

//-------------------------------------------------------------
//- SMs3dMesh
//- Group of triangles in the ms3d file
struct SMs3dMesh
{
	unsigned char m_ucFlags;   //Editor flags again
	char m_cName[32];          //Name of the mesh
	unsigned short m_usNumTris;//Number of triangles in the group
	unsigned short * m_uspIndices; //Triangle indices
	char m_cMaterial;          //Material index, -1 = no material

	//Let itclean up after itself like usual
	SMs3dMesh()
	{
		m_uspIndices = 0;
	}
	~SMs3dMesh()
	{
		if (m_uspIndices)
		{
			delete[] m_uspIndices;
			m_uspIndices = 0;
		}
	}
};

//-------------------------------------------------------------
//- SMs3dMaterial
//- Material information for the mesh
struct SMs3dMaterial
{
	char m_cName[32];         //Material name
	float m_fAmbient[4];      //Ambient values
	float m_fDiffuse[4];      //Diffuse values
	float m_fSpecular[4];     //Specular values
	float m_fEmissive[4];     //Emissive values
	float m_fShininess;       //0 - 128
	float m_fTransparency;    //0 - 1
	char m_cMode;             //unused
	char m_cTexture[128];     //Texture map file
	char m_cAlpha[128];       //Alpha map file
	CImage m_Texture;
};

//-------------------------------------------------------------
//- SMs3dKeyFrame
//- Rotation/Translation information for joints
struct SMs3dKeyFrame
{
	float m_fTime;     //Time at which keyframe is started
	float m_fParam[3]; //Translation or Rotation values
};

//-------------------------------------------------------------
//- SMs3dJoint
//- Bone Joints for animation
struct SMs3dJoint
{
	//Data from file
	unsigned char m_ucpFlags;             //Editor flags
	char m_cName[32];                     //Bone name
	char m_cParent[32];                   //Parent name
	float m_fRotation[3];                 //Starting rotation
	float m_fPosition[3];                 //Starting position
	unsigned short m_usNumRotFrames;      //Numbee of rotation frames
	unsigned short m_usNumTransFrames;    //Number of translation frames

	SMs3dKeyFrame * m_RotKeyFrames;       //Rotation keyframes
	SMs3dKeyFrame * m_TransKeyFrames;     //Translation keyframes

	//Data not loaded from file
	short m_sParent;                     //Parent joint index

	CMatrix4X4 m_matLocal;
	CMatrix4X4 m_matAbs;
	CMatrix4X4 m_matFinal;

	unsigned short m_usCurRotFrame;
	unsigned short m_usCurTransFrame;

	//Clean up after itself like usual
	SMs3dJoint()
	{
		m_RotKeyFrames = 0;
		m_TransKeyFrames = 0;
		m_usCurRotFrame = 0;
		m_usCurTransFrame = 0;
	}
	~SMs3dJoint()
	{
		if (m_RotKeyFrames)
		{
			delete[] m_RotKeyFrames;
			m_RotKeyFrames = 0;
		}
		if (m_TransKeyFrames)
		{
			delete[] m_TransKeyFrames;
			m_TransKeyFrames = 0;
		}
	}
};

#pragma pack(pop, packing)

enum DisplayMode { HAND, HANDNOBJECT, MINECRAFT };

class CMs3d
{
public:

	//Load the MS3D file
	bool Load(const char * szFilename);
	//Render the MS3D in its current position
	void Render();
	//Render the MS3D at a certain time (in seconds)
	void Render(float fTime);
	//Animate the model from based on time (seconds)
	void Animate(float fSpeed, float fStartTime, float fEndTime, bool bLoop, float * fCurTime);

	//Turn the drawing of bones on and off
	void SwapBoneDraw();
	//Turn the drawing of the mesh on and off
	void SwapMeshDraw();
	//Check if displays of bones and meshes are on or off
	bool AreBonesEnabled();
	bool AreMeshesEnabled();


	//Constructors
	CMs3d();
	//CMs3d(const char * szFilename);
	CMs3d(std::string displayMode);
	//Destructor
	~CMs3d();

	float TotalTime();
	float getAnimateTime() { return animate_time; }

private:

	//Total time for model animation
	float m_fTotalTime;

	//Draw the bones?
	bool m_bDrawBones;
	//Draw the mesh?
	bool m_bDrawMesh;

	//Setup joints
	void Setup();
	//Reset the timer
	void Reset();
	//Render the transformed vertices
	void RenderT();

	//Data
	unsigned short m_usNumVerts;
	unsigned short m_usNumTriangles;
	unsigned short m_usNumMeshes;
	unsigned short m_usNumMaterials;
	unsigned short m_usNumJoints;
	unsigned short m_usNumObjectFrames;

	SMs3dVertex * m_pVertices;
	SMs3dTriangle * m_pTriangles;
	SMs3dMesh * m_pMeshes;
	SMs3dMaterial * m_pMaterials;
	SMs3dJoint * m_pJoints;

	Card * m_pCard;

	//Timer
	CTimer m_Timer;
	float animate_time;

	//Display Mode
	DisplayMode m_eDisplayMode;

};

#endif //MS3D_H