
//#pragma twice <- that's a joke btw.

#pragma once

#define MAX_CMD_INPUT   64
#define MAX_CMDS		128
#define MAX_CMD_STRLEN  32

typedef void (__cdecl *CMDPROC)(PCHAR);

//----------------------------------------------------

class CCmdWindow
{
private:

	CHAR		m_szInputBuffer[MAX_CMD_INPUT+1];

	BOOL		m_bEnabled;

	int field_455;
	int field_459;
	int field_45D;
	DWORD		m_dwDrawColor;
	DWORD		m_dwBackgroundColor;
	int field_469;
	IDirect3DDevice8 *m_pD3DDevice;
	int field_471;
	int field_475;

	// Command procedure stuff.
	CMDPROC		m_pDefaultCmd;	 // used when no command specifier was
								 // used (ie. a normal chat message)
	CMDPROC		m_pCmds[MAX_CMDS];
	CHAR        m_szCmdNames[MAX_CMDS][MAX_CMD_STRLEN+1];
	int			m_iCmdCount;

	int			field_1701;

public:

	void Enable();
	void Disable();

	BOOL isEnabled() { return m_bEnabled; };

	void AddChar(char Char);
	void BackSpace();

	CMDPROC GetCmdHandler(PCHAR szCmdName);
	void AddDefaultCmdProc(CMDPROC cmdDefault);
	void AddCmdProc(PCHAR szCmdName, CMDPROC cmdHandler);

	CCmdWindow(IDirect3DDevice8 *pD3DDevice);
};

//----------------------------------------------------
// EOF