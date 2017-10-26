#include <vtkSmartPointer.h>
#include <vtkJPEGReader.h>
#include <vtkImageViewer2.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderer.h>
#include <vtkStringArray.h>
#include <vtkRenderWindow.h>


int main()
{
	//生成图像序列的文件名数组
	vtkSmartPointer< vtkStringArray > fileArray = vtkSmartPointer< vtkStringArray >::New();
	char fileName[128];
	for (int i = 1; i < 100; i++)
	{
		sprintf(fileName, "../data/Head/head%03d.jpg", i);
		vtkStdString::StdString filestr(fileName);
		fileArray->InsertNextValue(filestr);
	}

	//读取JPG序列图像
	vtkSmartPointer<vtkJPEGReader> reader = vtkSmartPointer<vtkJPEGReader>::New();
	reader->SetFileNames(fileArray);

	//vtkSmartPointer<vtkJPEGReader>reader =
	//	vtkSmartPointer<vtkJPEGReader>::New();
	//reader->SetFilePrefix("../Head/head");//设置文件名相同的部分
	//reader->SetFilePattern("%s%03d.jpg");
	//reader->SetDataExtent(0, 255, 0, 255, 1, 100);
	//reader->Update();

	vtkSmartPointer<vtkInteractorStyleImage> style = vtkSmartPointer<vtkInteractorStyleImage>::New();

	//显示读取的JPG图像
	vtkSmartPointer<vtkImageViewer2> imageViewer = vtkSmartPointer<vtkImageViewer2>::New();
	imageViewer->SetInputConnection(reader->GetOutputPort());

	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	renderWindowInteractor->SetInteractorStyle(style);

	imageViewer->SetSlice(50); //默认显示第50个切片(即第50层)
	imageViewer->SetSliceOrientationToXY();
	//imageViewer->SetSliceOrientationToYZ();
	//imageViewer->SetSliceOrientationToXZ();
	imageViewer->SetupInteractor(renderWindowInteractor);
	imageViewer->Render();

	imageViewer->GetRenderer()->SetBackground(1.0, 1.0, 1.0);
	imageViewer->SetSize(640, 480);
	imageViewer->GetRenderWindow()->SetWindowName("ReadSeriesImages1");

	renderWindowInteractor->Start();

	return EXIT_SUCCESS;
}