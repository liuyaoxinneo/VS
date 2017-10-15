/*=========================================================================

  Program:   Visualization Toolkit
  Module:    Cube.cxx

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// This example shows how to manually create vtkPolyData.

#include "vtkActor.h"
#include "vtkCamera.h"
#include "vtkCellArray.h"
#include "vtkFloatArray.h"
#include "vtkPointData.h"
#include "vtkPoints.h"
#include "vtkPolyData.h"
#include "vtkPolyDataMapper.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkRenderer.h"
#include "vtkInteractorStyleTrackballCamera.h"

int main()
{
  int i;
  static float x[8][3]={{0,0,0}, {1,0,0}, {1,1,0}, {0,1,0},
                        {0,0,1}, {1,0,1}, {1,1,1}, {0,1,1}};//正方体八个点的坐标
  static vtkIdType pts[6][4]={{0,1,2,3}, {4,5,6,7}, {0,1,5,4},
                        {1,2,6,5}, {2,3,7,6}, {3,0,4,7}};//{0，1，2，3}表示上面定义的第1、2、3、4个点组成一个平面

  // We'll create the building blocks of polydata including data attributes属性.
  vtkPolyData *cube = vtkPolyData::New();
  vtkPoints *points = vtkPoints::New();
  vtkCellArray *polys = vtkCellArray::New();
  vtkFloatArray *scalars = vtkFloatArray::New();//属性数据

  // Load the point, cell, and data attributes.
  for (i=0; i<8; i++) points->InsertPoint(i,x[i]);//将定义好的点放入points,i是每个点真正的索引
  for (i=0; i<6; i++) polys->InsertNextCell(4,pts[i]);
  //插入点的拓扑结构，InsertNextCell(n，m[]),n--表示每个cell(面)的多边形类型
  for (i=0; i<8; i++) scalars->InsertTuple1(i,i);//vtkFloatArray*scloars:设定每个顶点的标量值,各标量值对应的颜色由下面的cubemapper查找

  // We now assign the pieces to the vtkPolyData.
  cube->SetPoints(points);
  points->Delete();
  cube->SetPolys(polys);
  polys->Delete();
  cube->GetPointData()->SetScalars(scalars);
  scalars->Delete();

  // Now we'll look at it.
  vtkPolyDataMapper *cubeMapper = vtkPolyDataMapper::New();
      cubeMapper->SetInputData(cube);
      cubeMapper->SetScalarRange(0,7);//红（最小）--蓝（最大）

  vtkActor *cubeActor = vtkActor::New();
      cubeActor->SetMapper(cubeMapper);

  // The usual rendering stuff.
  vtkCamera *camera = vtkCamera::New();
      camera->SetPosition(1,1,1);//设置镜头位置
      camera->SetFocalPoint(0,0,0);//设置焦点位置

  vtkRenderer *renderer = vtkRenderer::New();
  vtkRenderWindow *renWin = vtkRenderWindow::New();
    renWin->AddRenderer(renderer);

  vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
    iren->SetRenderWindow(renWin);

vtkInteractorStyleTrackballCamera *style = vtkInteractorStyleTrackballCamera::New();
	iren->SetInteractorStyle(style);

  renderer->AddActor(cubeActor);
      renderer->SetActiveCamera(camera);
      renderer->ResetCamera();
      renderer->SetBackground(1,1,1);

  renWin->SetSize(300,300);

  // interact with data
  renWin->Render();
  iren->Start();

  // Clean up

  cube->Delete();
  cubeMapper->Delete();
  cubeActor->Delete();
  camera->Delete();
  renderer->Delete();
  renWin->Delete();
  iren->Delete();

  return 0;
}
