
#pragma once

#define MAX_CMDS		128
#define MAX_CMD_STRLEN  32

typedef void (__cdecl *CMDPROC)(PCHAR);

//----------------------------------------------------

class CCmdWindow
{
private:
	char _gap0[1145];

	// Command procedure stuff.
	CMDPROC		m_pDefaultCmd;	 // used when no command specifier was
								 // used (ie. a normal chat message)
	CMDPROC		m_pCmds[MAX_CMDS];
	CHAR        m_szCmdNames[MAX_CMDS][MAX_CMD_STRLEN+1];
	int			m_iCmdCount;

	char _gap1701[4];

public:
	CMDPROC GetCmdHandler(PCHAR szCmdName);
	void AddDefaultCmdProc(CMDPROC cmdDefault);
	void AddCmdProc(PCHAR szCmdName, CMDPROC cmdHandler);

	CCmdWindow(IDirect3DDevice8 *pD3DDevice);
};

//----------------------------------------------------
// EOF
