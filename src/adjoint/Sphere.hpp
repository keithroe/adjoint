

#ifndef ADJOINT_SPHERE_HPP_
#define ADJOINT_SPHERE_HPP_

#include <cassert>

#include <optixu/optixpp_namespace.h>
#include <optixu/optixu_math_namespace.h>

#include <Utility.hpp>

namespace adjoint
{

class Context;
class Surface;

class Sphere : public Contextualized
{
public:
    Sphere( Context* context, float radius, optix::float3 center, Surface* surface );
    ~Sphere(); 

    Surface*               getSurface() const;
    float                  getRadius() const;
    optix::float3          getCenter() const;

    optix::Geometry        getGeometry();

private:
    float                  m_radius;
    optix::float3          m_center;
    Surface*               m_surface;
    optix::Geometry        m_geometry;

    static optix::Program  s_intersection_program;
    static optix::Program  s_bounding_box_program;
};


} // end namespace adjoint


#endif // ADJOINT_SPHERE_HPP_
