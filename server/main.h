
#pragma once

#include <stdio.h>

#define MAX_PLAYERS			100
#define MAX_VEHICLES		200

#define MAP_NONE			0
#define MAP_VICE			1
#define MAP_LIBERTY			2

#include "../raknet/RakServer.h"
#include "../raknet/RakNetworkFactory.h"

#include "system.h"
#include "config.h"

#define DEFAULT_CONFIG_FILE "server.ini"
#define DEFAULT_MAX_PLAYERS 50
#define DEFAULT_LISTEN_PORT 8192

