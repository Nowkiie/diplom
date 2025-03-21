
// (c) Copyright Dmitriy Shikhov 2017

#include "utils/disable_crash_dialog.hpp"
#include <windows.h>

void utils::disable_crash_dialog()
{
    SetErrorMode(GetErrorMode() | SEM_FAILCRITICALERRORS | SEM_NOGPFAULTERRORBOX
                 | SEM_NOOPENFILEERRORBOX);
}
