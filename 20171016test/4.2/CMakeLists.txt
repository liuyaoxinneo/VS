CMAKE_MINIMUM_REQUIRED(VERSION 2.8.5 FATAL_ERROR)
if(POLICY CMP0025)
  cmake_policy(SET CMP0025 NEW) # CMake 3.0
endif()
if(POLICY CMP0053)
  cmake_policy(SET CMP0053 NEW) # CMake 3.1
endif()

PROJECT( ReadSeriesImages1 )

FIND_PACKAGE( VTK REQUIRED )
INCLUDE( ${VTK_USE_FILE} )

ADD_EXECUTABLE( ReadSeriesImages1 ReadSeriesImages1.cpp)
TARGET_LINK_LIBRARIES( ReadSeriesImages1 ${VTK_LIBRARIES} )
