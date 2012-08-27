
#ifndef ADJOINT_PINHOLE_CAMERA_HPP_
#define ADJOINT_PINHOLE_CAMERA_HPP_

#include <cassert>

#include <optixu/optixpp_namespace.h>
#include <optixu/optixu_math_namespace.h>

#include <core/Adjoint.hpp>
#include <core/Utility.hpp>

namespace adjoint
{

class Context;
class Surface;

class PinholeCamera : public Camera
{
public:
    PinholeCamera( Context* context, 
                   optix::float3 eye,
                   optix::float3 lookat,
                   optix::float3 up,
                   float hfov,
                   float vfov );

    optix::Program getRayGenProgram() const;

private:

    optix::float3   m_U;
    optix::float3   m_V;
    optix::float3   m_W;

    optix::Program  m_ray_gen_program;
};


} // end namespace adjoint


#endif // ADJOINT_PINHOLE_CAMERA_HPP_
