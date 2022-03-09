#include "reader.hpp"

#include <cstdio>
#include <string>
#include <vector>

void run_open_file();
void test_read_wav();

int main( int argc, char** argv )
{
    std::vector< std::string > args( argv, argv + argc );

    if ( args.at( 1 ) == std::string( "open_file" ) )
    {
        run_open_file();
    }
    else if ( args.at( 1 ) == std::string( "read_wav" ) )
    {
        test_read_wav();
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

void test_read_wav()
{
    auto wav = sound_utils::reader::read_wav( "test.wav" );
    if ( wav.channel != 2 )
    {
        fprintf( stderr, "Different number of 'channel'.: %d\n", wav.channel );
        exit( -1 );
    }
    if ( wav.sampling_frequency != 16000 )
    {
        fprintf( stderr, "Different number of 'sampling_frequency'.: %d\n", wav.sampling_frequency );
        exit( -1 );
    }
    if ( wav.quantization_bit != 16 )
    {
        fprintf( stderr, "Different number of 'quantization_bit'.: %d\n", wav.quantization_bit );
        exit( -1 );
    }
    if ( wav.datasize != 72000 )
    {
        fprintf( stderr, "Different number of 'datasize'.: %d\n", wav.quantization_bit );
        exit( -1 );
    }
    if ( wav.data.size() <= 0 )
    {
        fprintf( stderr, "No data loaded.\n" );
        exit( -1 );
    }
}