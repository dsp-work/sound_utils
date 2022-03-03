#include <reader.hpp>

namespace sound_utils
{
    namespace reader
    {
        FILE* open_file( const std::string& filename, const std::string& mode, const std::string& call_file, const int call_line )
        {
            if ( mode.size() > 2 )
            {
                fprintf( stderr, "Error: [%s l.%d]Incorrect input.(file name : %s, mode : %s)\n", call_file.c_str(), call_line, filename.c_str(), mode.c_str() );
                exit( EXIT_FAILURE );
            }
            auto fp = fopen( filename.c_str(), mode.c_str() );
            if ( fp == NULL )
            {
                fprintf( stderr, "Error: [%s l.%d]Can't open file.(file name : %s, mode : %s)\n", call_file.c_str(), call_line, filename.c_str(), mode.c_str() );
                exit( EXIT_FAILURE );
            }
            return fp;
        }


    }    // namespace reader
}    // namespace sound_utils