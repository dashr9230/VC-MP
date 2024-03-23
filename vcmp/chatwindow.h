
#pragma once

#define CHAT_FONT					"arial bold"
#define CHAT_FONT_SIZE				9

#define MAX_MESSAGE_LENGTH			128
#define MAX_LINE_LENGTH				MAX_MESSAGE_LENGTH / 2
#define MAX_DISP_MESSAGES			20

enum eChatMessageType {
	CHAT_TYPE_NONE=0,
	CHAT_TYPE_CHAT,
	CHAT_TYPE_INFO,
	CHAT_TYPE_DEBUG,
	CHAT_TYPE_ME
};

//----------------------------------------------------

class CChatWindow
{
private:
	BYTE				field_0;
	CHAR				m_szChatWindowBuffer[MAX_DISP_MESSAGES][MAX_MESSAGE_LENGTH];
	eChatMessageType	m_eChatType[MAX_DISP_MESSAGES];

	DWORD				m_dwChatTextColor;
	DWORD				m_dwChatInfoColor;
	DWORD				m_dwChatDebugColor;
	DWORD				m_dwChatBackgroundColor;
	DWORD				m_dwChatTeamColor;
	DWORD				m_dwChatMeColor;

	float				m_fDrawStartX;
	float				m_fDrawStartY;
	float				m_fDrawPadding;
	SIZE				m_sizeText;

	char				_gapA7D[4];
	DWORD				field_A81;

	void PushBack();
	void FilterInvalidChars(PCHAR szString);
	void AddToChatWindowBuffer(PCHAR szString, eChatMessageType eType);

public:
	void Draw();
	void AddMeMessage(CHAR *szFormat, ...);
	void AddChatMessage(CHAR *szNick, DWORD dwNickColor, CHAR *szMessage);
	void AddTeamMessage(CHAR *szName, DWORD dwColor, CHAR *szMessage);
	void AddInfoMessage(CHAR *szFormat, ...);
	void AddDebugMessage(CHAR *szFormat, ...);

	void DeleteDeviceObjects();

	CChatWindow(IDirect3DDevice8 *pD3DDevice);

	CD3DFont			*m_pD3DFont;
	IDirect3DDevice8	*m_pD3DDevice;
};

//----------------------------------------------------
// EOF
