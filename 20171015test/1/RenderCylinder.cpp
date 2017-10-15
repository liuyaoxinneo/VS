#include <vtkSmartPointer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkCylinderSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkLight.h>
#include <vtkCamera.h>
//所要包含的头文件和一下所用到的类相关

int main()
{
	vtkSmartPointer<vtkCylinderSource> cylinder =
		vtkSmartPointer<vtkCylinderSource>::New();
	cylinder->SetHeight( 3.0 );
	cylinder->SetRadius( 1.0 );
	cylinder->SetResolution( 10 );//生成中心在渲染场原点的柱体

	vtkSmartPointer<vtkPolyDataMapper> cylinderMapper =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	cylinderMapper->SetInputConnection( cylinder->GetOutputPort() );

	vtkSmartPointer<vtkActor> cylinderActor =
		vtkSmartPointer<vtkActor>::New();
	cylinderActor->SetMapper( cylinderMapper );

	vtkSmartPointer<vtkRenderer> renderer =
		vtkSmartPointer<vtkRenderer>::New();
	renderer->AddActor( cylinderActor );
	renderer->SetBackground( 1.0, 1.0, 1.0 );//白色（1，1，1）

	vtkSmartPointer<vtkRenderWindow> renWin =
		vtkSmartPointer<vtkRenderWindow>::New();
	renWin->AddRenderer( renderer );
	renWin->SetSize( 640, 480 );
	renWin->Render();
	renWin->SetWindowName("RenderCylinder");

	vtkSmartPointer<vtkRenderWindowInteractor> iren =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	iren->SetRenderWindow(renWin);

	vtkSmartPointer<vtkInteractorStyleTrackballCamera> style =
		vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
	iren->SetInteractorStyle(style);

	vtkSmartPointer<vtkLight> myLight =
		vtkSmartPointer<vtkLight>::New();
	myLight->SetColor(0,1,0);
	myLight->SetPosition(0,0,1);
	myLight->SetFocalPoint(
		renderer->GetActiveCamera()->GetFocalPoint());
	renderer->AddLight(myLight);

	vtkSmartPointer<vtkLight> myLight2 =
		vtkSmartPointer<vtkLight>::New();
	myLight2->SetColor(0,0,1);
	myLight2->SetPosition(0,0,-1);
	myLight2->SetFocalPoint(
		renderer->GetActiveCamera()->GetFocalPoint());
	renderer->AddLight(myLight2);

	//camera的设置
	vtkSmartPointer<vtkCamera>mycamera =
		vtkSmartPointer<vtkCamera>::New();
	mycamera->SetClippingRange(0.0475, 2.3768);
	mycamera->SetFocalPoint(0.0572, -0.2134, -0.0523);
	mycamera->SetPosition(0.3245, -0.1139, -0.2932);
	mycamera->SetViewUp(-0.2234, 0.9983, 0.0345);
	renderer->SetActiveCamera(mycamera);

	iren->Initialize();
	iren->Start();

	return EXIT_SUCCESS;
}
