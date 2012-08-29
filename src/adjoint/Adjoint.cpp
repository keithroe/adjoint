

#include <cassert>
#include <iostream>

#include <Adjoint.hpp>
#include <config.hpp>


using namespace adjoint;


#define OPTIX_CATCH_RETHROW                                                    \
    catch ( optix::Exception& e )                                              \
    {                                                                          \
        std::cerr << "optix failure\n\n\n";                                    \
        throw adjoint::Exception( std::string("OPTIX_EXCEPTION: ")+e.what() ); \
    }                                                                          \
    catch ( std::exception& e )                                                \
    {                                                                          \
        throw adjoint::Exception( e.what() ); \
    }                                                                          \
    catch (...)                                                                \
    {                                                                          \
        throw adjoint::Exception( std::string("unknown exception thrown") );   \
    }



/*******************************************************************************\
 *
 * Exception class
 *
\*******************************************************************************/

Exception::Exception()
    : std::runtime_error( "unknown adjoint exception" )
{
}


Exception::Exception( const std::string& mssg )
    : std::runtime_error( mssg )
{
}



/*******************************************************************************\
 *
 * Context class
 *
\*******************************************************************************/

Context::Context()
    : m_camera( 0 ),
      m_environment( 0 )
      
{
    try
    {
        m_optix_context = optix::Context::create();
        m_optix_context->setEntryPointCount( 1 );
        m_optix_context->setRayTypeCount( 2 );
        m_optix_context->setStackSize( 1200 );
        m_optix_context[ "radiance_ray_type" ]->setUint( 0u );
        m_optix_context[ "visibility_ray_type" ]->setUint( 1u );
        m_optix_context[ "output_buffer" ]->set( m_optix_context->createBuffer( RT_BUFFER_OUTPUT, RT_FORMAT_FLOAT3 ) );

        optix::GeometryGroup geom_group = m_optix_context->createGeometryGroup();
        geom_group->setAcceleration( m_optix_context->createAcceleration( "Bvh", "Bvh" ) );
        m_optix_context[ "top_object" ]->set( geom_group );

    }
    OPTIX_CATCH_RETHROW;
}


Context::~Context()
{
    m_optix_context->destroy();
}


Context* Context::create()
{
   std::cerr << "HELLO" << std::endl;
   return new Context;
}


void Context::destroy( Context* context )
{
   delete context;
   std::cerr << "GOODBYE" << std::endl;
}


void Context::setCamera( Camera* camera )
{
    assert( camera );
    m_camera = camera;
}


void Context::setEnvironment( Environment* environment )
{
    assert( environment );
    m_environment = environment;
}


void Context::addSphere( Sphere* sphere )
{
    assert( sphere );
    m_spheres.push_back( sphere );
}


void Context::render( size_t width, size_t height, float* output )
{
    assert( output );
    assert( m_camera );
    assert( m_environment );

    // TODO clean up old render state


    try
    {
        m_optix_context->setRayGenerationProgram( 0, m_camera->getRayGenProgram() );
        m_optix_context->setMissProgram( 0, m_environment->getMissProgram() );


        for( std::vector<Sphere*>::iterator it = m_spheres.begin();
             it != m_spheres.end();
             ++it )
        {
            addSphereToOptix( *it );
        }


        optix::Buffer output_buffer = m_optix_context[ "output_buffer" ]->getBuffer();
        output_buffer->setSize( width, height );

        m_optix_context->launch( 0, width, height );

        memcpy( output, output_buffer->map(), sizeof( optix::float3 ) * width * height );
        output_buffer->unmap();
    }
    OPTIX_CATCH_RETHROW;

}


optix::Program Context::createProgram( const std::string& cuda_file,
                                       const std::string& name )
{
    try
    {
        std::string path = adjoint::PTX_DIR + "/cuda_compile_ptx_generated_" +
                           cuda_file + ".ptx";
        optix::Program program;
        program = m_optix_context->createProgramFromPTXFile( path, name );

        std::cerr << "Successfully loaded optix program " << name << " from: "
                  << cuda_file << std::endl;;

        return program;
    }
    OPTIX_CATCH_RETHROW;
}


optix::Geometry Context::createGeometry( size_t num_primitives, 
                                         optix::Program intersect,
                                         optix::Program bbox )
{
    try
    {
        optix::Geometry geometry = m_optix_context->createGeometry();
        geometry->setPrimitiveCount( num_primitives );
        geometry->setIntersectionProgram( intersect );
        geometry->setBoundingBoxProgram( bbox );
        return geometry;
    }
    OPTIX_CATCH_RETHROW;
}


void Context::addSphereToOptix( Sphere* sphere )
{

}

/*******************************************************************************\
 *
 * Camera class
 *
\*******************************************************************************/

Camera::~Camera()
{
}


Camera::Camera( Context* context )
    : Contextualized( context )
{
}


/*******************************************************************************\
 *
 * Surface class
 *
\*******************************************************************************/

Surface::~Surface()
{
}


Surface::Surface( Context* context )
    : Contextualized( context )
{
}

    
/*******************************************************************************\
 *
 * Environment class
 *
\*******************************************************************************/

Environment::~Environment()
{
}


Environment::Environment( Context* context )
    : Contextualized( context )
{
}
