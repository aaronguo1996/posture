/*************************************************************/
/*                           LOG.H                           */
/*                                                           */
/* Purpose: Definitions for the CLog class and related       */
/*          functions to generate an application log.        */
/*      Evan Pipho (evan@codershq.com)                       */
/*                                                           */
/*************************************************************/
#ifndef LOG_H
#define LOG_H

//Predefined color code strings
#define COLOR_RED		"#FF0000"
#define COLOR_ORANGE	"#FF9900"
#define COLOR_YELLOW	"#FFFF00"
#define COLOR_GREEN		"#00FF00"
#define COLOR_BLUE		"#0000FF"
#define COLOR_PURPLE	"#FF00FF"
#define COLOR_BLACK		"#000000"
#define COLOR_WHITE		"#FFFFFF"
#define COLOR_GRAY		"#CCCCCC"

//-------------------------------------------------------------
//                        INCLUDES                            -
//-------------------------------------------------------------
#include <cstdio>

//-------------------------------------------------------------
//                           CLog                             -
// author: Evan Pipho (evan@codershq.com)                     -
// date  : Jul 08, 2002                                       -
//-------------------------------------------------------------
class CLog
{
public:
	//Initialize the log
	bool Init(const char * szFile);
	//Write to log
	void Write(const char * szColor, const char * szFmt, ...);

	//Constructor
	CLog();
	CLog(const char * szFilename);

private:
	
	//Filename of logfile
	char * m_szFilename;
};

#endif //LOG_H