#ifndef HOOKAPI_H
#define HOOKAPI_H
#include <windows.h>


class HookApi
{
public:
    LPVOID    pOldFunEntry, pNewFunEntry ;    // 初始函数地址、HOOK后的函数地址
    BYTE    bOldByte[5], bNewByte[5],*NewData,*OldData ;        // 原始字节、目标字节
   
    
public:
    HookApi();

    //实现apihook
    
    void Hook (SIZE_T psize );
    void DllHook( PSTR szModuleName, PSTR szFunName, FARPROC pFun ,int a);
    void ReHook ();
    void UnHook ();
    void thook();

    bool InHook( PSTR szModuleName, PSTR szFunName, FARPROC pFun,SIZE_T psize );

};

#endif // HOOKAPI_H
