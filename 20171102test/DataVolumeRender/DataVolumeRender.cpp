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
int number = end - begin + 1;
int input[26][18755];

int main(int, char *[])
{
	//属性数据：准备加入点数据的标量值
	//读入数据文件，实现强度赋值
	//以下，读入19、20、21、22、23这5个截面 18755个点的强度值，放入二维数组input[][]中
	int n = 0;
	FILE*fp;
	for (int i = begin ; i < end+1 ; i++)
	{
		//sprintf(name,"../../data_inserted/inserted_data%d.txt",i);
		sprintf(name, "../../data/data%d.txt", i);
		fp = fopen(name, "r");//以只读方式打开
		while (!feof(fp))
		{
			fscanf(fp, "%d", &input[i-19][n]);
			//printf("%d ", input[i-19][n]);
			n++;
		}
		fclose(fp);
		n = 0;
	}


	//定义vtkImageData类的数据
	vtkSmartPointer<vtkImageData> matrix = vtkSmartPointer<vtkImageData>::New();
	matrix->SetDimensions(nx, ny, 26);//设定在x,y,z三个方向上的点数,坐标范围0~n-1
	matrix->SetSpacing(0.5, 0.5, 0.5);//设定三个方向上每个像素点之间的距离
	matrix->AllocateScalars(VTK_UNSIGNED_CHAR, 1);

	unsigned char *ptr = (unsigned char*)matrix->GetScalarPointer();//通过访问图像数组（一维）来设置像素值
	for (int i = 0; i<nx * ny * 26; i++)
	{
		*ptr++ = 0;
	}//初始化操作

	int xindex, yindex;
	unsigned char buf;
	for (int n = 0; n < 26; n++)
	{
		for (int p = 0; p < 31; p++)
		{
			angle = p + 30;
			for (int q = 0; q < 605; q++)
			{
				buf = input[n][605 * p + q];
				xindex = ceil(a*q*cos(angle*pi / 180) / 604);
				yindex = ceil(a*q*sin(angle*pi / 180) / 604);
				unsigned char *coor = (unsigned char*)matrix->GetScalarPointer(xindex, yindex, n);
				*coor = buf;
			}
		}
	}

	//double buf;
	//for (int n = 0; n < number; n++)
	//{
	//	for (int xi = 0; xi < nx; nx++)
	//	{
	//		for (int yi = 0; yi < ny; ny++)
	//		{
	//			buf = input[n][xi*nx+yi];
	//			unsigned char *coor = (unsigned char*)matrix->GetScalarPointer(xi, yi, n);
	//			*coor = buf;
	//		}
	//	}
	//}
	//以下为绘图部分
	/*
	1：图像堆叠的三维：面绘制
	自定义颜色映射
	vtkSmartPointer<vtkLookupTable> lut =
		vtkSmartPointer<vtkLookupTable>::New();
	lut->SetNumberOfTableValues(10);
	lut->Build();
	lut->SetTableValue(0, 0, 0, 0, 1);
	lut->SetTableValue(1, 0.8900, 0.8100, 0.3400, 1);//SetTableValue(在表中的ID，R,G,B，不透明度)
	lut->SetTableValue(2, 1.0000, 0.3882, 0.2784, 1);
	lut->SetTableValue(3, 0.9608, 0.8706, 0.7020, 1);
	lut->SetTableValue(4, 0.9020, 0.9020, 0.9804, 1);
	lut->SetTableValue(5, 1.0000, 0.4900, 0.2500, 1);
	lut->SetTableValue(6, 0.5300, 0.1500, 0.3400, 1);
	lut->SetTableValue(7, 0.9804, 0.5020, 0.4471, 1);
	lut->SetTableValue(8, 0.7400, 0.9900, 0.7900, 1);
	lut->SetTableValue(9, 0.2000, 0.6300, 0.7900, 1);

	vtkSmartPointer<vtkDataSetMapper> mapper =
		vtkSmartPointer<vtkDataSetMapper>::New();
	mapper->SetInputData(matrix);//grid--vtkUnstructuredGrid，matrix--vtkImageData
	mapper->SetScalarRange(0, 255);
	mapper->SetLookupTable(lut);
	mapper->ScalarVisibilityOn();

	vtkSmartPointer<vtkActor> actor =
		vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);


	vtkSmartPointer<vtkRenderer> renderer =
		vtkSmartPointer<vtkRenderer>::New();
	renderer->AddActor(actor);
	renderer->SetBackground(1, 1, 1);

	vtkSmartPointer<vtkRenderWindow> renderWindow =
		vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->AddRenderer(renderer);
	renderWindow->SetSize(640, 480);
	renderWindow->Render();
	renderWindow->SetWindowName("Attribute");

	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	renderWindowInteractor->SetRenderWindow(renderWindow);

	renderWindow->Render();
	renderWindowInteractor->Start();

	system("pause");
	*/

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
	renWin->SetSize(600, 600);
	renWin->Render();
	renWin->SetWindowName("DataVolumeRendering");

	vtkSmartPointer<vtkRenderWindowInteractor> iren =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	iren->SetRenderWindow(renWin);
	ren->ResetCamera();

	renWin->Render();
	iren->Start();


	return 0;
}