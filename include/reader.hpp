#ifndef __READER_HPP_
#define __READER_HPP_

#include <Eigen/Dense>
#include <cstdio>
#include <cstdlib>
#include <file_operation>
#include <regex>
#include <string>
#include <vector>


namespace sound_utils
{
    namespace reader
    {
        enum WavType
        {
            Short,
            Float
        };

        struct WavIO
        {
            unsigned short channel;
            unsigned short quantization_bit;
            unsigned int sampling_frequency;
            unsigned int datasize;
            Eigen::VectorXd data;

        public:

            EIGEN_MAKE_ALIGNED_OPERATOR_NEW
        };

        FILE* open_file( const std::string&, const std::string&, const std::string& call_file, const int call_line );
        WavIO read_wav( const std::string& );
    }    // namespace reader
}    // namespace sound_utils

#endif /* __READER_HPP_ */