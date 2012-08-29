

#include <optix_world.h>
#include <cuda/common.hpp>

using namespace optix;


rtDeclareVariable(float3,        eye, , );
rtDeclareVariable(float3,        U, , );
rtDeclareVariable(float3,        V, , );
rtDeclareVariable(float3,        W, , );
rtDeclareVariable(rtObject,      top_object, , );
rtDeclareVariable(float,         epsilon, , );
rtDeclareVariable(unsigned int,  radiance_ray_type, , );

// Should be float4 for max perf.  keeping it simple
rtBuffer<float3, 2>              output_buffer;

rtDeclareVariable(uint2, launch_index, rtLaunchIndex, );
rtDeclareVariable(uint2, launch_dim,   rtLaunchDim, );


RT_PROGRAM void pinhole_camera()
{
  float2 d         = make_float2( launch_index ) / 
                     make_float2( launch_dim )   *
                     2.0f - 1.0f;
  float3 origin    = eye;
  float3 direction = normalize(d.x*U + d.y*V + W);
  
  optix::Ray ray   = optix::make_Ray( origin,
                                      direction,
                                      radiance_ray_type,
                                      epsilon,
                                      RT_DEFAULT_MAX);

  RadiancePRD prd;
  prd.result     = 0.0f;
  prd.importance = 1.0f;
  prd.wavelength = 680.0f; // TODO

  rtTrace( top_object, ray, prd );

  output_buffer[ launch_index ] = make_float3( prd.result );
}

