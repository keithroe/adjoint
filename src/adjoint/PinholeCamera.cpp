

#include <PinholeCamera.hpp>

using namespace adjoint;


namespace
{
    inline float DtoR(float d)
    {
        return d*(static_cast<float>(M_PI)/180.f);
    }


    inline float RtoD(float r)
    {
        return r*(180.f/static_cast<float>(M_PI));
    }
}


PinholeCamera::PinholeCamera( Context* context,
                              optix::float3 eye,
                              optix::float3 lookat,
                              optix::float3 up,
                              float hfov,
                              float vfov )
    : Camera( context )
{

  optix::float3 lookdir = optix::normalize( lookat-eye );
  up  = optix::normalize( up );
  m_U = optix::normalize( optix::cross( lookdir, up ) );
  m_V = optix::normalize( optix::cross( m_U, lookdir ) );

  float ulen = tanf( DtoR( hfov*0.5f ) );
  m_U = m_U * ulen;

  float vlen = tanf( DtoR( vfov*0.5f ) );
  m_V = m_V * vlen;


  //m_ray_gen_program = context->getOptixContext()->createProgramFromPTXFile( ptx

  


}


optix::Program PinholeCamera::getRayGenProgram() const
{
    return m_ray_gen_program;
}

