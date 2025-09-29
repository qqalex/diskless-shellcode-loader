#include "kb.h"
#include <minwindef.h>

tNtAllocateVirtualMemory   pNtAllocateVirtualMemory = NULL;
tNtProtectVirtualMemory    pNtProtectVirtualMemory = NULL;
tNtFreeVirtualMemory       pNtFreeVirtualMemory = NULL;
tRtlCreateUserThread       pRtlCreateUserThread = NULL;

BOOL NTPointers()
{
	HMODULE hNtdll = GetModuleHandleA("ntdll.dll");
  if (hNtdll == NULL)
    return FALSE;

	pNtAllocateVirtualMemory = 
		(tNtAllocateVirtualMemory)
		GetProcAddress(hNtdll, "NtAllocateVirtualMemory");
  pNtProtectVirtualMemory = 
		(tNtProtectVirtualMemory)
		GetProcAddress(hNtdll, "NtProtectVirtualMemory");
  pNtFreeVirtualMemory = 
		(tNtFreeVirtualMemory)
		GetProcAddress(hNtdll, "NtFreeVirtualMemory");
  pRtlCreateUserThread = 
		(tRtlCreateUserThread)
		GetProcAddress(hNtdll, "RtlCreateUserThread");

	if (pNtAllocateVirtualMemory == NULL ||
		pNtProtectVirtualMemory == NULL ||
		pNtFreeVirtualMemory == NULL ||
		pRtlCreateUserThread == NULL)
		return FALSE;

	return TRUE;
};