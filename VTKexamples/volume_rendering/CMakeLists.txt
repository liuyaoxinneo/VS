cmake_minimum_required(VERSION 2.8.5 FATAL_ERROR)
if(POLICY CMP0025)
  cmake_policy(SET CMP0025 NEW) # CMake 3.0
endif()
if(POLICY CMP0053)
  cmake_policy(SET CMP0053 NEW) # CMake 3.1
endif()

PROJECT(VolumeRendering)

FIND_PACKAGE(VTK REQUIRED)
vtk_module_config(VTK
  vtkCommonCore
  vtkCommonDataModel
  vtkFiltersSources
  vtkFiltersGeometry
  vtkInteractionStyle
  vtkRendering${VTK_RENDERING_BACKEND}
)

INCLUDE(${VTK_USE_FILE})

ADD_EXECUTABLE(VolumeRenderingApp VolumeRenderingApp.cpp)

TARGET_LINK_LIBRARIES(VolumeRenderingApp ${VTK_LIBRARIES})
