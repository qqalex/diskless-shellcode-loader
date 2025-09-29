#include "kb.h"

HINTERNET PollServer(HINTERNET hSession)
{
  const LPCWSTR HOST = L"localhost";
  const LPCWSTR PATH = L"/module";
  const INTERNET_PORT PORT = 8080;

  HINTERNET hConnect = WinHttpConnect(hSession, HOST, PORT, 0);
  if (!hConnect) return NULL;
  
  HINTERNET hRequest = WinHttpOpenRequest(hConnect, L"GET", PATH, NULL, 
    WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, 0);
  if (!hRequest) {
    WinHttpCloseHandle(hConnect);
    return NULL;
  }

  if (!WinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, 
    WINHTTP_NO_REQUEST_DATA, 0, 0, 0))
  {
    WinHttpCloseHandle(hConnect);
    WinHttpCloseHandle(hRequest);
    return NULL;
  }

  if (!WinHttpReceiveResponse(hRequest, NULL)) {
    WinHttpCloseHandle(hConnect);
    WinHttpCloseHandle(hRequest);
    return NULL;
  }

  if (hConnect) WinHttpCloseHandle(hConnect);

  return hRequest;
}