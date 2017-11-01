#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkInteractionStyle);

#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkImageActor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderWindow.h>

int main()
{
	vtkSmartPointer<vtkImageData> img =  vtkSmartPointer<vtkImageData>::New();
	img->SetDimensions(16,16,1);
	//img->SetScalarType(1);
	//img->SetNumberOfScalarComponents(1);
	img->AllocateScalars(VTK_UNSIGNED_CHAR,1);

	unsigned char *ptr = (unsigned char*)img->GetScalarPointer();
	for(int i=0; i<16*16*1; i++)
	{
		*ptr ++ =i%256; 
	}

	vtkSmartPointer<vtkImageActor> redActor =
		vtkSmartPointer<vtkImageActor>::New();
	redActor->SetInputData(img);

	double redViewport[4] = {0.0, 0.0, 1.0, 1.0};

	vtkSmartPointer<vtkRenderer> redRenderer =
		vtkSmartPointer<vtkRenderer>::New();
	redRenderer->SetViewport(redViewport);
	redRenderer->AddActor(redActor);
	redRenderer->ResetCamera();
	redRenderer->SetBackground(1.0, 1.0, 1.0);

	vtkSmartPointer<vtkRenderWindow> renderWindow =
		vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->AddRenderer(redRenderer);
	renderWindow->SetSize( 640, 480 );
	renderWindow->Render();
	renderWindow->SetWindowName("CreateVTKImageData");

	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	vtkSmartPointer<vtkInteractorStyleImage> style =
		vtkSmartPointer<vtkInteractorStyleImage>::New();
	renderWindowInteractor->SetInteractorStyle(style);

	renderWindowInteractor->SetRenderWindow(renderWindow);
	renderWindowInteractor->Initialize();
	renderWindowInteractor->Start();

	return EXIT_SUCCESS;
}
