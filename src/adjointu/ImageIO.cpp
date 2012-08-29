

#include <adjointu/ImageIO.hpp>

#include <ImfOutputFile.h>
#include <ImfInputFile.h>
#include <ImfRgbaFile.h>
#include <ImfChannelList.h>
#include <ImfFrameBuffer.h>


using namespace adjointu;

bool adjointu::writeOpenEXR( const std::string& filename,
                             unsigned int width,
                             unsigned int height,
                             const float* pixels )
{
    try
    {
        Imf::Header header( width, height );
        header.channels().insert ("R", Imf::Channel( Imf::FLOAT ) );
        header.channels().insert ("G", Imf::Channel( Imf::FLOAT ) );
        header.channels().insert ("B", Imf::Channel( Imf::FLOAT ) );


        Imf::OutputFile file( filename.c_str(), header );
        Imf::FrameBuffer frame_buffer;
        const unsigned int element_stride = sizeof(float)*3;

        frame_buffer.insert( "R", Imf::Slice( Imf::FLOAT,                // type
                                              (char*)&pixels[0],         // base
                                              element_stride,            // xStride
                                              element_stride*width ) );  // yStride

        frame_buffer.insert( "G", Imf::Slice( Imf::FLOAT,                // type
                                              (char*)&pixels[1],         // base
                                              element_stride,            // xStride
                                              element_stride*width ) );  // yStride

        frame_buffer.insert( "B", Imf::Slice( Imf::FLOAT,                // type
                                              (char*)&pixels[2],         // base
                                              element_stride,            // xStride
                                              element_stride*width ) );  // yStride

        file.setFrameBuffer( frame_buffer );
        file.writePixels( height );
        return true;
    }
    catch( std::exception& e )
    {
        std::cerr << e.what() << std::endl;
        return false;
    }
}
