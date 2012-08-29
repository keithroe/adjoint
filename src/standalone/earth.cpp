

#include <iostream>

#include <Adjoint/Adjoint.hpp>
#include <Adjoint/LambertianSurface.hpp>
#include <Adjoint/PinholeCamera.hpp>
#include <Adjoint/SolidEnvironment.hpp>
#include <Adjoint/Sphere.hpp>


int main( int argc, char** argv )
{
    adjoint::Context* context = adjoint::Context::create();

    adjoint::PinholeCamera* camera = new adjoint::PinholeCamera(
            context,
            optix::make_float3( 0.0f, 0.0f, -10.0f ),
            optix::make_float3( 0.0f, 0.0f, 0.0f ),
            optix::make_float3( 0.0f, 1.0f, 0.0f ),
            60.0f,
            45.0f );

    context->setCamera( camera );

    adjoint::SolidEnvironment* environment = new adjoint::SolidEnvironment(
            context,
            optix::make_float3( 0.0f, 0.0f, 1.0f ) );
    context->setEnvironment( environment );

    adjoint::Surface* earth_surface = new adjoint::LambertianSurface(
            context, 
            optix::make_float3( 1.0f, 0.0f, 1.0f ) );

    adjoint::Sphere* earth = new adjoint::Sphere(
            context, 1.0f,
            optix::make_float3( 0.0f ),
            earth_surface );
    context->addSphere( earth );
    
    const unsigned width  = 1024u;
    const unsigned height = 768u;
    float* raster = new float[ 3 * width * height ];
    context->render( width, height, raster );

    adjoint::Context::destroy( context );

    delete camera;
    delete environment;
    delete earth_surface;
    delete earth;
    delete [] raster;
}
