
#ifndef __STDAFX_H__
#define __STDAFX_H__

/** �������õ�ͷ�ļ� */
#include <windows.h>
#include <stdio.h>
#include <math.h>                            
#include <time.h>

/** ����glͷ�ļ� */
#include <gl\gl.h>				 
#include <gl\glu.h>
#include <glaux.h>
#include <glext.h>

/** ����OpenGL���ӿ��ļ� */
#pragma comment(lib, "opengl32.lib")		
#pragma comment(lib, "glu32.lib")							
#pragma comment(lib, "glaux.lib")	

/**< ��ֹ��������������ת���ľ��� */
#pragma warning(disable: 4311)                                 
#pragma warning(disable: 4312)
#pragma warning(disable: 4244)
#pragma warning(disable: 4018)
#pragma warning(disable: 4267)


/** ����������� */
const unsigned int MAP_WIDTH = 1024;
const unsigned int CELL_WIDTH = 16;

#endif