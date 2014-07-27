include_directories (${carvelution_SOURCE_DIR}/include)

file (GLOB carvelution_SOURCES "*.cpp")

add_executable (carvelution ${carvelution_SOURCES})

target_link_libraries (carvelution SFML-graphics SFML-system SFML-window Box2d)