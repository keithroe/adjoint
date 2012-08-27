

#ifndef ADJOINT_SPHERE_HPP_
#define ADJOINT_SPHERE_HPP_

#include <cassert>

#include <optixu/optixpp_namespace.h>

#include <core/Utility.hpp>

namespace adjoint
{

class Context;
class Surface;

class Sphere : public Contextualized
{
public:
    Sphere( Context* context, float radius, float center[3], Surface* surface );

    Surface*               getSurface();
    float                  getRadius();
    void                   getCenter( float center[3] );

    static optix::Program  getIntersectionProgram();
    static optix::Program  getBoundingBoxProgram();

private:
    float                  m_radius;
    float                  m_center[3];
    Surface*               m_surface;

    static optix::Program  s_intersection_program;
    static optix::Program  s_bounding_box_program;
};


} // end namespace adjoint


#endif // ADJOINT_SPHERE_HPP_
