#include <vtkSmartPointer.h>
#include <vtkImageReader2Factory.h>
#include <vtkImageReader2.h>
#include <vtkImageViewer2.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>

//测试文件：data/VTK-logo
int main(int argc, char *argv[])
{
	//读取图像
	vtkSmartPointer<vtkImageReader2Factory> readerFactory =
		vtkSmartPointer<vtkImageReader2Factory>::New();
	vtkImageReader2 * reader = readerFactory->CreateImageReader2("../VTK-logo");
	reader->SetFileName("../VTK-logo");
	reader->Update();

	//显示读取的图像
	vtkSmartPointer<vtkImageViewer2> imageViewer = vtkSmartPointer<vtkImageViewer2>::New();
	imageViewer->SetInputConnection(reader->GetOutputPort());
	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	imageViewer->SetupInteractor(renderWindowInteractor);
	imageViewer->Render();
	imageViewer->GetRenderer()->ResetCamera();
	imageViewer->Render();

	imageViewer->SetSize(640, 480);
	imageViewer->GetRenderWindow()->SetWindowName("ReadUnknowFormatImage");

	renderWindowInteractor->Start();

	return EXIT_SUCCESS;
}