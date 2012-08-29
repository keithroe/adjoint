


# build the library and ptx files
add_library( adjointu SHARED
    ImageIO.cpp
    ImageIO.hpp
    )

# Link against optix
target_link_libraries( adjointu
    ${OPENEXR_LIBRARIES}
    )



