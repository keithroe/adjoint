


#include <adjoint/LambertianSurface.hpp>

using namespace adjoint;


LambertianSurface::LambertianSurface( Context* context, optix::float3 color )
    : Surface( context ),
      m_color( color )
{
}


optix::Program LambertianSurface::getClosestHit()
{
    if( m_closest_hit )
        return m_closest_hit;

    m_closest_hit = m_context->createProgram( "lambertian_surface.cu",
                                              "lambertian_surface" );
    m_closest_hit[ "color" ]->setFloat( m_color );
    return m_closest_hit;
}

