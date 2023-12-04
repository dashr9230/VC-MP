
#include "main.h"

int AMXAPI aux_LoadProgram(AMX* amx, char* filename)
{
	FILE* fp;
	if ((fp = fopen(filename, "rb")) == NULL)
	{
		return AMX_ERR_NOTFOUND;
	}
	AMX_HEADER hdr;
	fread(&hdr, sizeof hdr, 1, fp);
	amx_Align16(&hdr.magic);
	amx_Align32((uint32_t *)&hdr.size);
	amx_Align32((uint32_t *)&hdr.stp);

	if (hdr.magic != AMX_MAGIC)
	{
		fclose(fp);
		return AMX_ERR_FORMAT;
	}

	void* memblock;
	if ((memblock = malloc(hdr.stp)) == NULL)
	{
		fclose(fp);
		return AMX_ERR_MEMORY;
	}

	rewind(fp);
	fread(memblock, 1, (size_t)hdr.size, fp);
	fclose(fp);

	//amx_SetDebugHook(amx, (AMX_DEBUG)amx_Debug);
	memset(amx, 0, sizeof(*amx));
	int result = amx_Init(amx, memblock);
	if (result != AMX_ERR_NONE)
	{
		free(memblock);
		amx->base = NULL;
	}
	return result;
}


char * AMXAPI aux_StrError(int errnum)
{
	static char *messages[] = {
		/* AMX_ERR_NONE      */ "(none)",
		/* AMX_ERR_EXIT      */ "Forced exit",
		/* AMX_ERR_ASSERT    */ "Assertion failed",
		/* AMX_ERR_STACKERR  */ "Stack/heap collision (insufficient stack size)",
		/* AMX_ERR_BOUNDS    */ "Array index out of bounds",
		/* AMX_ERR_MEMACCESS */ "Invalid memory access",
		/* AMX_ERR_INVINSTR  */ "Invalid instruction",
		/* AMX_ERR_STACKLOW  */ "Stack underflow",
		/* AMX_ERR_HEAPLOW   */ "Heap underflow",
		/* AMX_ERR_CALLBACK  */ "No (valid) native function callback",
		/* AMX_ERR_NATIVE    */ "Native function failed",
		/* AMX_ERR_DIVIDE    */ "Divide by zero",
		/* AMX_ERR_SLEEP     */ "(sleep mode)",
		/* 13 */                "(reserved)",
		/* 14 */                "(reserved)",
		/* 15 */                "(reserved)",
		/* AMX_ERR_MEMORY    */ "Out of memory",
		/* AMX_ERR_FORMAT    */ "Invalid/unsupported P-code file format",
		/* AMX_ERR_VERSION   */ "File is for a newer version of the AMX",
		/* AMX_ERR_NOTFOUND  */ "File or function is not found",
		/* AMX_ERR_INDEX     */ "Invalid index parameter (bad entry point)",
		/* AMX_ERR_DEBUG     */ "Debugger cannot run",
		/* AMX_ERR_INIT      */ "AMX not initialized (or doubly initialized)",
		/* AMX_ERR_USERDATA  */ "Unable to set user data field (table full)",
		/* AMX_ERR_INIT_JIT  */ "Cannot initialize the JIT",
		/* AMX_ERR_PARAMS    */ "Parameter error",
		};
	if (errnum < 0 || errnum >= sizeof messages / sizeof messages[0])
		return "(unknown)";
	return messages[errnum];
}

//----------------------------------------------------------------------------------

void AMXPrintError(CGameMode* pGameMode, AMX *amx, int error)
{
	if (error != AMX_ERR_NONE)
	{
		logprintf("Script[%s]: Run time error %d: \"%s\"",// on line %ld\n",
			pGameMode->GetFileName(), error, aux_StrError(error));//, (long)amx->curline);
	}
}

//----------------------------------------------------------------------------------
