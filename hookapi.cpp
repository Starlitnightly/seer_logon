#include "hookapi.h"
#include <windows.h>


HookApi::HookApi()
{
    
}
//安装hook
bool HookApi::InHook( PSTR szModuleName, PSTR szFunName, FARPROC pFun,SIZE_T psize)
{
    pOldFunEntry    = (LPVOID)GetProcAddress (GetModuleHandleA (szModuleName), szFunName ) ;
    HMODULE    hMod = ::GetModuleHandleA ( szModuleName ) ;
    if ( hMod != NULL )
    {
        pNewFunEntry    = (LPVOID)pFun ;
        pOldFunEntry    = (LPVOID)GetProcAddress ( hMod, szFunName ) ;
        bNewByte[0]        = 0xE9 ;
        *((PDWORD)(&(bNewByte[1])))    = (DWORD)pNewFunEntry - (DWORD)pOldFunEntry - 5 ;//jmp

        DWORD   dwProtect, dwWriteByte, dwReadByte ;
        VirtualProtect ( (LPVOID)pOldFunEntry, psize, PAGE_READWRITE, &dwProtect );
        ReadProcessMemory    ( GetCurrentProcess(), (LPVOID)pOldFunEntry, bOldByte, psize, &dwReadByte ) ;
        VirtualProtect ( (LPVOID)pOldFunEntry, psize, dwProtect, NULL ) ;
        return true; 
    }else
        return false;

 }

void HookApi::thook()
{
    /*
    pOldFunEntry    = (LPVOID)GetProcAddress (GetModuleHandleA (szModuleName), szFunName ) ;
    PDWORD OldProtect;
    bNewByte[0]        = 0xE9 ;
    *((PDWORD)(&(bNewByte[1])))    = (DWORD)pNewFunEntry - (DWORD)pOldFunEntry - 5 ;
    DWORD   dwProtect, dwWriteByte, dwReadByte ;
    VirtualProtect(pOldFunEntry,5,64,OldProtect);
    ReadProcessMemory(GetCurrentProcess(), (LPVOID)pOldFunEntry, bOldByte, 5, &dwReadByte ) ;
    VirtualProtect ( (LPVOID)pOldFunEntry, a, dwProtect, NULL ) ;
*/
}

//开始hook

// 实现HOOK API
void HookApi::Hook (SIZE_T psize )
{  
    //RtlMoveMemory(pOldFunEntry,bNewByte,psize);

    DWORD   dwProtect, dwWriteByte;
    //VirtualProtect((LPVOID)pOldFunEntry, psize, PAGE_READWRITE, &dwProtect);
    WriteProcessMemory( GetCurrentProcess(), (LPVOID)pOldFunEntry, bNewByte, psize, &dwWriteByte);
    //VirtualProtect((LPVOID)pOldFunEntry, psize, dwProtect, NULL);
}

//dll hook
void HookApi::DllHook ( PSTR szModuleName, PSTR szFunName, FARPROC pFun ,int a)
{
    HMODULE    hMod = ::GetModuleHandleA ( szModuleName ) ;
    if ( hMod != NULL )
    {
        pNewFunEntry    = (LPVOID)pFun ;
        pOldFunEntry    = (LPVOID)GetProcAddress ( hMod, szFunName ) ;
        bNewByte[0]        = 0xE9 ;
        *((PDWORD)(&(bNewByte[1])))    = (DWORD)pNewFunEntry - (DWORD)pOldFunEntry - 5 ;

        DWORD   dwProtect, dwWriteByte, dwReadByte ;
        VirtualProtect ( (LPVOID)pOldFunEntry, a, PAGE_READWRITE, &dwProtect );
        ReadProcessMemory    ( GetCurrentProcess(), (LPVOID)pOldFunEntry, bOldByte, a, &dwReadByte ) ;

        WriteProcessMemory    ( GetCurrentProcess(), (LPVOID)pOldFunEntry, bNewByte, a, &dwWriteByte ) ;
        VirtualProtect ( (LPVOID)pOldFunEntry, a, dwProtect, NULL ) ;
    }
}
// 重新HOOK
void HookApi::ReHook ()
{
    DWORD    dwProtect, dwWriteByte ;
    VirtualProtect ( pOldFunEntry, 5, PAGE_READWRITE, &dwProtect );
    WriteProcessMemory ( GetCurrentProcess(), pOldFunEntry, bNewByte, 5, &dwWriteByte ) ;
    VirtualProtect ( pOldFunEntry, 5, dwProtect, NULL ) ;
}
// 撤消HOOK
void HookApi::UnHook ()
{
    DWORD    dwProtect, dwWriteByte ;
    VirtualProtect ( pOldFunEntry, 5, PAGE_READWRITE, &dwProtect );
    WriteProcessMemory ( GetCurrentProcess(), pOldFunEntry, bOldByte, 5, &dwWriteByte ) ;
    VirtualProtect ( pOldFunEntry, 5, dwProtect, NULL ) ;
}
