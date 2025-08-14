
#include "main.h"

extern bool	bQuitApp;

void con_exit()
{
	bQuitApp = true;
}

void con_echo()
{
	char* arg = strtok(NULL, "");
	if (arg)
	{
		logprintf("%s", arg);
	} else {
		logprintf("");
	}
}

void con_exec()
{
	char* arg = strtok(NULL, " ");
	if (arg)
	{
		char tmp[256];
		sprintf(tmp, "%s.cfg", arg);
		FILE* f = fopen(tmp, "r");
		if (!f)
		{
			logprintf("Unable to exec file '%s'.", tmp);
		} else {
			while (fgets(tmp, 1024, f))
			{
				if (tmp[strlen(tmp)-1] == '\n')
					tmp[strlen(tmp)-1] = 0;
				// If the line has a comment, finish it there.
				for (size_t i=0; i<strlen(tmp)-1; i++)
				{
					if ((tmp[i] == '/') && (tmp[i+1] == '/'))
					{
						tmp[i] = 0;
						break;
					}
				}
				if (strlen(tmp) > 2)
				{
					if ((tmp[0] != '/') && (tmp[1] != '/'))
						pConsole->Execute(tmp);
				}
			}
			fclose(f);
		}
	} else {
		logprintf("Usage:");
		logprintf("  exec <filename>");
	}
}

extern BOOL bGameModeFinished;
void con_gmx()
{
	bGameModeFinished = TRUE;
}

void con_changemode()
{
	char* arg = strtok(NULL, "");
	if (arg)
	{
		if(pNetGame->SetNextScriptFile(arg)) {
			bGameModeFinished = TRUE;
		}
		// do nothing if we can't set the requested script.
	}
}

void con_cmdlist();

void con_varlist()
{
	pConsole->PrintVariableList();
}

void con_say()
{
	char* arg = strtok(NULL, "");
	char Message[255];
	if (arg) {
		sprintf(Message, "* Admin: %s", arg);
		//pNetGame->SendClientMessageToAll(0x2587CEAA, Message);
	}
}

void con_reloadbans()
{
	pNetGame->LoadBanList();
}

#define CON_CMDFLAG_DEBUG		1
#define CON_CMDFLAG_HIDDEN		2

struct ConsoleCommand_s
{
	char CmdName[255];
	DWORD CmdFlags;
	void (*CmdFunc)();
} ConsoleCommands[] = {
	{"echo",		0,	con_echo},
	{"exec",		0,	con_exec},
	{"cmdlist",		0,	con_cmdlist},
	{"varlist",		0,	con_varlist},
	{"exit",		0,	con_exit},
	{"gmx",			0,	con_gmx},
	{"changemode",	0,	con_changemode},
	{"say",			0,	con_say},
	{"reloadbans",	0,	con_reloadbans},
};

void con_cmdlist()
{
	logprintf("Console Commands:");
	for (int i=0; i<ARRAY_SIZE(ConsoleCommands); i++)
	{
		logprintf("  %s%s", ConsoleCommands[i].CmdName, (ConsoleCommands[i].CmdFlags & CON_CMDFLAG_DEBUG)?" (DEBUG)":"");
	}
	logprintf("");
}

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

	if(pNetGame) {
		CGameMode *pGameMode = pNetGame->GetGameMode();
		CFilterScripts *pFilterScripts = pNetGame->GetFilterScripts();

		int ret = pFilterScripts->OnRconCommand(pExecLine);
		if(ret == -1)
			return;
		if(ret == 0) {
			if(pGameMode) {
				ret = pGameMode->OnRconCommand(pExecLine);
			} else {
				ret = 0;
			}
		}
		if(ret == -1 || ret == 1)
			return;
	}

	for (int i=0; i<ARRAY_SIZE(ConsoleCommands); i++)
	{
		if (stricmp(cmd, ConsoleCommands[i].CmdName) == 0)
		{
			if (ConsoleCommands[i].CmdFlags & CON_CMDFLAG_DEBUG)
			{
				#ifndef _DEBUG
					logprintf("Unable to execute command '%s'. Debug mode required.", ConsoleCommands[i].CmdName);
					return;
				#endif
			}
			ConsoleCommands[i].CmdFunc();
			return;
		}
	}

	ConsoleVariable_s* ConVar = FindVariable(cmd);
	if (ConVar != NULL)
	{
		bool readonly = (ConVar->VarFlags & CON_VARFLAG_READONLY) == CON_VARFLAG_READONLY;
		if (ConVar->VarFlags & CON_VARFLAG_DEBUG)
		{
			#ifndef _DEBUG
				logprintf("Unable to access variable '%s'. Debug mode required.", cmd);
				return;
			#endif
		}
		bool bChangedVar = false;
		char* arg = strtok(NULL, " ");
		switch (ConVar->VarType)
		{
			case CON_VARTYPE_FLOAT:
				if ((arg) && (!readonly))
				{
					*(float*)ConVar->VarPtr = (float)atof(arg);
					bChangedVar = true;
				} else {
					logprintf("%s = %f  (float%s)", cmd, *(float*)ConVar->VarPtr, readonly?", read-only":"");
				}
				break;
			case CON_VARTYPE_INT:
				if ((arg) && (!readonly))
				{
					*(int*)ConVar->VarPtr = atoi(arg);
					bChangedVar = true;
				} else {
					logprintf("%s = %d  (int%s)", cmd, *(int*)ConVar->VarPtr, readonly?", read-only":"");
				}
				break;
			case CON_VARTYPE_BOOL:
				if ((arg) && (!readonly))
				{
					*(bool*)ConVar->VarPtr = (atoi(arg) > 0);
					bChangedVar = true;
				} else {
					logprintf("%s = %d  (bool%s)", cmd, *(bool*)ConVar->VarPtr, readonly?", read-only":"");
				}
				break;
			case CON_VARTYPE_STRING:
				if ((arg) && (!readonly))
				{
					if (ConVar->VarPtr != NULL)
						free(ConVar->VarPtr);

					char* str;
					char* ext = strtok(NULL, "");
					if (ext)
					{
						str = (char*)malloc(strlen(arg)+strlen(ext)+2);
						strcpy(str, arg);
						strcat(str, " ");
						strrtrim(ext);
						strcat(str, ext);
					} else {
						str = (char*)malloc(strlen(arg)+1);
						strcpy(str, arg);
					}
					if (strlen(str) > 1023) str[1022] = 0;
					ConVar->VarPtr = str;
					bChangedVar = true;
				} else {
					logprintf("%s = \"%s\"  (string%s)", cmd, (char*)ConVar->VarPtr, readonly?", read-only":"");
				}
				break;
		}
		if (bChangedVar)
		{
			if (ConVar->VarChangeFunc)
			{
				ConVar->VarChangeFunc();
			}
		}
	} else {
		logprintf("Unknown command or variable:\n  %s", cmd);
	}
}
