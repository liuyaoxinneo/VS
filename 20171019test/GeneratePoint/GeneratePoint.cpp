//源码复制：20171018/2.1/PolyDataNew

#include <vtkSmartPointer.h>
#include <vtkPolygon.h>
#include <vtkTriangle.h>
#include <vtkCellArray.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkProperty.h>

#include <iostream>

#include <vtkMath.h>
#include <vtkVertexGlyphFilter.h>
#include <vtkDataReader.h>
#include <sstream>
#include <vtkUnsignedCharArray.h>

static double pi = vtkMath::Pi();
int a = 10;
int ny = 200;
double angle;
unsigned char input[18755];


int main(int argc, char *argv[])
{

	//std::cout << "sin()= " << sin(pi/4) << std::endl;

	//生成点集--插入点的坐标
	vtkSmartPointer<vtkPoints> points =
		vtkSmartPointer<vtkPoints>::New();
	for (int j = 0; j < 31; j++)
	{
		angle = j + 30;
		for (int i = 0; i < 605; i++)
		{
			double xbuf = i*a*cos(angle*pi / 180) / 604;
			double ybuf = i*a*sin(angle*pi / 180) / 604;
			points->InsertNextPoint(ybuf,ny-1-xbuf, 0);//每一次InsertNextPoint()之后，返回每个点的ID,从0开始
		}
	}
	//至此，生成18755个有坐标的点集

	//生成多边形数据，将坐标点
	vtkSmartPointer<vtkPolyData> polydata =
		vtkSmartPointer<vtkPolyData>::New();
	polydata->SetPoints(points);

	//以下，读入18755个点的强度值
	FILE*fp;
	fp = fopen("../data1.txt","r");//以只读方式打开
	for (int m = 0; !feof(fp); m++)
	{
		fscanf(fp,"%d",&input[m]);
	}
	fclose(fp);

	//以下，将18755个点的强度值给坐标点
	vtkSmartPointer<vtkUnsignedCharArray>weight = vtkSmartPointer<vtkUnsignedCharArray>::New();
	weight->SetNumberOfValues(18755);
	for (int i = 0; i < 18755; i++)
	{
		weight->SetValue(i, input[i]);
	}	

	//vertex的功能是将每个cell都变为vertex的样式
	vtkSmartPointer<vtkVertexGlyphFilter> glyphFilter = vtkSmartPointer<vtkVertexGlyphFilter>::New();
	glyphFilter->SetInputData(polydata);
	glyphFilter->Update();


	//---以下为渲染管道部分---
	vtkSmartPointer<vtkPolyDataMapper> mapper =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputConnection(glyphFilter->GetOutputPort());

	vtkSmartPointer<vtkActor> actor =
		vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);
	actor->GetProperty()->SetPointSize(1);
	actor->GetProperty()->SetColor(0, 0, 0);//设置显示时散点的大小和颜色

	vtkSmartPointer<vtkRenderer> renderer =
		vtkSmartPointer<vtkRenderer>::New();
	renderer->AddActor(actor);
	renderer->SetBackground(1, 1, 1);

	//渲染窗口设置部分
	vtkSmartPointer<vtkRenderWindow> renderWindow =
		vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->AddRenderer(renderer);
	renderWindow->SetSize(640, 480);
	renderWindow->Render();
	renderWindow->SetWindowName("PointsGenerate");


	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	renderWindowInteractor->SetRenderWindow(renderWindow);

	renderWindow->Render();
	renderWindowInteractor->Start();

	return EXIT_SUCCESS;
}
