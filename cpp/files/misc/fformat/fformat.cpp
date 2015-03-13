#include <stdio.h>
#include <string.h>
#include <tchar.h>
#include <windows.h>
#include <winbase.h>

// full-screen mode on WinNT/2000/XP is enabled through these undocumented APIs
typedef BOOL (WINAPI *GetConsoleDisplayModeT)(DWORD*);
typedef BOOL (WINAPI *SetConsoleDisplayModeT)(HANDLE, DWORD, DWORD*);

GetConsoleDisplayModeT GetConsoleDisplayMode;
SetConsoleDisplayModeT SetConsoleDisplayMode;


// flushes some text at the given rate
void Flush(LPCTSTR text, UINT delay)
{
   size_t c;

   for (c = 0; c < _tcslen(text); c++)
   {
      printf("%c", text[c]);
      ::Sleep(delay);
   }
}



// returns the window handle of the current console
HWND GetConsoleHwnd(void)
{
   HWND hWnd = NULL;
   char pszNewTitle[MAX_PATH];
   char pszOldTitle[MAX_PATH];

   // retrieve the console title
   ::GetConsoleTitle(pszOldTitle, MAX_PATH);
   
   // make the title unique
   wsprintf(pszNewTitle, "%d/%d", ::GetTickCount(), ::GetCurrentProcessId());
   ::SetConsoleTitle(pszNewTitle);
   
   // wait for title update
   ::Sleep(100);
   hWnd = ::FindWindow(NULL, pszNewTitle);

   // restore the orginal title
   ::SetConsoleTitle(pszOldTitle);

   return(hWnd);
}

int main(int argc, char* argv[])
{
   HWND hWnd;
   DWORD version, minor, major;
   DWORD sectorsPerCluster, bytesPerSector, freeClusters, totalClusters;
   DWORD serialNumber;
   double volumeSize;
   char buffer[MAX_PATH];
   int i;

   // enable full-screen mode
   hWnd = GetConsoleHwnd();
   
   if (hWnd == NULL)
      return -1;
   
   version = ::GetVersion();
   major = (DWORD)(LOBYTE(LOWORD(version)));
   minor = (DWORD)(HIBYTE(LOWORD(version)));
   
   if (version < 0x80000000)
   {
      // WinNT/2000/XP
      HINSTANCE hLib = ::LoadLibrary("KERNEL32.DLL");

      SetConsoleDisplayMode = (SetConsoleDisplayModeT)
                              ::GetProcAddress(hLib, "SetConsoleDisplayMode");

      GetConsoleDisplayMode = (GetConsoleDisplayModeT)
                              ::GetProcAddress(hLib, "GetConsoleDisplayMode");

      HANDLE hCon = ::CreateFile("CONOUT$",
                                 GENERIC_WRITE | GENERIC_READ,
                                 FILE_SHARE_READ | FILE_SHARE_WRITE,
                                 NULL,
                                 OPEN_EXISTING,
                                 0,
                                 0);
     
      DWORD oldMode;
      SetConsoleDisplayMode (hCon, 1, &oldMode);
   }
   else if (major < 4)
   {
      // Win32s
      return -1; 
   }
   else
   {
      // Win95/98/Me
      ::SendMessage(hWnd, WM_COMMAND, (WPARAM)57359, (LPARAM)0);
   }

   // retrieve the C: volume size
   ::GetDiskFreeSpace("C:", &sectorsPerCluster, &bytesPerSector,
                                   &freeClusters, &totalClusters);

    // from bytes to MBs
   volumeSize = (double)bytesPerSector * sectorsPerCluster * totalClusters;
   volumeSize = volumeSize / (1024 * 1024);

    // retrieve the C: volume serial number
    ::GetVolumeInformation("C:\\", NULL, 0, &serialNumber, NULL, NULL, NULL, 0);

   // start up the show!
   Flush("C:>\n", 0);
   ::Sleep(3000);
   Flush("C:>", 0);
   ::Sleep(1000);
   Flush("FORMAT C: /S\n", 50);
   ::Sleep(1000);
   Flush("\nATTENZIONE: TUTTI I DATI SUL DISCO RIGIDO C: ANDRANNO PERSI!\n", 0);
   Flush("Continuare con la formattazione (S/N)? ", 0);
   ::Sleep(1000);
   Flush("S\n\n", 0);
   ::Sleep(500);

   Flush("\nControllo del formato del disco.\n", 0);
   ::Sleep(200);
   Flush("Registrazione cluster danneggiati in corso", 0);
   ::Sleep(1000);
   Flush("..........\n", 300);
   Flush("Completata.\n", 0);

   sprintf(buffer, "\nVerifica di %.2f MB in corso\n", volumeSize);
   Flush(buffer, 0);

   Flush(" 0%% completato.", 0);

   for (i = 1; i < 101; i++)
   {
       Flush("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b", 0);
       sprintf(buffer, "%2d%% completato.", i);
       Flush(buffer, 0);
       ::Sleep(50);
   }

   Flush("\n", 100);
   Flush("\nEtichetta di volume (11 caratteri, invio per non darne)? ", 0);
   ::Sleep(1000);
   Flush("FAKEFORMAT\n", 50);

// .........
//

   sprintf(buffer, "\nNumero di serie: %u\n", serialNumber);
   Flush(buffer, 0);
   ::Sleep(2000);

   return 0;
}
