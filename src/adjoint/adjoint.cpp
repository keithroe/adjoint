

#include <iostream>
#include <Core/Adjoint.hpp>

int main( int argc, char** argv )
{
    std::cerr << "HELLO" << std::endl;

    std::cerr << adjoint::Context::create() << std::endl;
}
