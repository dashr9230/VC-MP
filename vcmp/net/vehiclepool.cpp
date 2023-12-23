
#include "../main.h"

//----------------------------------------------------

CVehiclePool::CVehiclePool()
{
	BYTE byteVehicleID = 0;

	while(byteVehicleID != MAX_VEHICLES) {
		field_0[byteVehicleID] = 0;
		field_320[byteVehicleID] = 0;
		field_640[byteVehicleID] = 0;
		byteVehicleID++;
	}
}

//----------------------------------------------------
