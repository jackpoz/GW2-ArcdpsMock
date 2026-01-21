#pragma once
#include "SharedTypes.h"
#include "arcdps_structs.h"

struct Library
{
    LibraryHandle Handle;
    GetInitAddrSignature GetInit;
    GetReleaseAddrSignature GetRelease;
    ModInitSignature Init;
    arcdps_exports* Exports;
};
