#include "reader.hpp"

#include <cstdio>
#include <string>
#include <vector>

void run_open_file();

int main( int argc, char** argv )
{
    std::vector< std::string > args( argv, argv + argc );

    if ( args.at( 1 ) == std::string( "open_file" ) )
    {
        run_open_file();
    }
    else
    {
        fprintf( stderr, "Matching test is not exist.\n" );
        exit( -1 );
    }
}

void run_open_file()
{
    FILE* fp = NULL;
    fp = sound_utils::reader::open_file( "test.txt", "r", __FILE__, __LINE__ );
    fclose( fp );
    fp = sound_utils::reader::open_file( "test.txt", "w", __FILE__, __LINE__ );
    fclose( fp );
    fp = sound_utils::reader::open_file( "test.txt", "rb", __FILE__, __LINE__ );
    fclose( fp );
    fp = sound_utils::reader::open_file( "test.txt", "wb", __FILE__, __LINE__ );
    fclose( fp );
    // fp = sound_utils::reader::open_file( "test.txt", "zz", __FILE__, __LINE__ );
    // fclose( fp );
    // fp = sound_utils::reader::open_file( "test.txt", "hoge", __FILE__, __LINE__ );
    // fclose( fp );
}