#ifndef __READER_HPP_
#define __READER_HPP_

#include <cstdio>
#include <cstdlib>
#include <string>

namespace sound_utils
{
    namespace reader
    {
        FILE* open_file( const std::string&, const std::string&, const std::string& call_file, const int call_line );
    }
}    // namespace sound_utils

#endif /* __READER_HPP_ */