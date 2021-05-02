cmake_minimum_required(VERSION 3.1)


include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/raytrace)

add_executable(PCam run.cpp)

target_link_libraries(PCam sive-util)
target_link_libraries(PCam ${Boost_PROGRAM_OPTIONS_LIBRARIES})
target_link_libraries(PCam ${PNG_LIBRARY})
target_link_libraries(PCam ${ZLIB_LIBRARY})

#add_executable(PCam PerspectiveCamera.cpp)
#add_library(Scene SceneContainer.cpp)

