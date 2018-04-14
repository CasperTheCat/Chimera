cmake_minimum_required (VERSION 3.1)
set (CMAKE_CXX_STANDARD 17)

project (Chimera VERSION 0.0.1 DESCRIPTION "Project Chimera")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

set(Boost_USE_STATIC_LIBS TRUE)
#set(Boost_USE_MULTITHREADED TRUE)
#set(Boost_USE_STATIC_RUNTIME TRUE)

FIND_PACKAGE(Boost COMPONENTS system filesystem REQUIRED)

set(SourceFiles
./core/Source.cpp
./core/Process.cpp
)

set(HeaderFiles
./core/Process.h
./core/Util.h
)


INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIRS} )
add_executable(Chimera ${HeaderFiles} ${SourceFiles})
TARGET_LINK_LIBRARIES(Chimera ${Boost_LIBRARIES})
