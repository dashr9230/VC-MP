
#ifndef VCMPSRV_CONSOLE_H
#define VCMPSRV_CONSOLE_H

enum CON_VARTYPE {CON_VARTYPE_FLOAT, CON_VARTYPE_INT, CON_VARTYPE_BOOL, CON_VARTYPE_STRING};

#define CON_VARFLAG_READONLY	2
#define CON_VARFLAG_RULE		4	// Gets sent with a RULES query responce

typedef void (*VARCHANGEFUNC)();

struct ConsoleVariable_s
{
	CON_VARTYPE VarType;
	DWORD VarFlags;
	void* VarPtr;
	VARCHANGEFUNC VarChangeFunc;
};

typedef std::map<std::string, ConsoleVariable_s*> StringConvarMap;

class CConsole
{
public:
	StringConvarMap ConsoleVariables;

	CConsole();
	~CConsole();

	ConsoleVariable_s* FindVariable(char* pVarName);

	void AddVariable(char* pVarName, CON_VARTYPE VarType, DWORD VarFlags, void* VarPtr,
		VARCHANGEFUNC VarChangeFunc = NULL);
	char* AddStringVariable(char* pVarName, DWORD VarFlags, char* pInitStr,
		VARCHANGEFUNC VarChangeFunc = NULL);

	void ModifyVariableFlags(char* pVarName, DWORD VarFlags);

	char* GetStringVariable(char* pVarName);
	void SetStringVariable(char* pVarName, char* pString);

	int GetIntVariable(char* pVarName);
	void SetIntVariable(char* pVarName, int iInt);

	void Execute(char* pExecLine);
};

#endif
