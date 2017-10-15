// VTK headers
#include "vtkVolume16Reader.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkMarchingCubes.h"
#include "vtkStripper.h"
#include "vtkActor.h"
#include "vtkPolyDataMapper.h"
#include "vtkProperty.h"
#include "vtkCamera.h"
//#include "vtkBoxWidget.h"

#include <iostream>

int main()
{
//读取二维切片数据序列
vtkVolume16Reader *reader = vtkVolume16Reader::New();
reader->SetDataDimensions(256, 256); //设置像素
reader->SetDataByteOrderToLittleEndian();
reader->SetFilePrefix("E:\\VS-sync\\volume data\\CThead");//设置读取路径
reader->SetImageRange(1, 113);
reader->SetDataSpacing(1, 1, 2);


//抽取等值面为骨头的信息
vtkMarchingCubes *boneExtractor = vtkMarchingCubes::New();
boneExtractor->SetInputConnection(reader->GetOutputPort());
boneExtractor->SetValue(0,500); //设置提取的等值信息

//剔除旧的或废除的数据单元，提高绘制速度
vtkStripper *boneStripper = vtkStripper::New(); //三角带连接
//注意：vtk6.0以后的版本，管道的连接函数修改为了SetInputConnection()和GetOutputPort().
boneStripper->SetInputConnection(boneExtractor->GetOutputPort());

//建立映射
vtkPolyDataMapper *boneMapper = vtkPolyDataMapper::New();
//注意：vtk6.0以后的版本，管道的连接函数修改为了SetInputConnection()和GetOutputPort().
boneMapper->SetInputConnection(boneStripper->GetOutputPort());

//建立角色
vtkActor *bone = vtkActor::New();
bone->SetMapper(boneMapper);

bone->GetProperty()->SetDiffuseColor(.1,.94,.52);
bone->GetProperty()->SetSpecular(.3);
bone->GetProperty()->SetSpecularPower(20);

//标准句子
//定义绘制器
vtkRenderer *aRenderer = vtkRenderer::New();
//定义绘制窗口
vtkRenderWindow *renWin = vtkRenderWindow::New();
renWin->AddRenderer(aRenderer);
//定义窗口交互器
vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
iren->SetRenderWindow(renWin);

//创建一个camera
vtkCamera *aCamera = vtkCamera::New();
aCamera->SetViewUp(0,0,-1);
aCamera->SetPosition(0,1,0);
aCamera->SetFocalPoint(0,0,0);

aRenderer->AddActor(bone);
aRenderer->SetActiveCamera(aCamera);
aRenderer->ResetCamera();
aCamera->Dolly(1.5);
aRenderer->SetBackground(0,0,0);
aRenderer->ResetCameraClippingRange();

/*
vtkBoxWidget *boxWidget = vtkBoxWidget::New();
boxWidget->SetInteractor(iren);
boxWidget->SetPlaceFactor(1.25);

boxWidget->SetProp3D(bone);
boxWidget->PlaceWidget();
*/

iren->Initialize();
iren->Start();
reader->Delete();
iren->Delete();
return 0;
}
