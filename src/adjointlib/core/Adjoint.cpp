
#include <iostream>

#include <core/Adjoint.hpp>

using namespace adjoint;


Context::Context()
{
}


Context* Context::create()
{
   std::cerr << "GOODBYE" << std::endl;
   return new Context;
}



Camera::~Camera()
{
}


Camera::Camera( Context* context )
    : Contextualized( context )
{
}


Surface::~Surface()
{
}


Surface::Surface( Context* context )
    : Contextualized( context )
{
}

    
Environment::~Environment()
{
}


Environment::Environment( Context* context )
    : Contextualized( context )
{
}
