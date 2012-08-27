

#include <core/PinholeCamera.hpp>

using namespace adjoint;



PinholeCamera::PinholeCamera( Context* context,
                              optix::float3 eye,
                              optix::float3 lookat,
                              optix::float3 up,
                              float hfov,
                              float vfov )
    : Camera( context )
{
}


optix::Program PinholeCamera::getRayGenProgram() const
{
    if( m_ray_gen_program )
        return m_ray_gen_program;

    // TODO
    return 0;
}

