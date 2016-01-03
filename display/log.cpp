/*************************************************************/
/*                           LOG.CPP                         */
/*                                                           */
/* Purpose: Implementation for CLog, application log class   */
/*      Evan Pipho (evan@codershq.com)                       */
/*                                                           */
/*************************************************************/
//-------------------------------------------------------------
//                        INCLUDES                            -
//-------------------------------------------------------------
#include <windows.h>
#include <cstdarg>
#include <ctime>
#include "log.h"

//-------------------------------------------------------------
//- Init
//- Initializes the log and writes the header
//-------------------------------------------------------------
bool CLog::Init(const char * szFile)
{
	char caTime[32];
	char caDate[32];
	FILE * f = fopen(szFile, "wt");
	if(!f)
		return false;

	fprintf(f, "<HTML>\n<HEAD><TITLE>Application Log</TITLE></HEAD>\n<BODY BGCOLOR = \"#000000\">\n");
	_strtime(caTime);
	_strdate(caDate);
	fprintf(f, "<FONT COLOR = \"#FFFFFF\">Log Started at %s on %s</FONT><BR><BR>\n", caTime, caDate);
	fprintf(f, "</BODY></HTML>");
	fclose(f);
	m_szFilename = (char *)szFile;

	return true;
}

//-------------------------------------------------------------
//- Write
//- Writes tot he log, uses variable args
//-------------------------------------------------------------
void CLog::Write(const char * szColor, const char * szFmt, ...)
{
	char caString[1024];
	char caTime[32];

	va_list va;
	va_start(va, szFmt);
	vsprintf(caString, szFmt, va);
	va_end(va);

	_strtime(caTime);

	FILE * f = fopen(m_szFilename, "r+");
	if(!f)
		return;

	fseek(f, -14, SEEK_END);
	fprintf(f, "<FONT COLOR = \"%s\">%s&nbsp;&nbsp;&nbsp;&nbsp;%s</FONT><BR>\n", szColor, caTime, caString);
	fprintf(f, "</BODY></HTML>");
	fclose(f);
}

//-------------------------------------------------------------
//- Constructors
//- 1. Default Constructor
//- 2. char *, filename to write log to
//-------------------------------------------------------------
CLog::CLog()
{
	m_szFilename = 0;
}

CLog::CLog(const char * szFilename)
{
	Init(szFilename);
}
