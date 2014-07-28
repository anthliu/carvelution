include_directories (${carvelution_SOURCE_DIR}/include)

find_package (Qt4 REQUIRED)
include (${QT_USE_FILE})
add_definitions (${QT_DEFINITIONS})

file (GLOB carvelution_SOURCES "*.cpp")

add_executable (carvelution ${carvelution_SOURCES})

target_link_libraries (carvelution SFML-graphics SFML-system SFML-window Box2d ${QT_LIBRARIES})