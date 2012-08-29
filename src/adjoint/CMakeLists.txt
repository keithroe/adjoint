
set( PTX_OUTPUT_DIR "${CMAKE_BINARY_DIR}/lib/ptx" CACHE PATH
    "Path to where generated PTX is stored" 
    ) 

set( CUDA_GENERATED_OUTPUT_DIR ${PTX_OUTPUT_DIR} )

# Set up build .cu -> .ptx build 
set( CUDA_SOURCES
    cuda/common.hpp
    cuda/pinhole_camera.cu
    cuda/solid_environment.cu
    )

CUDA_COMPILE_PTX( ptx_files
    ${CUDA_SOURCES}
    )

configure_file( "${CMAKE_CURRENT_SOURCE_DIR}/config.hpp.in"
                "${CMAKE_BINARY_DIR}/include/config.hpp" )

include_directories( "${CMAKE_BINARY_DIR}/include" )

# build the library and ptx files
add_library( adjoint SHARED
    ${ptx_files}
    ${CUDA_SOURCES}
    Adjoint.cpp
    Adjoint.hpp
    LambertianSurface.cpp
    LambertianSurface.hpp
    PinholeCamera.cpp
    PinholeCamera.hpp
    SolidEnvironment.cpp
    SolidEnvironment.hpp
    Sphere.cpp
    Sphere.hpp
    Utility.hpp
    )

# Link against optix
target_link_libraries( adjoint 
    optix
    ${optix_rpath}
    ${OPENEXR_LIBRARIES}
    )



