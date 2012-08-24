
set( PTX_OUTPUT_DIR "${CMAKE_BINARY_DIR}/lib/ptx" CACHE PATH
     "Path to where generated PTX is stored" 
     ) 

set( CUDA_GENERATED_OUTPUT_DIR ${PTX_OUTPUT_DIR} )

# Set up build .cu -> .ptx build 
#CUDA_COMPILE_PTX( ptx_files
#    Renderer/Cuda/hit.cu
#    Renderer/Cuda/raygen.cu
#    Renderer/Cuda/trimesh.cu
#    )

#configure_file( "${CMAKE_CURRENT_SOURCE_DIR}/Core/config.hpp.in"
#                "${CMAKE_BINARY_DIR}/include/config.hpp" )

include_directories( "${CMAKE_BINARY_DIR}/include" )


# build the library and ptx files
add_library( adjointlib SHARED
    ${ptx_files}
    core/Adjoint.hpp
    core/Adjoint.cpp
    core/Mesh.cpp
    core/Mesh.hpp
    core/Utility.hpp
    )

# Link against optix
target_link_libraries( adjointlib 
    optix
    ${optix_rpath}
    ${OPENEXR_LIBRARIES}
    )



