#include <vtkSmartPointer.h>
#include <vtkBMPReader.h>
#include <vtkImageData.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkImageViewer2.h>
#include <vtkRenderWindow.h>
#include <vtkStructuredPointsReader.h>

//测试文件：data/VTK-logo.bmp
int main(int argc, char* argv[])
{
	//if (argc < 2)
	//{
	//	std::cout << argv[0] << " " << "BMP-File(*.bmp)" << std::endl;
	//	return EXIT_FAILURE;
	//}
	//设置文件名直接以“../xxx.bmp”的形式读取

	vtkSmartPointer<vtkBMPReader> reader = vtkSmartPointer<vtkBMPReader>::New();
	std::cout << "Modification Time of reader (After New()): " << reader->GetMTime() << std::endl;
	reader->SetFileName("../VTK-logo.bmp");
	std::cout << "Modification Time of reader (After SetFileName()): " << reader->GetMTime() << std::endl;

	vtkImageData* imageData = reader->GetOutput();
	std::cout << "Modification Time of reader (After GetOutput()): " << reader->GetMTime() << std::endl;
	reader->Update();
	std::cout << "Modification Time of reader (After Update()): " << reader->GetMTime() << std::endl;

	int extent[6];
	imageData->GetExtent(extent);
  
	std::cout << "Extent of image: " << extent[0] << " "
		<< extent[1] << " " << extent[2] << " " << extent[3] << " "
		<< extent[4] << " " << extent[5] << " " << std::endl;

	vtkSmartPointer<vtkImageViewer2> viewer =
		vtkSmartPointer<vtkImageViewer2>::New();
	vtkSmartPointer<vtkRenderWindowInteractor> interactor =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	viewer->SetupInteractor(interactor);
	viewer->SetInputData(imageData);
	//viewer->SetInput(imageData);
	viewer->Render();

	viewer->SetSize(640, 480);
	viewer->GetRenderWindow()->SetWindowName("vtkPipelineExecute");

	interactor->Initialize();
	interactor->Start();

	return EXIT_SUCCESS;
}
