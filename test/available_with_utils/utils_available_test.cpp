#include <cassert>
#include <cstdio>
#include <string>
#include <DspWorkUtils/string>
#include <vector>


void run_split_string();

int main( int argc, char** argv )
{
    std::vector< std::string > args( argv, argv + argc );

    if ( args.at( 1 ) == std::string( "split_string" ) )
    {
        run_split_string();
    }
    else
    {
        fprintf( stderr, "Matching test is not exist.\n" );
        exit( -1 );
    }
}

void run_split_string()
{
    using std::string;

    string base( "No,one.two,three" );
    auto split_str = dsp_work_utils::split_char( base, ',' );

    assert( 3 == split_str.size() );
    assert( string( "No" ) == split_str.at( 0 ) );
    assert( string( "one.two" ) == split_str.at( 1 ) );
    assert( string( "three" ) == split_str.at( 2 ) );
}