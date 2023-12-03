
#include "main.h"

CPickUpPool::CPickUpPool()
{
	for (int i = 0; i != MAX_PICKUPS; i++)
	{
		field_0[i] = 0;
		field_540[i] = 0;
	}
}
