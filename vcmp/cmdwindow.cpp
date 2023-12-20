
#include "main.h"

extern CGame		 *pGame;

//----------------------------------------------------

CCmdWindow::CCmdWindow(IDirect3DDevice8 *pD3DDevice)
{
	m_bEnabled			= FALSE;
	m_iCmdCount			= 0;
	field_1701			= 16;
}

//----------------------------------------------------




//----------------------------------------------------

void CCmdWindow::Enable()
{
	m_bEnabled = TRUE;
	field_1701 = 16;
	pGame->ToggleKeyInputsDisabled(TRUE);
}

//----------------------------------------------------

void CCmdWindow::Disable()
{
	m_bEnabled = FALSE;
	field_1701 = 16;
	pGame->ToggleKeyInputsDisabled(FALSE);
}

//----------------------------------------------------




//----------------------------------------------------

void CCmdWindow::AddChar(char Char)
{
	if(FALSE == m_bEnabled) return;

	if(Char < ' ') return;

	int iCurBufferLen = strlen(m_szInputBuffer);
	if(iCurBufferLen < MAX_CMD_INPUT) {
		m_szInputBuffer[iCurBufferLen] = Char;
		m_szInputBuffer[iCurBufferLen+1] = '\0';
	}
}

//----------------------------------------------------

void CCmdWindow::BackSpace()
{
	if(FALSE == m_bEnabled) return;
	int iCurBufferLen = strlen(m_szInputBuffer);
	m_szInputBuffer[iCurBufferLen - 1] = '\0';
}

//----------------------------------------------------





//----------------------------------------------------

CMDPROC CCmdWindow::GetCmdHandler(PCHAR szCmdName)
{
	int x=0;
	while(x!=m_iCmdCount) {
		if(!stricmp(szCmdName,m_szCmdNames[x])) {
			return m_pCmds[x];
		}
		x++;
	}
	return NULL;
}

//----------------------------------------------------

void CCmdWindow::AddDefaultCmdProc(CMDPROC cmdDefault)
{
	m_pDefaultCmd = cmdDefault;
}

//----------------------------------------------------

void CCmdWindow::AddCmdProc(PCHAR szCmdName, CMDPROC cmdHandler)
{
	if(m_iCmdCount < MAX_CMDS && (strlen(szCmdName) < MAX_CMD_STRLEN)) {
		m_pCmds[m_iCmdCount] = cmdHandler;
		strcpy(m_szCmdNames[m_iCmdCount],szCmdName);
		m_iCmdCount++;
	}
}

//----------------------------------------------------
