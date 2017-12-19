#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkInteractionStyle);
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkTriangle.h>
#include <vtkCellArray.h>
#include <vtkPointData.h>
#include <vtkPolyDataMapper.h>
#include <vtkDataSetMapper.h>
#include <vtkDoubleArray.h>
#include <vtkFloatArray.h>
#include <vtkLookupTable.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkVertex.h>
#include <vtkUnstructuredGrid.h>
#include <vtkUnstructuredGridWriter.h>

#include <vtkImageData.h>
#include <vtkUnsignedCharArray.h>
#include <vtkStringArray.h>

//体绘制需要的头文件
#include <vtkImageCast.h>
#include <vtkVolumeRayCastCompositeFunction.h>
#include <vtkVolumeRayCastMIPFunction.h>
#include <vtkVolumeRayCastIsosurfaceFunction.h>
#include <vtkGPUVolumeRayCastMapper.h>
#include <vtkVolumeProperty.h>
#include <vtkPiecewiseFunction.h>
#include <vtkColorTransferFunction.h>
#include <vtkVolumeRayCastMapper.h>
#include <vtkLODProp3D.h>

//输出数据文件需要的头文件
#include <vtkMetaImageWriter.h>
#include <vtkMetaImageReader.h>

#include <fstream>
#include <iostream>

int main(int, char *[])
{
	//以下尝试读.mhd+.zraw文件
	vtkSmartPointer<vtkMetaImageReader>reader = vtkSmartPointer<vtkMetaImageReader>::New();
	reader->SetFileName("../../Data/volume_data/scan.mhd");
	reader->Update();


	//以下为绘图部分
	//直接体绘制
	vtkSmartPointer<vtkImageCast> cast = vtkSmartPointer<vtkImageCast>::New();
	cast->SetInputConnection(reader->GetOutputPort());
	cast->SetOutputScalarTypeToUnsignedShort();
	cast->Update();

	//1：Alpha合成投影函数:默认为
	//vtkSmartPointer<vtkVolumeRayCastCompositeFunction> rayCastFun =
	//	vtkSmartPointer<vtkVolumeRayCastCompositeFunction>::New();
	//2：最大密度投影函数
	//vtkSmartPointer<vtkVolumeRayCastMIPFunction> rayCastFun =
	//	vtkSmartPointer<vtkVolumeRayCastMIPFunction>::New();
	//3:等值面绘制函数
	//vtkSmartPointer<vtkVolumeRayCastIsosurfaceFunction> rayCastFun =
	//	vtkSmartPointer<vtkVolumeRayCastIsosurfaceFunction>::New();
	//rayCastFun->SetIsoValue(100);

	//1:非GPU加速
	//vtkSmartPointer<vtkVolumeRayCastMapper> volumeMapper =
	//	vtkSmartPointer<vtkVolumeRayCastMapper>::New();
	//volumeMapper->SetInputConnection(reader->GetOutputPort());
	//volumeMapper->SetVolumeRayCastFunction(rayCastFun);

	//2：GPU加速的光线投影--不需要设置SetVolumeRayCastFunction，也不需要定义以上三种投影函数中的任何一种
	vtkSmartPointer<vtkGPUVolumeRayCastMapper> volumeMapper =
		vtkSmartPointer<vtkGPUVolumeRayCastMapper>::New();
	volumeMapper->SetInputConnection(reader->GetOutputPort());//设置输入图像数据

	//设置光线采样距离--纵向采样距离
	volumeMapper->SetSampleDistance(0.5);//vtkVolumeRayCastMapper默认采样步长为1,步长越短精度越高
	//设置图像采样步长--平面采样分辨率,设置每个像素对应多少条光线
	volumeMapper->SetAutoAdjustSampleDistances(0);//默认为开启，方便缩放时的渲染时的缩放速度，若要设置图像采样距离则必须先关闭
	volumeMapper->SetImageSampleDistance(0.5);//SetImageSampleDistance(x),(n=1/x^2)个像素--1条光线

	//设置属性
	//设置光照和阴影
	vtkSmartPointer<vtkVolumeProperty> volumeProperty =
		vtkSmartPointer<vtkVolumeProperty>::New();
	volumeProperty->SetInterpolationTypeToLinear();
	volumeProperty->ShadeOff();//在此缺陷显示中，关闭阴影图像更亮
	//volumeProperty->ShadeOn();  //打开或者关闭阴影测试，默认为关闭阴影效果
	//volumeProperty->SetAmbient(0.4);//设置环境光系数
	//volumeProperty->SetDiffuse(0.6);//散射光系数
	//volumeProperty->SetSpecular(0.2);//反射光系数

	//设置不透明度传输函数
	//compositeOpacity为一个分段函数
	vtkSmartPointer<vtkPiecewiseFunction> compositeOpacity =
		vtkSmartPointer<vtkPiecewiseFunction>::New();
	//1：直接通过添加断点来设置函数
	compositeOpacity->AddPoint(10, 0.00);
	compositeOpacity->AddPoint(70, 0.10);
	compositeOpacity->AddPoint(90, 0.40);//AddPoint(x,y),x--自变量，灰度值;y--映射值，不透明度;返回当前断点的ID（从0开始）
	compositeOpacity->AddPoint(180, 0.60);
	//2：直接添加一条线段，添加断点处的两个断点
	//compositeOpacity->AddSegment(120, 0.0, 180, 0.6);//(x1,y1,x2,y2)
	//compositeOpacity->AddSegment(180, 0.6, 255, 1);
	volumeProperty->SetScalarOpacity(compositeOpacity); 

	//测试隐藏部分数据,对比不同的设置
	//compositeOpacity->AddPoint(120,  0.00);
	//compositeOpacity->AddPoint(180,  0.60);
	//volumeProperty->SetScalarOpacity(compositeOpacity);

	vtkSmartPointer<vtkPiecewiseFunction> volumeGradientOpacity =
		vtkSmartPointer<vtkPiecewiseFunction>::New();
	volumeGradientOpacity->AddPoint(10, 0.0);
	volumeGradientOpacity->AddPoint(90, 0.5);
	volumeGradientOpacity->AddPoint(100, 1.0);
	//volumeProperty->SetGradientOpacity(volumeGradientOpacity);//设置梯度不透明度效果对比

	//设置颜色传输函数
	vtkSmartPointer<vtkColorTransferFunction> color =
		vtkSmartPointer<vtkColorTransferFunction>::New();
	//以下自定义颜色传输函数
	color->AddRGBPoint(0, 0, 0, 0);
	color->AddRGBPoint(76.5, 0, 0.10, 0.48);
	color->AddRGBPoint(102, 0.22, 0.56, 0.44);
	color->AddRGBPoint(127.5, 0.64, 0.8, 0.23);
	color->AddRGBPoint(153, 0.94, 0.82, 0.12);
	color->AddRGBPoint(178.5, 0.82, 0.49, 0.35);
	color->AddRGBPoint(204, 0.80, 0.45, 0.19);
	color->AddRGBPoint(229.5, 0.46, 0.29, 0.07);
	color->AddRGBPoint(255, 0.64,0.16, 0.07); //(标量值，R/255, G/255, B/255)
	volumeProperty->SetColor(color);

	vtkSmartPointer<vtkVolume> volume =
		vtkSmartPointer<vtkVolume>::New();
	volume->SetMapper(volumeMapper);
	volume->SetProperty(volumeProperty);

	//以下尝试利用vtkLODProp3D类来提高绘制速度
	//vtkSmartPointer<vtkLODProp3D> prop =
	//	vtkSmartPointer<vtkLODProp3D>::New();
	//prop->AddLOD(volumeMapper,volumeProperty,10.0);

	vtkSmartPointer<vtkRenderer> ren = vtkSmartPointer<vtkRenderer>::New();
	ren->SetBackground(1.0, 1.0, 1.0);
	ren->AddVolume(volume);
	//ren->AddVolume(prop);

	vtkSmartPointer<vtkRenderWindow> renWin = vtkSmartPointer<vtkRenderWindow>::New();
	renWin->AddRenderer(ren);
	renWin->SetSize(800, 800);
	renWin->Render();
	renWin->SetWindowName("DataDisplay");

	vtkSmartPointer<vtkRenderWindowInteractor> iren =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	iren->SetRenderWindow(renWin);
	ren->ResetCamera();

	renWin->Render();
	iren->Start();

    //system("pause");

	return EXIT_SUCCESS;
}