#include <windows.h>

__declspec(dllexport) DWORD WINAPI go(LPVOID lpParameter)
{
  
  MessageBoxA(
    NULL,
    "Module execute",
    "C2 remote prompt",
    MB_OK | MB_ICONINFORMATION
  );

  return 0;
}