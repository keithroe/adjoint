

#ifndef ADJOINT_CORE_MESH_HPP_
#define ADJOINT_CORE_MESH_HPP_

#include <optixu/optixpp_namespace.h>

namespace adjoint
{


class Surface;

class Mesh
{
public:
    Mesh( size_t num_verts, const float* verts, 
          size_t num_tris,  const size_t* tris,
          adjoint::Surface* shader );

    const optix::Program    getIntersectionProgram()const;
    const optix::Program    getBoundsProgam()const;

    const adjoint::Surface* getSurface()const;

private:
    adjoint::Surface* m_shader;

};


} // end namespace adjoint


#endif // ADJOINT_CORE_MESH_HPP_
