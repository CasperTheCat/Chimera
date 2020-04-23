cmake_minimum_required (VERSION 3.1)
set (CMAKE_CXX_STANDARD 17)

project (Chimera VERSION 0.0.1 DESCRIPTION "Project Chimera")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

# Windows
IF (WIN32)
  set(dxtex  ${CMAKE_SOURCE_DIR}/extern/DirectXTex)
  set(dxtexl  DirectXTex)
  add_subdirectory(${CMAKE_SOURCE_DIR}/extern/DirectXTex)
ELSE()
  set(dxtex "")
  set(dxtexl  "")
ENDIF()


set(SourceFiles
./core/Source.cpp
./core/Process.cpp
./core/ImageProcessing/Image.cpp
./core/ImageProcessing/ImageConverters.cpp
#./core/DX/DirectXRender.cpp
)

set(HeaderFiles
./core/Process.h
./core/Util.h
./core/Format.h
./core/ImageProcessing/Image.h
./core/ImageProcessing/ImageConverters.h
#./core/DX/DirectXRender.h
)


include_directories(
    ${CMAKE_SOURCE_DIR}/extern/glm
    ${dxtex}
)

add_subdirectory(${CMAKE_SOURCE_DIR}/extern/glm)

add_executable(Chimera ${HeaderFiles} ${SourceFiles})
TARGET_LINK_LIBRARIES(Chimera 
    glm
    ${dxtexl}
)
