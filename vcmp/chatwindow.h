
#pragma once

enum eChatMessageType {
	CHAT_TYPE_DEBUG=3
};

class CChatWindow
{
private:

	void FilterInvalidChars(PCHAR szString);
	void AddToChatWindowBuffer(PCHAR szString, eChatMessageType eType);

public:

	void AddDebugMessage(CHAR *szFormat, ...);

	CChatWindow(IDirect3DDevice8 *pD3DDevice);

};
