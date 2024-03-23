
#include "main.h"

extern CGame *pGame;

D3DDISPLAYMODE d3ddm;

//----------------------------------------------------

CChatWindow::CChatWindow(IDirect3DDevice8 *pD3DDevice)
{
	int x=0;

	field_0				= 2;
	m_fDrawStartX		= 25.0f;
	m_fDrawStartY		= 30.0f;
	m_fDrawPadding		= 3.0f;
	m_pD3DFont			= NULL;

	if(pD3DDevice) {
		m_pD3DFont = new CD3DFont(CHAT_FONT,CHAT_FONT_SIZE+1,0);
		m_pD3DFont->InitDeviceObjects(pD3DDevice);
		m_pD3DFont->RestoreDeviceObjects();

		pD3DDevice->GetDisplayMode(&d3ddm);
		pGame->field_0 = d3ddm.Width;
		pGame->field_4 = d3ddm.Height;
	}

	m_pD3DFont->GetTextExtent("W",&m_sizeText);

	// Init the chat window lines to 0
	while(x!=MAX_DISP_MESSAGES) {
		memset(m_szChatWindowBuffer[x],0,MAX_MESSAGE_LENGTH);
		x++;
	}

	m_dwChatTeamColor = D3DCOLOR_ARGB(255,222,55,55);
	field_A81 = D3DCOLOR_ARGB(255,222,55,55);

	m_pD3DDevice = pD3DDevice;

	m_dwChatTextColor = D3DCOLOR_ARGB(255,255,255,255);
	m_dwChatInfoColor = D3DCOLOR_ARGB(255,55,125,255);
	m_dwChatDebugColor = D3DCOLOR_ARGB(255,4,163,107);
	m_dwChatBackgroundColor = D3DCOLOR_ARGB(255,0,0,0);
	m_dwChatMeColor = D3DCOLOR_ARGB(255,204,163,107);
}

//----------------------------------------------------

void CChatWindow::Draw()
{
	float fDrawX=m_fDrawStartX;
	float fDrawY=m_fDrawStartY;
	DWORD dwColorChat=0;

}

//----------------------------------------------------

void CChatWindow::AddMeMessage(CHAR * szFormat, ...)
{
	char tmp_buf[512];
	memset(tmp_buf,0,512);

	va_list args;
	va_start(args, szFormat);
	vsprintf(tmp_buf, szFormat, args);
	va_end(args);

	FilterInvalidChars(tmp_buf);
	AddToChatWindowBuffer(tmp_buf,CHAT_TYPE_ME);	
}


//----------------------------------------------------

void CChatWindow::AddChatMessage(CHAR *szNick, DWORD dwNickColor, CHAR *szMessage)
{
	char tmp_buf[512] = {0};
	char * t = tmp_buf;

	memset(tmp_buf,0,512);

	// NICKNAME
	*t = '\01'; t++; // color start
	memcpy(t,&dwNickColor,sizeof(DWORD)); t+=4; // nick color
	memcpy(t,szNick,strlen(szNick)); t+=strlen(szNick); // nick string
	*t = '\01'; t++; // color start
	memcpy(t,&m_dwChatTextColor,sizeof(DWORD)); t+=4; // chat color
	*t = ':'; t++;
	*t = ' '; t++;

	// MESSAGE
	FilterInvalidChars(szMessage);

	strcpy(t,szMessage);

	AddToChatWindowBuffer(tmp_buf,CHAT_TYPE_CHAT);
}

//----------------------------------------------------

void CChatWindow::AddTeamMessage(CHAR *szName, DWORD dwColor, CHAR *szMessage)
{
	char tmp_buf[512] = {0};
	char * t = tmp_buf;

	memset(tmp_buf,0,512);

	// NICKNAME
	*t = '\01'; t++; // color start
	memcpy(t,&dwColor,sizeof(DWORD)); t+=4;
	memcpy(t,szName,strlen(szName)); t+=strlen(szName);
	*t = '\01'; t++; // color start
	memcpy(t,&m_dwChatTeamColor,sizeof(DWORD)); t+=4; // chat color
	*t = ':'; t++;
	*t = ' '; t++;

	// MESSAGE
	FilterInvalidChars(szMessage);

	strcpy(t,szMessage);

	AddToChatWindowBuffer(tmp_buf,CHAT_TYPE_CHAT);
}

//----------------------------------------------------

void CChatWindow::AddInfoMessage(CHAR * szFormat, ...)
{
	char tmp_buf[512];
	memset(tmp_buf,0,512);

	va_list args;
	va_start(args, szFormat);
	vsprintf(tmp_buf, szFormat, args);
	va_end(args);

	FilterInvalidChars(tmp_buf);
	AddToChatWindowBuffer(tmp_buf,CHAT_TYPE_INFO);
}

//----------------------------------------------------

void CChatWindow::AddDebugMessage(CHAR * szFormat, ...)
{
	char tmp_buf[512];
	memset(tmp_buf,0,512);

	va_list args;
	va_start(args, szFormat);
	vsprintf(tmp_buf, szFormat, args);
	va_end(args);

	FilterInvalidChars(tmp_buf);
	AddToChatWindowBuffer(tmp_buf,CHAT_TYPE_DEBUG);
}

//----------------------------------------------------

void CChatWindow::FilterInvalidChars(PCHAR szString)
{
	while(*szString) {
		if(*szString < ' ' || *szString > 'z') {
			*szString = ' ';
		}
		szString++;
	}
}

//----------------------------------------------------

void CChatWindow::AddToChatWindowBuffer(PCHAR szString, eChatMessageType eType)
{
	int iBestLineLength;

	PushBack();

	if(strlen(szString) > MAX_LINE_LENGTH)
	{
		iBestLineLength = MAX_LINE_LENGTH;
		// see if we can locate a space.
		while(szString[iBestLineLength] != ' ' && iBestLineLength)
			iBestLineLength--;

		if((MAX_LINE_LENGTH - iBestLineLength) > 8) {
			// we should just take the whole line
			strncpy(m_szChatWindowBuffer[MAX_DISP_MESSAGES-1],szString,MAX_LINE_LENGTH);
			m_szChatWindowBuffer[MAX_DISP_MESSAGES-1][MAX_LINE_LENGTH] = '\0';
			m_eChatType[MAX_DISP_MESSAGES-1] = eType;
			PushBack();
			strcpy(m_szChatWindowBuffer[MAX_DISP_MESSAGES-1],szString+MAX_LINE_LENGTH);
			m_eChatType[MAX_DISP_MESSAGES-1] = eType;
		}
		else {
			// grab upto the found space.
			strncpy(m_szChatWindowBuffer[MAX_DISP_MESSAGES-1],szString,iBestLineLength);
			m_szChatWindowBuffer[MAX_DISP_MESSAGES-1][iBestLineLength] = '\0';
			m_eChatType[MAX_DISP_MESSAGES-1] = eType;
			PushBack();
			strcpy(m_szChatWindowBuffer[MAX_DISP_MESSAGES-1],szString+(iBestLineLength+1));
			m_eChatType[MAX_DISP_MESSAGES-1] = eType;
		}
	}
	else {
		strcpy(m_szChatWindowBuffer[MAX_DISP_MESSAGES-1],szString);
		m_eChatType[MAX_DISP_MESSAGES-1] = eType;
	}
}

//----------------------------------------------------

void CChatWindow::PushBack()
{
	int x=0;
	while(x!=(MAX_DISP_MESSAGES - 1)) {
		strcpy(m_szChatWindowBuffer[x],m_szChatWindowBuffer[x + 1]);
		m_eChatType[x] = m_eChatType[x + 1];
		x++;
	}
}

//----------------------------------------------------

void CChatWindow::DeleteDeviceObjects()
{
	SAFE_DELETE(m_pD3DFont);
}

//----------------------------------------------------
// EOF
