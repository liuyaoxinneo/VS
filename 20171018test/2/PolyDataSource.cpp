#include <vtkConeSource.h>
#include <vtkArrowSource.h>
#include <vtkCubeSource.h>
#include <vtkCylinderSource.h>
#include <vtkDiskSource.h>
#include <vtkLineSource.h>
#include <vtkPlaneSource.h>
#include <vtkSphereSource.h>

#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <iostream>

int main(int argc, char *argv[])
{
	vtkSmartPointer<vtkConeSource> coneSource =
		vtkSmartPointer<vtkConeSource>::New();
	coneSource->Update();
	vtkSmartPointer<vtkArrowSource> arrow=
		vtkSmartPointer<vtkArrowSource>::New();

	vtkSmartPointer<vtkPolyData> cone = coneSource ->GetOutput();
	int nPoints = cone->GetNumberOfPoints();
	int nCells = cone->GetNumberOfCells();

	std::cout << "Points number:" << nPoints << std::endl;
	std::cout << "Cells  number:" << nCells << std::endl;

	vtkSmartPointer<vtkPolyDataMapper> mapper =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputData(cone);

	vtkSmartPointer<vtkActor> actor =
		vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);

	vtkSmartPointer<vtkRenderer> renderer =
		vtkSmartPointer<vtkRenderer>::New();
	renderer->AddActor(actor);
	renderer->SetBackground(0, 0, 0);

	vtkSmartPointer<vtkRenderWindow> renderWindow =
		vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->AddRenderer(renderer);
	renderWindow->SetSize(640, 480);
	renderWindow->Render();
	renderWindow->SetWindowName("PolyDataSource");

	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	renderWindowInteractor->SetRenderWindow(renderWindow);

	renderWindow->Render();
	renderWindowInteractor->Start();

	return EXIT_SUCCESS;
}