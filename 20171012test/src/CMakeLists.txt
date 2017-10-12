CMAKE_MINIMUM_REQUIRED(VERSION 3.3 FATAL_ERROR)
 
PROJECT(Sphere)
 
FIND_PACKAGE(VTK REQUIRED)
INCLUDE(${VTK_USE_FILE})
 
ADD_EXECUTABLE(Sphere MACOSX_BUNDLE Sphere.cxx)
 
if(VTK_LIBRARIES)
  target_link_libraries(Sphere ${VTK_LIBRARIES})
else()
  target_link_libraries(Sphere vtkHybrid vtkWidgets)
endif()