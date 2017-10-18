#include <vtkSmartPointer.h>
#include <vtkPolygon.h>
#include <vtkTriangle.h>
#include <vtkCellArray.h>
#include <vtkPolyData.h>
#include <vtkPointData.h>
#include <vtkCellData.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkLookupTable.h>
#include <vtkTransformTextureCoords.h>
#include <iostream>

int main(int argc, char *argv[])
{
	vtkSmartPointer<vtkPoints> points =
		vtkSmartPointer<vtkPoints>::New();
	points->InsertNextPoint(0.0, 0.0, 0.0);
	points->InsertNextPoint(1.0, 0.0, 0.0);
	points->InsertNextPoint(1.0, 1.0, 0.0);
	points->InsertNextPoint(0.0, 1.0, 0.0);
	points->InsertNextPoint(2.0, 0.0, 0.0);

	vtkSmartPointer<vtkPolygon> polygon =
		vtkSmartPointer<vtkPolygon>::New();
	polygon->GetPointIds()->SetNumberOfIds(4);
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
	cells->InsertNextCell(trianle);

	vtkSmartPointer<vtkPolyData> polygonPolyData =
		vtkSmartPointer<vtkPolyData>::New();
	polygonPolyData->SetPoints(points);
	polygonPolyData->SetPolys(cells);

	unsigned char red[3] = { 255, 0, 0 };
	unsigned char green[3] = { 0, 255, 0 };
	unsigned char blue[3] = { 0, 0, 255 };

	//为points设置颜色数据，共有5个点
	vtkSmartPointer<vtkUnsignedCharArray> pointColors =
		vtkSmartPointer<vtkUnsignedCharArray>::New();
	pointColors->SetNumberOfComponents(3);//SetNumberOfComponents()设置每个tuple的维度，由于颜色由RGB三个分量组成，故设为3
	pointColors->InsertNextTupleValue(red);
	pointColors->InsertNextTupleValue(green);
	pointColors->InsertNextTupleValue(blue);
	pointColors->InsertNextTupleValue(green);
	pointColors->InsertNextTupleValue(red);
	polygonPolyData->GetPointData()->SetScalars(pointColors);
	//通过GetPointData获取点数据的指针，通过SetScalars来完成数值-->颜色的映射

	//为cells设置颜色数据，共有2个cell
	vtkSmartPointer<vtkUnsignedCharArray> cellColors =
		vtkSmartPointer<vtkUnsignedCharArray>::New();
	cellColors->SetNumberOfComponents(3);
	cellColors->InsertNextTupleValue(red);
	cellColors->InsertNextTupleValue(green);
	polygonPolyData->GetCellData()->SetScalars(cellColors);
	
	//同时设置了points和cells的颜色时，显示points的颜色

	vtkSmartPointer<vtkIntArray> pointfield =
		vtkSmartPointer<vtkIntArray>::New();
	pointfield->SetName("Field");
	pointfield->SetNumberOfComponents(3);
	pointfield->InsertNextTuple3(1, 0, 0);
	pointfield->InsertNextTuple3(2, 0, 0);
	pointfield->InsertNextTuple3(3, 0, 0);
	pointfield->InsertNextTuple3(4, 0, 0);
	pointfield->InsertNextTuple3(5, 0, 0);
	polygonPolyData->GetPointData()->AddArray(pointfield);

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

	vtkSmartPointer<vtkPolyDataMapper> mapper =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputData(polygonPolyData);
	//mapper->SetScalarModeToUseCellData();
	//mapper->SetScalarModeToUsePointFieldData();
	//mapper->ColorByArrayComponent("Field", 0);
	//mapper->SelectColorArray("Field");
	//mapper->SetScalarRange(1,5);
	mapper->SetLookupTable(lut);

	vtkSmartPointer<vtkActor> actor =
		vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);

	vtkSmartPointer<vtkRenderer> renderer =
		vtkSmartPointer<vtkRenderer>::New();
	renderer->AddActor(actor);
	renderer->SetBackground(1.0, 1.0, 1.0);

	vtkSmartPointer<vtkRenderWindow> renderWindow =
		vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->AddRenderer(renderer);
	renderWindow->SetSize(640, 480);
	renderWindow->Render();
	renderWindow->SetWindowName("PolyDataColor");

	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	renderWindowInteractor->SetRenderWindow(renderWindow);

	renderWindow->Render();
	renderWindowInteractor->Start();

	return EXIT_SUCCESS;
}