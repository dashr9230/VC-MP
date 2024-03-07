
#pragma once

//----------------------------------------------------

class CVehiclePool
{
private:

	int field_0[MAX_VEHICLES];
	int field_320[MAX_VEHICLES];

public:

	CVehiclePool();

	BOOL InitialiseFromConfig(CConfig *pConfig);

};

//----------------------------------------------------
