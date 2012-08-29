
//
// License, etc
// 

#ifndef ADJOINT_CORE_ADJOINT_HPP_
#define ADJOINT_CORE_ADJOINT_HPP_



#include <stdexcept>
#include <optixu/optixpp_namespace.h>
#include <Utility.hpp>


namespace adjoint
{

class Camera;
class Environment;
class Light;
class Sphere;
class Surface;



class Exception : public std::runtime_error
{
public:
    Exception();
    Exception( const std::string& mssg );
};



class Context
{
public:
    static Context*    create();
    static void        destroy( Context* context );
    

    void               setCamera( Camera* camera );
    
    void               setEnvironment( Environment* environment );

    void               addSphere( Sphere* sphere );

    void               render( size_t width, size_t height, float* output );

    
    optix::Program     createProgram( const std::string& cuda_file,
                                      const std::string& name );

    optix::Geometry    createGeometry( size_t num_primitives, 
                                       optix::Program intersect,
                                       optix::Program bbox );
private:

    void addSphereToOptix( Sphere* sphere );

    ~Context();
    Context();
    Context( const Context& );
    Context& operator=( const Context& );

    optix::Context        m_optix_context;

    Camera*               m_camera;
    Environment*          m_environment;
    std::vector<Sphere*>  m_spheres;
};



class Camera : public Contextualized
{
public:
    Camera( Context* context );
    virtual ~Camera();
    virtual optix::Program getRayGenProgram() = 0;
};



class Surface : public Contextualized
{
public:
    Surface( Context* context );
    virtual ~Surface();

    virtual bool           isEmitter() const = 0;
    virtual bool           isVolume() const = 0;
    virtual optix::Program getClosestHit() = 0;
};



class Environment : public Contextualized
{
public:
    Environment( Context* context );
    virtual ~Environment();

    virtual optix::Program getMissProgram() = 0;
};



} // end namespace adjoint


#endif // ADJOINT_CORE_ADJOINT_HPP_
