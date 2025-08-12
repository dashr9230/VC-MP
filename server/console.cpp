
#include "main.h"

#ifdef LINUX

// strlwr is not included with the GNU C lib it seems.
char* strlwr(char* str)
{
	for (size_t i=0; i<strlen(str); i++)
	{
		if ((str[i] >= 'A') && (str[i] <= 'Z'))
		{
			str[i] -= 32;
		}
	}
	return str;
}

#endif	// #ifdef LINUX

char* strrtrim(char* str)
{
	for (int i=strlen(str)-1; i>=0; i--)
	{
		if ((str[i] == ' ') || (str[i] == '\t'))
		{
			str[i] = 0;
		} else {
			break;
		}
	}
	return str;
}

CConsole::CConsole()
{

}

CConsole::~CConsole()
{
	ConsoleVariables.clear();
}

ConsoleVariable_s* CConsole::FindVariable(char* pVarName)
{
	char VarName[255];
	strncpy(VarName, pVarName, 255);
	strlwr(VarName);

	StringConvarMap::iterator itor;
	itor = ConsoleVariables.find(VarName);
	if (itor != ConsoleVariables.end())
	{
		return itor->second;
	}
	return NULL;
}

void CConsole::PrintVariableList()
{
	char val[1034]; // Max str size of 1024 + the (string) tag.
	logprintf("Console Variables:");
	StringConvarMap::iterator itor;
	for (itor = ConsoleVariables.begin(); itor != ConsoleVariables.end(); itor++)
	{
		val[0] = 0;
		switch (itor->second->VarType)
		{
			case CON_VARTYPE_FLOAT:
				sprintf(val, "%f  (float)", *(float*)itor->second->VarPtr);
				break;
			case CON_VARTYPE_INT:
				sprintf(val, "%d  (int)", *(int*)itor->second->VarPtr);
				break;
			case CON_VARTYPE_BOOL:
				sprintf(val, "%d  (bool)", *(bool*)itor->second->VarPtr);
				break;
			case CON_VARTYPE_STRING:
				sprintf(val, "\"%s\"  (string)", (char*)itor->second->VarPtr);
				break;
		}
		const char* VarName = itor->first.c_str();
		logprintf("  %s\t%s= %s%s%s%s", VarName, (strlen(VarName)<6)?"\t":"", val,
			(itor->second->VarFlags & CON_VARFLAG_READONLY)?" (read-only)":"",
			(itor->second->VarFlags & CON_VARFLAG_DEBUG)?" (debug)":"",
			(itor->second->VarFlags & CON_VARFLAG_RULE)?" (rule)":"");
	}
	logprintf("");
}

void CConsole::AddVariable(char* pVarName, CON_VARTYPE VarType, DWORD VarFlags, void* VarPtr,
						   VARCHANGEFUNC VarChangeFunc)
{
	char VarName[255];
	strncpy(VarName, pVarName, 255);
	strlwr(VarName);

	if (FindVariable(VarName) != NULL)
	{
		logprintf("Unable to add console variable '%s'. Already exists.", VarName);
		return;
	}

	ConsoleVariable_s* ConVar = new ConsoleVariable_s;
	ConVar->VarType = VarType;
	ConVar->VarFlags = VarFlags;
	ConVar->VarPtr = VarPtr;
	ConVar->VarChangeFunc = VarChangeFunc;

	if (VarChangeFunc)
		VarChangeFunc();

	ConsoleVariables.insert(StringConvarMap::value_type(VarName, ConVar));
}

char* CConsole::AddStringVariable(char* pVarName, DWORD VarFlags, char* pInitStr,
								 VARCHANGEFUNC VarChangeFunc)
{
	char* str;
	if (!pInitStr)
	{
		// Empty string
		str = (char*)malloc(1);
		str[0] = 0;
	} else {
		str = (char*)malloc(strlen(pInitStr)+1);
		strcpy(str, pInitStr);
	}
	AddVariable(pVarName, CON_VARTYPE_STRING, VarFlags, (void*)str, VarChangeFunc);
	return str;
}

void CConsole::RemoveVariable(char* pVarName)
{
	ConsoleVariable_s* ConVar = FindVariable(pVarName);
	if (ConVar != NULL)
	{
		if (ConVar->VarType == CON_VARTYPE_STRING)
		{
			if (ConVar->VarPtr != NULL)
				free(ConVar->VarPtr);
		}
		char VarName[255];
		strncpy(VarName, pVarName, 255);
		strlwr(VarName);
		SAFE_DELETE(ConVar);
		ConsoleVariables.erase(VarName);
	}
}

void CConsole::ModifyVariableFlags(char* pVarName, DWORD VarFlags)
{
	ConsoleVariable_s* ConVar = FindVariable(pVarName);
	if (ConVar != NULL)
	{
		ConVar->VarFlags = VarFlags;
	}
}

char* CConsole::GetStringVariable(char* pVarName)
{
	ConsoleVariable_s* ConVar = FindVariable(pVarName);
	if (ConVar != NULL)
	{
		if (ConVar->VarType == CON_VARTYPE_STRING)
			return (char*)ConVar->VarPtr;
	}
	return NULL;
}

void CConsole::SetStringVariable(char* pVarName, char* pString)
{
	ConsoleVariable_s* ConVar = FindVariable(pVarName);
	if (ConVar != NULL)
	{
		if (ConVar->VarType == CON_VARTYPE_STRING)
		{
			if (ConVar->VarPtr != NULL)
				free(ConVar->VarPtr);

			char* str = (char*)malloc(strlen(pString)+1);
			strcpy(str, pString);
			ConVar->VarPtr = str;
		}
	}
}

float CConsole::GetFloatVariable(char* pVarName)
{
	ConsoleVariable_s* ConVar = FindVariable(pVarName);
	if (ConVar != NULL)
	{
		if (ConVar->VarType == CON_VARTYPE_FLOAT)
			return *(float*)ConVar->VarPtr;
	}
	return 0.0f;
}

void CConsole::SetFloatVariable(char* pVarName, float fFloat)
{
	ConsoleVariable_s* ConVar = FindVariable(pVarName);
	if (ConVar != NULL)
	{
		if (ConVar->VarType == CON_VARTYPE_FLOAT)
			*(float*)ConVar->VarPtr = fFloat;
	}
}

int CConsole::GetIntVariable(char* pVarName)
{
	ConsoleVariable_s* ConVar = FindVariable(pVarName);
	if (ConVar != NULL)
	{
		if (ConVar->VarType == CON_VARTYPE_INT)
			return *(int*)ConVar->VarPtr;
	}
	return 0;
}

void CConsole::SetIntVariable(char* pVarName, int iInt)
{
	ConsoleVariable_s* ConVar = FindVariable(pVarName);
	if (ConVar != NULL)
	{
		if (ConVar->VarType == CON_VARTYPE_INT)
			*(int*)ConVar->VarPtr = iInt;
	}
}

bool CConsole::GetBoolVariable(char* pVarName)
{
	ConsoleVariable_s* ConVar = FindVariable(pVarName);
	if (ConVar != NULL)
	{
		if (ConVar->VarType == CON_VARTYPE_BOOL)
			return *(bool*)ConVar->VarPtr;
	}
	return false;
}

void CConsole::SetBoolVariable(char* pVarName, bool bBool)
{
	ConsoleVariable_s* ConVar = FindVariable(pVarName);
	if (ConVar != NULL)
	{
		if (ConVar->VarType == CON_VARTYPE_BOOL)
			*(bool*)ConVar->VarPtr = bBool;
	}
}

void CConsole::Execute(char* pExecLine)
{
	if (!pExecLine) return;

	// Ya can't strtok on a read-only string!
	char cpy[255];
	strncpy(cpy, pExecLine, 255);
    char* cmd = strlwr(strtok(cpy, " "));

	// TODO: CConsole::Execute
}
