#ifndef MAPFILE_H
#define MAPFILE_H

#include <cstdint>

namespace  mapfile
{
#pragma pack(push,1)
    //struct FileHeader
    //{
    //    char signature[8];
    //    int version;
    //    char fileType[8];
    //    unsigned __int64 indexLength;
    //};

    struct FileHeaderBase
    {
        char    signature[8];
        int32_t    version;
        char    fileType[8];
    };

    struct FileHeaderV1
    {
        uint64_t    indexLength;
    };

    struct FileHeaderV2
    {
        unsigned char    clusterSize;
        uint64_t    clusterLength;
        uint64_t    indexLength;
    };

    struct IndexCluster
    {
        int32_t        z;
        int32_t        x;
        int32_t        y;
        uint64_t    offset;
        uint32_t    size;
    };

    // size 4 + 4 + 4 + 4 + 8 = 24
    struct FileIndex
    {
        int32_t        z;
        int32_t        x;
        int32_t        y;
        uint32_t    fileSize;
        uint64_t    offset;
    };

#pragma pack(pop)
}

#endif // MAPFILE_H