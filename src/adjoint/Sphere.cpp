

#include <adjoint/Adjoint.hpp>
#include <adjoint/Sphere.hpp>

using namespace adjoint;


optix::Program  Sphere::s_intersection_program;
optix::Program  Sphere::s_bounding_box_program;



Sphere::Sphere( Context* context, float radius, optix::float3 center, Surface* surface )
    : Contextualized( context ),
      m_radius( radius ), 
      m_center( center ),
      m_surface( surface )
{
    assert( m_surface );
}

Sphere::~Sphere()
{
    // Allow the optix::Context to clean up optix resources
}


adjoint::Surface* Sphere::getSurface() const
{
    return m_surface;
}


float Sphere::getRadius() const
{
    return m_radius;
}


optix::float3 Sphere::getCenter() const
{
    return m_center;
}


optix::Geometry Sphere::getGeometry()
{
    if( m_geometry )
        return m_geometry;

    if( !s_intersection_program )
        s_intersection_program = m_context->createProgram( "sphere.cu",
                                                           "sphere_intersect" );

    if( !s_bounding_box_program )
        s_bounding_box_program = m_context->createProgram( "sphere.cu",
                                                           "sphere_bbox" );

    m_geometry = m_context->createGeometry( 1u, s_intersection_program, s_bounding_box_program );
    m_geometry[ "radius" ]->setFloat( m_radius );
    m_geometry[ "center" ]->setFloat( m_center );
    return m_geometry;
}
