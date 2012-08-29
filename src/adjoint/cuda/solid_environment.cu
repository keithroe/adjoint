

#include <optix_world.h>
#include <cuda/common.hpp>

rtDeclareVariable(float3, color, , );

rtDeclareVariable(RadiancePRD, prd, rtPayload, );

RT_PROGRAM void solid_environment()
{
  prd.result = 0.1f;
}
