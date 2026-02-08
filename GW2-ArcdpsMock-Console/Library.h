#pragma once
#include <CrossplatformMocks/Module.h>
#include <ArcdpsExtension/arcdps_structs.h>

struct Library
{
    LibraryHandle Handle;
    GetInitAddrSignature GetInit;
    GetReleaseAddrSignature GetRelease;
    ModInitSignature Init;
    arcdps_exports* Exports;
};
