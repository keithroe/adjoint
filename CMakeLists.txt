
cmake_minimum_required( VERSION 2.8 )
project( Adjoint ) 

set( CMAKE_MODULE_PATH
     "${CMAKE_SOURCE_DIR}/CMake"
    )

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

add_subdirectory( src )
