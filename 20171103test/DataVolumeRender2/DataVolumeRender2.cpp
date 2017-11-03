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
#include <vtkGPUVolumeRayCastMapper.h>
#include <vtkVolumeProperty.h>
#include <vtkPiecewiseFunction.h>
#include <vtkColorTransferFunction.h>
#include <vtkVolumeRayCastMapper.h>

//输出数据文件需要的头文件
#include <vtkMetaImageWriter.h>


#include <fstream>
#include <iostream>


//定义全局变量
static double pi = vtkMath::Pi();
int a = 800;
int nx = 700, ny = 700;
double angle;
int length = 18755;
char name[128];

int begin = 19, end = 43;
int number = 25;
int input2[25][490000];

int input[25][18755];



int main(int, char *[])
{
	//属性数据：准备加入点数据的标量值
	//读入数据文件，实现强度赋值
	//以下，读入19--44这26个截面 18755个点的强度值，放入二维数组input[][]中
	int n = 0;
	FILE*fp;
	for (int i = begin; i < end+1; i++)
	{
		sprintf(name, "../../Data/data_ins_int/ins_int_data%d.txt", i);
		fp = fopen(name, "r");
		while (!feof(fp))
		{
			fscanf(fp, "%d", &input2[i-19][n]);
			n++;
		}
		fclose(fp);
		n = 0;
	}
	printf("upload done!");

	//定义vtkImageData类的数据
	vtkSmartPointer<vtkImageData> matrix = vtkSmartPointer<vtkImageData>::New();
	matrix->SetDimensions(nx, ny, number);//设定在x,y,z三个方向上的点数,坐标范围0~n-1
	matrix->SetSpacing(0.5, 0.5, 0.5);//设定三个方向上每个像素点之间的距离
	matrix->AllocateScalars(VTK_UNSIGNED_CHAR, 1);//分配内存，（数据类型，组分的数量）

	//初始化操作
	unsigned char *ptr = (unsigned char*)matrix->GetScalarPointer();//通过访问图像数组（一维）来设置像素值
	for (int i = 0; i<nx * ny * number; i++)
	{
		*ptr++ = 0;
	}

	int buf;
	int x, y;
	for (int n = 0; n < number; n++)
	{
		for (int xi = 0; xi < 700; xi++)
		{
			for (int yi = 0; yi < 700; yi++)
			{
				buf = input2[n][xi * 700 + yi];
				unsigned char *coor = (unsigned char*)matrix->GetScalarPointer(xi, yi, n);
				*coor = buf;
			}
		}
	}

	//以下尝试写文件
	vtkSmartPointer<vtkMetaImageWriter>writer = vtkSmartPointer<vtkMetaImageWriter>::New();
	writer->SetFileName("../../Data/data_volume/focus.mhd");
	writer->SetInputData(matrix);
	writer->Write();


	//以下为绘图部分
	//2：直接体绘制
	vtkSmartPointer<vtkImageCast> cast = vtkSmartPointer<vtkImageCast>::New();
	cast->SetInputData(matrix);
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

	//2：GPU加速的光线投影--不用设置SetVolumeRayCastFunction
	vtkSmartPointer<vtkGPUVolumeRayCastMapper> volumeMapper =
		vtkSmartPointer<vtkGPUVolumeRayCastMapper>::New();
	volumeMapper->SetInputData(matrix);


	//设置光线采样距离--纵向采样距离
	volumeMapper->SetSampleDistance(0.5);//vtkVolumeRayCastMapper默认采样步长为1
	//设置图像采样步长--平面采样分辨率,每个像素对应多少条光线
	//volumeMapper->SetAutoAdjustSampleDistances(0);//默认为开启，方便缩放时的渲染时的缩放速度，若要设置图像采样距离则必须先关闭
	volumeMapper->SetImageSampleDistance(0.5);//16个像素--1条光线

	vtkSmartPointer<vtkVolumeProperty> volumeProperty =
		vtkSmartPointer<vtkVolumeProperty>::New();
	volumeProperty->SetInterpolationTypeToLinear();
	volumeProperty->ShadeOn();  //打开或者关闭阴影测试，默认为关闭阴影效果
	volumeProperty->SetAmbient(0.4);//设置环境光系数
	volumeProperty->SetDiffuse(0.6);//散射光系数
	volumeProperty->SetSpecular(0.2);//反射光系数

	//设置不透明度传输函数
	//opacity--不透明度
	vtkSmartPointer<vtkPiecewiseFunction> compositeOpacity =
		vtkSmartPointer<vtkPiecewiseFunction>::New();
	//1：直接通过添加断点来设置函数
	compositeOpacity->AddPoint(10, 0.00);
	compositeOpacity->AddPoint(70, 0.10);
	compositeOpacity->AddPoint(90, 0.40);//AddPoint(x,y),x--自变量，灰度值，y--映射值，不透明度
	compositeOpacity->AddPoint(180, 0.60);//compositeOpacity为一个分段函数
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

	vtkSmartPointer<vtkRenderer> ren = vtkSmartPointer<vtkRenderer>::New();
	ren->SetBackground(1.0, 1.0, 1.0);
	ren->AddVolume(volume);

	vtkSmartPointer<vtkRenderWindow> renWin = vtkSmartPointer<vtkRenderWindow>::New();
	renWin->AddRenderer(ren);
	renWin->SetSize(600, 600);
	renWin->Render();
	renWin->SetWindowName("DataVolumeRendering");

	vtkSmartPointer<vtkRenderWindowInteractor> iren =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	iren->SetRenderWindow(renWin);
	ren->ResetCamera();

	renWin->Render();
	iren->Start();

    //system("pause");

	return 0;
}