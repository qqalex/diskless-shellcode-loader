#include "kb.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, 
  LPSTR lpCmdLine, int nCmdShow)
{
  dbgp("#   Beacon: Debug build 0.0.0");
  return KbMain();
}

int main()
{
  return WinMain(GetModuleHandle(NULL), 
  NULL, GetCommandLineA(), SW_SHOWDEFAULT);
}