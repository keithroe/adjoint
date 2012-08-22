
//
// License, etc
// 

#include <optixu/optixpp_namespace.h>


namespace adjoint
{

class Camera;
class Environment;
class Light;
class Mesh;
class Surface;

class Context
{
public:
    static Context* create();
    
    ~Context();

    void setCamera( const Camera* camera );

    void addMesh( size_t num_verts, const float* verts, 
                  size_t num_tris,  const size_t* tris,
                  adjoint::Surface* shader );

    void addLight( const Light* light ); 

    void setEnvironment( const Environment* environment );

private:

    Context();
    Context( const Context& );
    Context& operator=( const Context& );

    optix::Context        m_optix_context;

    Camera*               m_camera;
    std::vector<Mesh*>    m_meshes;
    std::vector<Light*>   m_lights;
};



class Contextualized
{
public:
    Contextualized( adjoint::Context* context );

protected:
    adjoint::Context* m_context;
};



class Camera : public Contextualized
{
public:
    virtual ~Camera();
    virtual optix::Program getRayGenProgram() const = 0;
};



class Surface : public Contextualized
{
public:
    virtual ~Surface();

    virtual bool           isVolume() const = 0;
    virtual optix::Program getClosestHit() const = 0;
};



class Light : public Contextualized
{
public:
    virtual ~Light();
    virtual optix::Program getClosestHit() const = 0;
    virtual optix::Program getIntersectionProgram() const = 0;
};


class Environment : public Contextualized
{
public:
    virtual ~Environment();
    virtual optix::Program getClosestHit() const = 0;
    virtual optix::Program getIntersectionProgram() const = 0;
};




} // end namespace adjoint
