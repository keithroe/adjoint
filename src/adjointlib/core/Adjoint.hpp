
//
// License, etc
// 

#ifndef ADJOINT_CORE_ADJOINT_HPP_
#define ADJOINT_CORE_ADJOINT_HPP_



#include <optixu/optixpp_namespace.h>
#include <core/Utility.hpp>


namespace adjoint
{

class Camera;
class Environment;
class Light;
class Sphere;
class Surface;


class Context
{
public:
    static Context* create();
    
    ~Context();

    void setCamera( const Camera* camera );
    
    void setEnvironment( const Environment* environment );

    void addSphere( const Sphere* sphere );

private:

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
    virtual optix::Program getRayGenProgram() const = 0;
};



class Surface : public Contextualized
{
public:
    Surface( Context* context );
    virtual ~Surface();

    virtual bool           isEmitter() const = 0;
    virtual bool           isVolume() const = 0;
    virtual optix::Program getClosestHit() const = 0;
};



class Environment : public Contextualized
{
public:
    Environment( Context* context );
    virtual ~Environment();

    virtual optix::Program getMissProgram() const = 0;
};



} // end namespace adjoint


#endif // ADJOINT_CORE_ADJOINT_HPP_
