
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
