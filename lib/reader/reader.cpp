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

        sound_utils::reader::WavIO read_wav( const std::string& filename )
        {
#if __GNUC__ > 5
            if ( !std::regex_search( filename, std::regex( ".+\\.wav" ) ) )
            {
                fprintf( stderr, "Error: [%s l.%d]Incorrect file name.(file name : %s)\n", __FILE__, __LINE__, filename.c_str() );
                exit( EXIT_FAILURE );
            }
#else
            if ( filename.find( ".wav" ) == std::string::npos )
            {
                fprintf( stderr, "Error: [%s l.%d]Incorrect file name.(file name : %s)\n", __FILE__, __LINE__, filename.c_str() );
                exit( EXIT_FAILURE );
            }
#endif
            sound_utils::reader::WavIO sound;
            auto fp = open_file( filename, "rb", __FILE__, __LINE__ );
            char riff_chunk_ID[4];
            unsigned int riff_chunk_size;
            char riff_form_type[4];
            char fmt_chunk_ID[4];
            unsigned int fmt_chunk_size;
            short int fmt_wave_format_type;
            short int fmt_channel;
            unsigned int fmt_samples_per_sec;
            unsigned int fmt_bytes_per_sec;
            short int fmt_block_size;
            short int fmt_bits_per_sample;
            char data_chunk_ID[4];
            unsigned int data_chunk_size;

            std::fread( riff_chunk_ID, 1, 4, fp );
            std::fread( &riff_chunk_size, 4, 1, fp );
            std::fread( riff_form_type, 1, 4, fp );
            std::fread( fmt_chunk_ID, 1, 4, fp );
            std::fread( &fmt_chunk_size, 4, 1, fp );
            std::fread( &fmt_wave_format_type, 2, 1, fp );
            std::fread( &fmt_channel, 2, 1, fp );
            std::fread( &fmt_samples_per_sec, 4, 1, fp );
            std::fread( &fmt_bytes_per_sec, 4, 1, fp );
            std::fread( &fmt_block_size, 2, 1, fp );
            std::fread( &fmt_bits_per_sample, 2, 1, fp );
            std::fread( data_chunk_ID, 1, 4, fp );
            std::fread( &data_chunk_size, 4, 1, fp );

            sound.channel = fmt_channel;
            sound.quantization_bit = fmt_bits_per_sample;
            sound.sampling_frequency = fmt_samples_per_sec;
            sound.datasize = data_chunk_size / ( sound.quantization_bit / 8 ) / sound.channel;

            if ( sound.quantization_bit == 16 )
            {
                std::vector< short > buf( sound.datasize );
                fread( buf.data(), sizeof( short ), sound.datasize, fp );
                for ( size_t i = 0, max = buf.size(); i < max; ++i )
                {
                    sound.data.push_back( static_cast< double >( buf.at( i ) ) );
                }
            }
            fclose( fp );
            return sound;
        }
    }    // namespace reader
}    // namespace sound_utils