#define SE_SHUTDOWN_NAME
#define SHTDN_REASON_MINOR_OTHER 0x00000000
#define SHTDN_REASON_MAJOR_OTHER 0x00000000
#define SHTDN_REASON_FLAG_PLANNED 0x80000000
#include <Windows.h>
HMODULE hNTDLL;
TOKEN_PRIVILEGES tkp;
HANDLE hToken;
typedef enum _SHUTDOWN_ACTION {
ShutdownNoReboot, ShutdownReboot, ShutdownPowerOff
} SHUTDOWN_ACTION, *PSHUTDOWN_ACTION;
typedef DWORD (WINAPI* lpNtSetSystemPowerState)(IN POWER_ACTION SystemAction,IN SYSTEM_POWER_STATE MinSystemState,IN ULONG Flags);
lpNtSetSystemPowerState NtSetSystemPowerState;
int main(){
	hNTDLL = LoadLibrary("NTDLL.DLL");
	NtSetSystemPowerState = (lpNtSetSystemPowerState)GetProcAddress(hNTDLL, "NtSetSystemPowerState");
	OpenProcessToken(GetCurrentProcess(),TOKEN_QUERY|TOKEN_ADJUST_PRIVILEGES, &hToken);
	LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid);
	tkp.PrivilegeCount = 1;
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, NULL, 0);
	CloseHandle(hToken); 
	NtSetSystemPowerState(PowerActionShutdownOff,PowerSystemShutdown,
		SHTDN_REASON_MAJOR_OTHER | SHTDN_REASON_MINOR_OTHER | SHTDN_REASON_FLAG_PLANNED);
	return 0;
}