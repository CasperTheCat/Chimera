cmake_minimum_required (VERSION 3.1)
set (CMAKE_CXX_STANDARD 17)

project (Chimera VERSION 0.0.1 DESCRIPTION "Project Chimera")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")


set(SourceFiles
./core/Source.cpp
)

set(HeaderFiles
)

# Make the real project executable
#link_directories(${CMAKE_SOURCE_DIR}/lib)
add_executable(Chimera ${HeaderFiles} ${SourceFiles})
