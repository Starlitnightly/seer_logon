#ifndef APIHOOK_H
#define APIHOOK_H


struct hook_t
{
    bool isHooked;
    void* FunctionAddress;
    void* Hook;
    char  Jmp[6];
    char  APIBytes[6];
    void* APIFunction;
};

class apihook
{
public:
    apihook();
    bool InitializeHook(hook_t* Hook, char* ModuleName, char* FunctionName, void* HookFunction);
    bool InitializeByAddress(hook_t* Hook, void* Address, void* HookFunction);
    bool InsertHook(hook_t* Hook);
    bool Unhook(hook_t* Hook);
    bool FreeHook(hook_t* Hook);

};

#endif // APIHOOK_H
