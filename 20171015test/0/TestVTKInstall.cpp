
#include <vtkRenderWindow.h>
#include <vtkSmartPointer.h>

int main()
{
	vtkSmartPointer<vtkRenderWindow> renWin =
		vtkSmartPointer<vtkRenderWindow>::New();
	renWin->Render();

	renWin->SetWindowName("TestVTKInstall");
	renWin->SetSize(640, 480);
	renWin->Render();

	std::cin.get();
	return EXIT_SUCCESS;
}
