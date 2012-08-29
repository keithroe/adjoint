

#ifndef ADJOINT_SOLID_ENVIRONMENT_HPP_
#define ADJOINT_SOLID_ENVIRONMENT_HPP_


#include <adjoint/Adjoint.hpp>

namespace adjoint
{


class SolidEnvironment : public Environment
{
public:
    SolidEnvironment( Context* context, optix::float3 color );
    
    optix::Program getMissProgram();

private:

    optix::float3    m_color;
    optix::Program   m_miss_program;
};

}


#endif // ADJOINT_SOLID_ENVIRONMENT_HPP_

