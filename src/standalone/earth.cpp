

#include <iostream>
#include <Adjoint.hpp>

int main( int argc, char** argv )
{
    std::cerr << "HELLO" << std::endl;

    std::cerr << adjoint::Context::create() << std::endl;
}
