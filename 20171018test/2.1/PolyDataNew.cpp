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

int main(int argc, char *argv[])
{
	vtkSmartPointer<vtkPoints> points =
		vtkSmartPointer<vtkPoints>::New();
	points->InsertNextPoint(0.0, 0.0, 0.0);
	points->InsertNextPoint(1.0, 0.0, 0.0);
	points->InsertNextPoint(1.0, 1.0, 0.0);
	points->InsertNextPoint(0.0, 1.0, 0.0);
	points->InsertNextPoint(2.0, 0.0, 0.0);//每次InsertNextPoint()之后，都返回这个点的索引i，默认索引从0开始，此时每个点已经有了一个索引
	//方法二：先规定总点数，再逐点赋坐标值


	vtkSmartPointer<vtkPolygon> polygon =
		vtkSmartPointer<vtkPolygon>::New();
	polygon->GetPointIds()->SetNumberOfIds(4);//设置索引--ID查找表中存储的点数
	polygon->GetPointIds()->SetId(0, 0);
	polygon->GetPointIds()->SetId(1, 1);
	polygon->GetPointIds()->SetId(2, 2);
	polygon->GetPointIds()->SetId(3, 3);

	vtkSmartPointer<vtkTriangle> trianle =
		vtkSmartPointer<vtkTriangle>::New();
	trianle->GetPointIds()->SetId(0, 1);
	trianle->GetPointIds()->SetId(1, 2);
	trianle->GetPointIds()->SetId(2, 4);

	vtkSmartPointer<vtkCellArray> cells =
		vtkSmartPointer<vtkCellArray>::New();
	cells->InsertNextCell(polygon);
	cells->InsertNextCell(trianle);//两个单元的面片

	vtkSmartPointer<vtkPolyData> polygonPolyData =
		vtkSmartPointer<vtkPolyData>::New();
	polygonPolyData->SetPoints(points);
	polygonPolyData->SetPolys(cells);

	vtkSmartPointer<vtkPolyDataMapper> mapper =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputData(polygonPolyData);

	vtkSmartPointer<vtkActor> actor =
		vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);

	vtkSmartPointer<vtkRenderer> renderer =
		vtkSmartPointer<vtkRenderer>::New();
	renderer->AddActor(actor);
	renderer->SetBackground(0.5, 0.5, 0.5);

	vtkSmartPointer<vtkRenderWindow> renderWindow =
		vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->AddRenderer(renderer);
	renderWindow->SetSize(640, 480);
	renderWindow->Render();
	renderWindow->SetWindowName("PolyDataNew");


	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	renderWindowInteractor->SetRenderWindow(renderWindow);

	renderWindow->Render();
	renderWindowInteractor->Start();

	return EXIT_SUCCESS;
}