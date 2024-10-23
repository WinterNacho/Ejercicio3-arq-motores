add_library(Planets_lib STATIC
    "private/asdasd")

target_include_directories(Planets_lib PRIVATE ${MONA_INCLUDE_DIRECTORY} ${THIRD_PARTY_INCLUDE_DIRECTORIES} "{CMAKE_CURRENT_SOURCE_DIR/public}")
target_link_libraries(Planets_lib PRIVATE MonaEngine)

set_property(TARGET Planets_lib PROPERTY CXX_STANDARD 20)