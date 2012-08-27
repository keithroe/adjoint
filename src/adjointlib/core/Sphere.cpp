

#include <core/Sphere.hpp>

using namespace adjoint;


optix::Program  Sphere::s_intersection_program;
optix::Program  Sphere::s_bounding_box_program;



Sphere::Sphere( Context* context, float radius, float center[3], Surface* surface )
    : Contextualized( context ),
      m_radius( radius ), 
      m_surface( surface )
{
    assert( m_surface );
    m_center[ 0 ] = center[ 0 ];
    m_center[ 1 ] = center[ 1 ];
    m_center[ 2 ] = center[ 2 ];
}



adjoint::Surface* Sphere::getSurface()
{
    return m_surface;
}



float Sphere::getRadius()
{
    return m_radius;
}



void Sphere::getCenter( float center[3] )
{
    center[ 0 ] = m_center[ 0 ];
    center[ 1 ] = m_center[ 1 ];
    center[ 2 ] = m_center[ 2 ];
}



optix::Program Sphere::getIntersectionProgram()
{
    if( s_intersection_program )
        return s_intersection_program;

    // TODO
    return 0;
}


optix::Program Sphere::getBoundingBoxProgram()
{
    if( s_bounding_box_program )
        return s_bounding_box_program;

    // TODO
    return 0;
}
