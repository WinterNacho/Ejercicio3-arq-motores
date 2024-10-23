set(CMAKE_LEGACY_CYGWIN_WIN32 OFF)
cmake_minimum_required(VERSION 3.15)
project(Planets C CXX)
add_subdirectory(MonaEngine)
set(Planets_lib_INCLUDE_DIRECTORY Planets_lib/public)
add_executable(Planets Planets.cpp) 
set_property(TARGET Planets  PROPERTY CXX_STANDARD 20)
target_link_libraries(Planets  PRIVATE MonaEngine)
target_include_directories(Planets  PRIVATE  ${MONA_INCLUDE_DIRECTORY} ${THIRD_PARTY_INCLUDE_DIRECTORIES} ${Planets_lib_INCLUDE_DIRECTORY})
add_custom_command(TARGET Planets POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different 
    $<TARGET_FILE:OpenAL> $<TARGET_FILE_DIR:Planets>)  