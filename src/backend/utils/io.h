#ifndef EESAVEEDITOR_IO_H
#define EESAVEEDITOR_IO_H

#include <fstream>
#include <vector>

#include "aliases.h"

/**
 * This class encapsulates casting binary data into the structs easily.
 * Mostly to hide the ugliness of that whole process.
 */
class StructWriter
{
public:
    explicit StructWriter( std::ifstream& file_handle ) noexcept : m_file_handle( file_handle ) { }

    /**
     * Reads the binary data from the std::ifstream from the provided offset
     * and writes it into the passed struct.
     *
     * @tparam Struct Type of struct to write into
     * @param st Specific struct instance to write into
     * @param offset Offset in the file to read from
     */
    template<typename Struct>
    void into( Struct& st, const u32 offset = 0 ) const
    {
        if ( offset > 0 ) [[likely]]
        {
            m_file_handle.seekg( offset, std::ios::beg );
        }

        m_file_handle.read( reinterpret_cast<char*>(&st), sizeof( Struct ) );
    }

    /**
     * Reads the binary data from the std::ifstream from the provided offset
     * and writes it into the passed vector of structs.
     *
     * @tparam Struct Type of struct to write into
     * @param st Vector of specific struct instances to write into
     * @param offset Offset in the file to read from
     */
    template<typename Struct>
    void into( std::vector<Struct>& st, const u32 offset = 0 ) const
    {
        if ( offset > 0 ) [[likely]]
        {
            m_file_handle.seekg( offset, std::ios::beg );
        }

        m_file_handle.read( reinterpret_cast<char*>(st.data()),
                          static_cast<std::streamsize>(st.size() * sizeof( Struct )) );
    }

private:
    std::ifstream& m_file_handle;
};

class BinaryWriter
{
public:
    explicit BinaryWriter( std::ofstream& file_handle ) : m_file_handle( file_handle ) { }

    template<typename Struct>
    void out( Struct& st, const u32 offset = 0 ) const
    {
        if ( offset > 0 ) [[likely]]
        {
            m_file_handle.seekp( offset, std::ios::beg );
        }

        m_file_handle.write( reinterpret_cast<const char*>(&st), sizeof( Struct ) );
    }

private:
    std::ofstream& m_file_handle;
};

#endif //EESAVEEDITOR_IO_H
