

#ifndef ADJOINT_LAMBERTIAN_HPP_
#define ADJOINT_LAMBERTIAN_HPP_


#include <adjoint/Adjoint.hpp>

namespace adjoint
{


class LambertianSurface : public Surface
{
public:
    LambertianSurface( Context* context, optix::float3 color );


    bool           isEmitter() const  { return false; }
    bool           isVolume() const   { return false; }
    optix::Program getClosestHit();

private:

    optix::float3     m_color;
    optix::Program    m_closest_hit;
};


}


#endif // ADJOINT_LAMBERTIAN_HPP_
