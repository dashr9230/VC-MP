
#include "main.h"

CVehiclePool::CVehiclePool()
{
	for(BYTE byteVehicleID = 0; byteVehicleID != MAX_VEHICLES; byteVehicleID++) {
		field_0[byteVehicleID] = 0;
		field_320[byteVehicleID] = 0;
	}
}
