
#pragma once

struct SCRIPT_COMMAND		//	Params
{							//		i = integer
	WORD OpCode;			//		f = float
	char Params[13];		//		v = variable
};							//		s = string

int ScriptCommand(const SCRIPT_COMMAND* ScriptCommand, ...);	// The main scripting function. See notes.

const SCRIPT_COMMAND set_player_drive_by_mode = { 0x0501, "ii" };
