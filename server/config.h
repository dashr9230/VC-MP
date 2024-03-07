
#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_CONFIG_STRSIZE 256
#define MAX_CONFIG_ENTRIES 1024

#define CCONF_ERR_SUCCESS	0
#define CCONF_ERR_FILE		1
#define CCONF_ERR_PARSE		2

//----------------------------------------------------

class CConfig
{
private:
	int iNumEntries; // Stores the number of entries.
	char *m_szDirectiveName[MAX_CONFIG_ENTRIES]; // Stores the directives
	char *m_szDirectiveData[MAX_CONFIG_ENTRIES]; // Stores the directive params

	void AddConfigEntry(char * szName, char * wsData);
	int  StringCompI(const char *s1, const char *s2);

public:
	CConfig() {
		iNumEntries=0;
		memset(m_szErrorString,0,MAX_CONFIG_STRSIZE);
	}

	// Contains verbose information about a config error.
	char m_szErrorString[MAX_CONFIG_STRSIZE];

	// Loads a file for the config class specified by szFileName.
	// Returns 0 to indicate success. Non 0 values indicate
	// an error as defined by the CCONF_ERR_ constants.
	// m_szErrorString will have information about the error.
	int ReadFile(char * szFileName);

	// Retreives a directive entry as string, case insensitve.
	// Returns NULL if entry is not found.
	char * GetConfigEntryAsString(char *szDirectiveName,int iArrayIndex = 0);

	// Retreives a directive entry as int.
	// If iArrayIndex is non 0, $szDirectiveName will be searched recursively.
	// Returns -1 if the config entry is not found.
	int GetConfigEntryAsInt(char *szDirectiveName, int iArrayIndex = 0);

	// Retreives BOOL entry. Returns 0 on "False" and 1 on "True". Returns
	// (-1) if the entry is not found.
	int GetConfigEntryAsBool(char *szDirectiveName, int iArrayIndex = 0);

	// Checks to see if the directive name is an array. Returns the number
	// of consecutive elements if there is an array by that name.
	int GetConfigArrayCount(char *szDirectiveName);
};

//----------------------------------------------------
