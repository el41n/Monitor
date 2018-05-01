#include "systemInfo.h"

#include <windows.h>
#include <qdebug.h>
#include <intrin.h>

QString systemInformation::getProcessorArchitecture()
{
    switch (sysInfo.wProcessorArchitecture) {
    case 0:
        return QString("INTEL x86 architecture");
        break;
    case 6:
        return QString("INTEL itanium-based architecture");
        break;
    case 9:
        return QString("AMD x64 architecture");
        break;
    default:
        return QString("Unknown architecture");
        break;
    }
}

int systemInformation::getPageGranularity()
{
    return sysInfo.dwPageSize;
}

int systemInformation::getMinimumAppAddress()
{
    return *((int *)sysInfo.lpMinimumApplicationAddress);
}

int systemInformation::getMaximumAppAdress()
{
    return *((int *)sysInfo.lpMaximumApplicationAddress);
}

QString systemInformation::getProcessorType()
{
    switch (sysInfo.dwProcessorType) {
    case 386:
        return QString("Intel 80x386");
        break;
    case 486:
        return QString("Intel 80x486");
        break;
     case 586:
         return QString("Intel Pentium");
         break;
    case 2200:
        return QString("Intel IA64");
        break;
    case 8664:
        return QString("AMD x86-64");
        break;
    default:
        return QString("Unknown");
        break;
    }
}

void systemInformation::getProcID()
{
}
typedef BOOL (WINAPI *LPFN_GLPI)(
    PSYSTEM_LOGICAL_PROCESSOR_INFORMATION,
    PDWORD);

DWORD CountSetBits(ULONG_PTR bitMask)
{
    DWORD LSHIFT = sizeof(ULONG_PTR)*8 - 1;
    DWORD bitSetCount = 0;
    ULONG_PTR bitTest = (ULONG_PTR)1 << LSHIFT;
    DWORD i;

    for (i = 0; i <= LSHIFT; ++i)
    {
        bitSetCount += ((bitMask & bitTest)?1:0);
        bitTest/=2;
    }

    return bitSetCount;
}

void systemInformation::getProcInfo()
{
    LPFN_GLPI glpi;
    BOOL done = FALSE;
    PSYSTEM_LOGICAL_PROCESSOR_INFORMATION buffer = NULL;
    PSYSTEM_LOGICAL_PROCESSOR_INFORMATION ptr = NULL;
    DWORD returnLength = 0;
    DWORD logicalProcessorCount = 0;
    DWORD numaNodeCount = 0;
    DWORD processorCoreCount = 0;
    DWORD processorL1CacheCount = 0;
    DWORD processorL1CacheSize = 0;
    DWORD processorL2CacheCount = 0;
    DWORD processorL2CacheSize = 0;
    DWORD processorL3CacheCount = 0;
    DWORD processorL3CacheSize = 0;
    DWORD processorPackageCount = 0;
    DWORD byteOffset = 0;
    PCACHE_DESCRIPTOR Cache;

    glpi = (LPFN_GLPI) GetProcAddress(
                            GetModuleHandle(TEXT("kernel32")),
                            "GetLogicalProcessorInformation");
    if (NULL == glpi)
    {
       // _tprintf(TEXT("\nGetLogicalProcessorInformation is not supported.\n"));
        //return (1);
    }

    while (!done)
    {
        DWORD rc = glpi(buffer, &returnLength);

        if (FALSE == rc)
        {
            if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
            {
                if (buffer)
                    free(buffer);

                buffer = (PSYSTEM_LOGICAL_PROCESSOR_INFORMATION)malloc(
                        returnLength);

                if (NULL == buffer)
                {
                    //_tprintf(TEXT("\nError: Allocation failure\n"));
                    //return (2);
                }
            }
            else
            {
               // _tprintf(TEXT("\nError %d\n"), GetLastError());
                //return (3);
            }
        }
        else
        {
            done = TRUE;
        }
    }

    ptr = buffer;

    while (byteOffset + sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION) <= returnLength)
    {
        switch (ptr->Relationship)
        {
        case RelationNumaNode:
            // Non-NUMA systems report a single record of this type.
            numaNodeCount++;
            break;

        case RelationProcessorCore:
            processorCoreCount++;

            // A hyperthreaded core supplies more than one logical processor.
            logicalProcessorCount += CountSetBits(ptr->ProcessorMask);
            break;

        case RelationCache:
            // Cache data is in ptr->Cache, one CACHE_DESCRIPTOR structure for each cache.
            Cache = &ptr->Cache;
            if (Cache->Level == 1)
            {
                processorL1CacheCount++;
                processorL1CacheSize = Cache->Size;
            }
            else if (Cache->Level == 2)
            {
                processorL2CacheCount++;
                processorL2CacheSize = Cache->Size;
            }
            else if (Cache->Level == 3)
            {
                processorL3CacheCount++;
                processorL3CacheSize = Cache->Size;
            }
            break;

        case RelationProcessorPackage:
            // Logical processors share a physical package.
            processorPackageCount++;
            break;

        default:
            //_tprintf(TEXT("\nError: Unsupported LOGICAL_PROCESSOR_RELATIONSHIP value.\n"));
            break;
        }
        byteOffset += sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION);
        ptr++;
    }

//    //_tprintf(TEXT("\nGetLogicalProcessorInformation results:\n"));
//    //_tprintf(TEXT("Number of NUMA nodes: %d\n"),
//             numaNodeCount);
//    //_tprintf(TEXT("Number of physical processor packages: %d\n"),
//             processorPackageCount);
//    //_tprintf(TEXT("Number of processor cores: %d\n"),
//             processorCoreCount);
//    //_tprintf(TEXT("Number of logical processors: %d\n"),
//             logicalProcessorCount);
//    //_tprintf(TEXT("Number of processor L1/L2/L3 caches: %d/%d/%d\n"),
//             processorL1CacheCount,
//             processorL2CacheCount,
//             processorL3CacheCount);

    free(buffer);
}

void systemInformation::proba()
{

}

systemInformation::systemInfo()
{
    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);
    this->sysInfo = sysInfo;
}
