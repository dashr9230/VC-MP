
#pragma once

#include <windows.h>

//-----------------------------------------------------------

#define MAX_PLAYERS		50
#define MAX_VEHICLES	200

//-----------------------------------------------------------

#define MAP_VICE			0
#define MAP_LIBERTY			1

#pragma pack(1)
typedef struct _PED_TYPE {
	char _gap0;
} PED_TYPE;

#pragma pack(1)
typedef struct _VEHICLE_TYPE {
	char _gap0;
} VEHICLE_TYPE;

#define WEAPON_MODEL_CELLPHONE			258
#define WEAPON_MODEL_BRASSKNUCKLE		259
#define WEAPON_MODEL_SCREWDRIVER		260
#define WEAPON_MODEL_GOLFCLUB			261
#define WEAPON_MODEL_NITESTICK			262
#define WEAPON_MODEL_KNIFECUR			263
#define WEAPON_MODEL_BASEBALL_BAT		264
#define WEAPON_MODEL_HAMMER				265
#define WEAPON_MODEL_CLEAVER			266
#define WEAPON_MODEL_MACHETE			267
#define WEAPON_MODEL_KATANA				268
#define WEAPON_MODEL_CHAINSAW			269
#define WEAPON_MODEL_GRENADE			270
#define WEAPON_MODEL_TEARGAS			271
#define WEAPON_MODEL_MOLOTOV			272
#define WEAPON_MODEL_MISSILE			273
#define WEAPON_MODEL_COLT45				274
#define WEAPON_MODEL_PYTHON				275
#define WEAPON_MODEL_RUGER				276
#define WEAPON_MODEL_CHROMEGUN			277
#define WEAPON_MODEL_SHOTGSPA			278
#define WEAPON_MODEL_BUDDYSHOT			279
#define WEAPON_MODEL_M4					280
#define WEAPON_MODEL_TEC9				281
#define WEAPON_MODEL_UZI				282
#define WEAPON_MODEL_INGRAMSL			283
#define WEAPON_MODEL_MP5LNG				284
#define WEAPON_MODEL_SNIPER				285
#define WEAPON_MODEL_LASER				286
#define WEAPON_MODEL_ROCKETLA			287
#define WEAPON_MODEL_FLAME				288
#define WEAPON_MODEL_M60				289
#define WEAPON_MODEL_MINIGUN			290
#define WEAPON_MODEL_BOMB				291
#define WEAPON_MODEL_CAMERA				292
#define WEAPON_MODEL_FINGERS			293
#define WEAPON_MODEL_MINIGUN2			294

#define WEAPON_UNARMED					0
#define WEAPON_BRASSKNUCKLE				1
#define WEAPON_SCREWDRIVER				2
#define WEAPON_GOLFCLUB					3
#define WEAPON_NITESTICK				4
#define WEAPON_KNIFECUR					5
#define WEAPON_BASEBALL_BAT				6
#define WEAPON_HAMMER					7
#define WEAPON_CLEAVER					8
#define WEAPON_MACHETE					9
#define WEAPON_KATANA					10
#define WEAPON_CHAINSAW					11
#define WEAPON_GRENADE					12
#define WEAPON_TEARGAS					14
#define WEAPON_MOLOTOV					15
#define WEAPON_MISSILE					16
#define WEAPON_COLT45					17
#define WEAPON_PYTHON					18
#define WEAPON_CHROMEGUN				19
#define WEAPON_SHOTGSPA					20
#define WEAPON_BUDDYSHOT				21
#define WEAPON_TEC9						22
#define WEAPON_UZI						23
#define WEAPON_INGRAMSL					24
#define WEAPON_MP5LNG					25
#define WEAPON_M4						26
#define WEAPON_RUGER					27
#define WEAPON_SNIPER					28
#define WEAPON_LASER					29
#define WEAPON_ROCKETLA					30
#define WEAPON_FLAME					31
#define WEAPON_M60						32
#define WEAPON_MINIGUN					33
#define WEAPON_BOMB						34
#define WEAPON_HELICANNON				35
#define WEAPON_CAMERA					36
#define WEAPON_COLLISION				39
#define WEAPON_FALL						41
#define WEAPON_DRIVEBY					42
#define WEAPON_DROWN					43
#define WEAPON_WATER					50
#define WEAPON_EXPLOSION				51
