#ifndef EESAVEEDITOR_IO_H
#define EESAVEEDITOR_IO_H

#include <fstream>
#include <vector>

#include "aliases.h"

class StructWriter
{
public:
    explicit StructWriter(std::ifstream& file_handle) : file_handle(file_handle) {}

    template <typename Struct>
    void into(Struct& st, const u32 offset = 0) const
    {
        if (offset > 0) [[likely]]
            file_handle.seekg( offset, std::ios::beg );

        file_handle.read( reinterpret_cast<char*>(&st), sizeof( Struct ) );
    }

    template <typename Struct>
    void into(std::vector<Struct>& st, const u32 offset = 0) const
    {
        if (offset > 0) [[likely]]
            file_handle.seekg( offset, std::ios::beg );

        file_handle.read( reinterpret_cast<char*>( st.data() ), static_cast<std::streamsize>(st.size() * sizeof( Struct ) ));
    }
private:
    std::ifstream& file_handle;
};

#endif //EESAVEEDITOR_IO_H