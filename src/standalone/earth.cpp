

#include <iostream>

#include <adjoint/Adjoint.hpp>
#include <adjoint/LambertianSurface.hpp>
#include <adjoint/PinholeCamera.hpp>
#include <adjoint/SolidEnvironment.hpp>
#include <adjoint/Sphere.hpp>
#include <adjointu/ImageIO.hpp>


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
    adjointu::writeOpenEXR( "out.exr", width, height, raster );

    adjoint::Context::destroy( context );

    delete camera;
    delete environment;
    delete earth_surface;
    delete earth;
    delete [] raster;
}
