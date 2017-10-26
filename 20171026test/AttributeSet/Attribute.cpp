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

#include <fstream>
#include <iostream>


//定义全局变量
static double pi = vtkMath::Pi();
int a = 200;
double angle;
int length=18755;
int input[18755];

int main(int, char *[])
{
	//几何数据：创建点集数据的坐标点
	vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
	for (int p = 0; p < 31; p++)
	{
		angle = p + 30;
		for (int q = 0; q < 605; q++)
		{
			double xbuf = a*q*cos(angle*pi / 180)/604;
			double ybuf = a*q*sin(angle*pi / 180)/604;
			points->InsertNextPoint(ceil(xbuf), ceil(ybuf), 0);//每一次InsertNextPoint()之后，返回每个点在点集points中的ID,从0开始
		}
	}

	//拓扑数据：拓扑构型为点(vertex)
	vtkSmartPointer<vtkVertex> vertexs = vtkSmartPointer<vtkVertex>::New();
	vertexs->GetPointIds()->SetNumberOfIds(length);
	for (int n = 0; n < length; n++)
	{
		vertexs->GetPointIds()->SetId(n,n);//SetId(在vertexs中的ID(每个单元只需一个)，在points点集中的ID)
	}

	//属性数据：准备加入点数据的标量值
	//读入数据文件，实现强度赋值
	//以下，读入18755个点的强度值
	int n = 0;
	FILE*fp;
	int buffer;
	fp = fopen("../data1.txt", "r");//以只读方式打开
	while (!feof(fp))
	{	
		fscanf(fp, "%d", &input[n]);
		n++;
		//printf("%d ",input[n]);
	}
	fclose(fp);

	vtkSmartPointer<vtkDoubleArray> weights = vtkSmartPointer<vtkDoubleArray>::New();
	weights->SetNumberOfValues(length);
	for (int j = 0; j < length; j++)
	{
		weights->SetValue(j, input[j]);//setvalue(在points点集中的ID，该点的属性值)
	}

	//以上三部分数据组合成一个结构
	vtkSmartPointer<vtkUnstructuredGrid> grid = vtkSmartPointer<vtkUnstructuredGrid>::New();
	//grid->Allocate(1,1);
	grid->SetPoints(points);//设置对应的点集
	grid->GetPointData()->SetScalars(weights);//设置对应的属性值
	grid->InsertNextCell(vertexs->GetCellType(), vertexs->GetPointIds());//设置单元类型
	
	//以下为绘图部分
	//自定义颜色映射
	vtkSmartPointer<vtkLookupTable> lut =
		vtkSmartPointer<vtkLookupTable>::New();
	lut->SetNumberOfTableValues(10);
	lut->Build();
	lut->SetTableValue(0, 0, 0, 0, 1);
	lut->SetTableValue(1, 0.8900, 0.8100, 0.3400, 1);
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
	mapper->SetInputData(grid);
	mapper->SetScalarRange(0,255);
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

	//system("pause");

	return 0;
}