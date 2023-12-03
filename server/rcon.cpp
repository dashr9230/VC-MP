
#include "main.h"

extern char *szAdminPass;

CRcon::CRcon(WORD iPort, char* szPass, WORD iMaxAdmins)
{
	m_pRak = RakNetworkFactory::GetRakServerInterface();
	m_pRak->SetPassword(szPass);
	szAdminPass = szPass;

	for(int i=0; i<8; i++) {
		field_4[i] = 0;
	}

	if (!m_pRak->Start(iMaxAdmins, 0, 5, iPort))
	{
		logprintf("RCON: Unable to start Remote Console server.");
	} else {
		logprintf("RCON: Remote Console server started.");
	}
}

CRcon::~CRcon()
{
	if (m_pRak)
		RakNetworkFactory::DestroyRakServerInterface(m_pRak);
}

void CRcon::Process(void)
{
	// TODO: CRcon::Process
}
