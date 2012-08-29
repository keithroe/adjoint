
if( NOT CMAKE_BUILD_TYPE )
    set( CMAKE_BUILD_TYPE "Release" CACHE STRING
         "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel."
         FORCE )
endif( NOT CMAKE_BUILD_TYPE )

include_directories( "${CMAKE_SOURCE_DIR}/src/adjointlib" )

add_definitions( -Wall -Werror -funroll-loops -floop-optimize -ffast-math )

find_package( OptiX REQUIRED )
find_package( OPENEXR REQUIRED )
find_package( CUDA 4.2 REQUIRED )

# Add the path to the OptiX headers to our include paths.
include_directories(
    "${CMAKE_SOURCE_DIR}/src/adjoint" 
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CUDA_INCLUDE_DIRS}" 
    "${OPENEXR_INCLUDE_PATHS}"
    "${OptiX_INCLUDE}"
    )

# Tell clang_complete about our include paths
#configure_file( "${CMAKE_CURRENT_SOURCE_DIR}/clang_complete.in"  "${CMAKE_CURRENT_SOURCE_DIR}/.clang_complete" )

add_subdirectory( adjoint )
add_subdirectory( adjointu )
add_subdirectory( standalone )

