
#include "main.h"

CChatWindow::CChatWindow(IDirect3DDevice8 *pD3DDevice)
{

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
	// TODO: CChatWindow::AddToChatWindowBuffer
}

//----------------------------------------------------
