#ifndef CRE_FILE_H
#define CRE_FILE_H

#include "xref.h"

namespace
{
    #pragma pack(push, 1)
    struct CreHeader
    {
        CharArray<4> signature; // 0x0 "CRE "
        CharArray<4> version;   // 0x4 "V1.0"
    };
    #pragma pack(pop)
}

#endif