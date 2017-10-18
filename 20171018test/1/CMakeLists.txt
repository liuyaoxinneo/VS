CMAKE_MINIMUM_REQUIRED(VERSION 2.8.5 FATAL_ERROR)
if(POLICY CMP0025)
  cmake_policy(SET CMP0025 NEW) # CMake 3.0
endif()
if(POLICY CMP0053)
  cmake_policy(SET CMP0053 NEW) # CMake 3.1
endif()

PROJECT( Texture2DVolumeRenderingApp )

FIND_PACKAGE( VTK REQUIRED )
INCLUDE( ${VTK_USE_FILE} )

ADD_EXECUTABLE( Texture2DVolumeRenderingApp Texture2DVolumeRenderingApp.cpp)
TARGET_LINK_LIBRARIES( Texture2DVolumeRenderingApp ${VTK_LIBRARIES} )
