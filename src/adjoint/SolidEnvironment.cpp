


#include <adjoint/SolidEnvironment.hpp>

using namespace adjoint;

SolidEnvironment::SolidEnvironment( Context* context, optix::float3 color )
    : Environment( context ),
      m_color( color )
{
}
    

optix::Program SolidEnvironment::getMissProgram()
{
    if( m_miss_program )
        return m_miss_program;

    m_miss_program = m_context->createProgram( "solid_environment.cu",
                                               "solid_environment" );
    m_miss_program[ "color" ]->setFloat( m_color );

    return m_miss_program;
}

