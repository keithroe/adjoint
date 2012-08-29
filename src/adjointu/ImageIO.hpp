

#ifndef ADJOINTU_IMAGE_IO_HPP_
#define ADJOINTU_IMAGE_IO_HPP_

#include <string>

namespace adjointu
{

bool writeOpenEXR( const std::string& filename,
        unsigned int width,
        unsigned int height,
        const float* pixels );
}


#endif // ADJOINTU_IMAGE_IO_HPP_
