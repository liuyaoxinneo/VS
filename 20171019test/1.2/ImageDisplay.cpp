#include <vtkSmartPointer.h>
#include <vtkImageViewer2.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkMetaImageReader.h>

//测试图像：../data/brain.mhd
int main(int argc, char* argv[])
{
	vtkSmartPointer<vtkMetaImageReader> reader =
		vtkSmartPointer<vtkMetaImageReader>::New();
	reader->SetFileName("../brain.mhd");
	reader->Update();

	vtkSmartPointer<vtkImageViewer2> imageViewer =
		vtkSmartPointer<vtkImageViewer2>::New();
	imageViewer->SetInputConnection(reader->GetOutputPort());

	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	imageViewer->SetupInteractor(renderWindowInteractor);

	imageViewer->SetColorLevel(500);//窗位--窗宽的中心位置
	imageViewer->SetColorWindow(2000);//窗宽--设置显示的最大灰度值和最小灰度值之间的跨度，显示时按比例转化到显示器能显示的256级灰度
	imageViewer->SetSlice(10);
	imageViewer->SetSliceOrientationToXY();
	imageViewer->Render();

	imageViewer->GetRenderer()->SetBackground(1.0, 1.0, 1.0);
	imageViewer->SetSize(640, 480);
	imageViewer->GetRenderWindow()->SetWindowName("DisplayImageExample");

	renderWindowInteractor->Start();

	return EXIT_SUCCESS;
}
