#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkInteractionStyle);
#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkStructuredPoints.h>
#include <vtkStructuredPointsReader.h>
#include <vtkVolumeRayCastCompositeFunction.h>//三种RayCast方法的头文件也要加上，否则无法使用
#include <vtkVolumeRayCastIsosurfaceFunction.h>
#include <vtkVolumeRayCastMIPFunction.h>
#include <vtkGPUVolumeRayCastMapper.h>
#include <vtkVolumeRayCastMapper.h>
#include <vtkColorTransferFunction.h>
#include <vtkPiecewiseFunction.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkVolumeProperty.h>
#include <vtkAxesActor.h>
#include <vtkImageShiftScale.h>
#include <vtkImageCast.h>
#include <vtkFixedPointVolumeRayCastMapper.h>
#include <vtkMetaImageReader.h>

//测试：../data/mummy.128.vtk
int main(int argc, char *argv[])
{
	vtkSmartPointer<vtkStructuredPointsReader> reader =
		vtkSmartPointer<vtkStructuredPointsReader>::New();
	reader->SetFileName("../mummy.128.vtk");
	reader->Update();
	//vtkSmartPointer<vtkMetaImageReader> reader =
	//	vtkSmartPointer<vtkMetaImageReader>::New();
	//reader->SetFileName("../data_volume/focus.mhd");
	//reader->Update();

	vtkSmartPointer<vtkImageCast> cast = vtkSmartPointer<vtkImageCast>::New();
	cast->SetInputConnection(reader->GetOutputPort());
	cast->SetOutputScalarTypeToUnsignedShort();
	cast->Update();
	
	//1：Alpha合成投影函数
	vtkSmartPointer<vtkVolumeRayCastCompositeFunction> rayCastFun =
		vtkSmartPointer<vtkVolumeRayCastCompositeFunction>::New();
	//2：最大密度投影函数
	//vtkSmartPointer<vtkVolumeRayCastMIPFunction> rayCastFun =
	//	vtkSmartPointer<vtkVolumeRayCastMIPFunction>::New();
	//3:等值面绘制函数
	//vtkSmartPointer<vtkVolumeRayCastIsosurfaceFunction> rayCastFun =
	//	vtkSmartPointer<vtkVolumeRayCastIsosurfaceFunction>::New();
	//rayCastFun->SetIsoValue(100);

	//1:非GPU加速
	/*vtkSmartPointer<vtkVolumeRayCastMapper> volumeMapper =
		vtkSmartPointer<vtkVolumeRayCastMapper>::New();
	volumeMapper->SetInputConnection(reader->GetOutputPort());
	volumeMapper->SetVolumeRayCastFunction(rayCastFun);*/
	//2：GPU加速的光线投影--不用设置SetVolumeRayCastFunction
	vtkSmartPointer<vtkGPUVolumeRayCastMapper> volumeMapper =
		vtkSmartPointer<vtkGPUVolumeRayCastMapper>::New();
	volumeMapper->SetInputConnection(reader->GetOutputPort());


	//设置光线采样距离--纵向采样距离
	volumeMapper->SetSampleDistance(0.5);//vtkVolumeRayCastMapper默认采样步长为1
	//设置图像采样步长--平面采样分辨率,每个像素对应多少条光线
	//volumeMapper->SetAutoAdjustSampleDistances(0);//默认为开启，方便缩放时的渲染时的缩放速度，若要设置图像采样距离则必须先关闭
	//volumeMapper->SetImageSampleDistance(0.5);//16个像素--1条光线

	vtkSmartPointer<vtkVolumeProperty> volumeProperty =
		vtkSmartPointer<vtkVolumeProperty>::New();
	volumeProperty->SetInterpolationTypeToLinear();
	volumeProperty->ShadeOn();  //打开或者关闭阴影测试，默认为关闭阴影效果
	volumeProperty->SetAmbient(0.4);//设置环境光系数
	volumeProperty->SetDiffuse(0.6);//散射光系数
	volumeProperty->SetSpecular(0.2);//反射光系数

	//opacity--不透明度
	vtkSmartPointer<vtkPiecewiseFunction> compositeOpacity =
		vtkSmartPointer<vtkPiecewiseFunction>::New();
	//1：直接通过添加断点来设置函数
	compositeOpacity->AddPoint(70, 0.00);
	compositeOpacity->AddPoint(90, 0.40);//AddPoint(x,y),x--自变量，灰度值，y--映射值，不透明度
	compositeOpacity->AddPoint(180, 0.60);//compositeOpacity为一个分段函数
	//2：直接添加一条线段，添加断点处的两个断点
	//compositeOpacity->AddSegment(120, 0.0, 180, 0.6);//(x1,y1,x2,y2)
	//compositeOpacity->AddSegment(180, 0.6, 255, 1);
	volumeProperty->SetScalarOpacity(compositeOpacity); //设置不透明度传输函数

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

	vtkSmartPointer<vtkColorTransferFunction> color =
		vtkSmartPointer<vtkColorTransferFunction>::New();
	color->AddRGBPoint(0.000, 0.00, 0.00, 0.00);
	color->AddRGBPoint(64.00, 1.00, 0.52, 0.30);
	color->AddRGBPoint(190.0, 1.00, 1.00, 1.00);
	color->AddRGBPoint(220.0, 0.20, 0.20, 0.20);
	volumeProperty->SetColor(color);//设置颜色传输函数

	vtkSmartPointer<vtkVolume> volume =
		vtkSmartPointer<vtkVolume>::New();
	volume->SetMapper(volumeMapper);
	volume->SetProperty(volumeProperty);

	vtkSmartPointer<vtkRenderer> ren = vtkSmartPointer<vtkRenderer>::New();
	ren->SetBackground(1.0, 1.0, 1.0);
	ren->AddVolume(volume);

	vtkSmartPointer<vtkRenderWindow> renWin = vtkSmartPointer<vtkRenderWindow>::New();
	renWin->AddRenderer(ren);
	renWin->SetSize(300, 300);
	renWin->Render();
	renWin->SetWindowName("VolumeRenderingApp");

	vtkSmartPointer<vtkRenderWindowInteractor> iren =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	iren->SetRenderWindow(renWin);
	ren->ResetCamera();

	renWin->Render();
	iren->Start();

	return EXIT_SUCCESS;
}