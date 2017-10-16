#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtk3DSImporter.h>
#include <vtkDataSet.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>

//测试文件：data/R8.3ds
int main(int argc, char *argv[])
{
	//if (argc != 2)
	//{
	//	std::cout << "Required arguments: Filename(*.3ds)" << std::endl;
	//	return EXIT_FAILURE;
	//}

	//std::string filename = argv[1];
	//std::cout << "Reading " << filename << std::endl;

	// 3DS Import
	vtkSmartPointer<vtk3DSImporter> importer = vtkSmartPointer<vtk3DSImporter>::New();
	importer->SetFileName("../R8.3ds");
	importer->ComputeNormalsOn();
	importer->Read();

	vtkSmartPointer<vtkRenderer> renderer = importer->GetRenderer();
	vtkSmartPointer<vtkRenderWindow> renderWindow = importer->GetRenderWindow();//从读取的实例中直接获得render和renderwindow
	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	renderWindowInteractor->SetRenderWindow(renderWindow);

	renderer->GradientBackgroundOn();
	renderer->SetBackground(1.0, 1.0, 1.0);
	renderer->SetBackground2(0.0, 0.0, 0.5);//两种颜色渐变的background,最多只能有两种颜色
	renderWindow->Render();
	renderWindow->SetSize(640, 480);
	renderWindow->SetWindowName("Import3DS");

	renderWindowInteractor->Start();

	return EXIT_SUCCESS;
}