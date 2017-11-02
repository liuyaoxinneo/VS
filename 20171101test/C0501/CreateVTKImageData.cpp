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

#include <vtkLookupTable.h>
#include <vtkDataSetMapper.h>

int main()
{
	vtkSmartPointer<vtkImageData> img =  vtkSmartPointer<vtkImageData>::New();
	img->SetDimensions(16,16,1);
	img->AllocateScalars(VTK_UNSIGNED_CHAR,1);

	unsigned char *ptr = (unsigned char*)img->GetScalarPointer();
	for(int i=0; i<16*16*1; i++)
	{
		*ptr ++ =i%256; 
	}

	//以下为绘图部分
	//自定义颜色映射
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

	vtkSmartPointer<vtkDataSetMapper> mapper =
		vtkSmartPointer<vtkDataSetMapper>::New();
	mapper->SetInputData(img);
	mapper->SetScalarRange(0, 255);
	mapper->SetLookupTable(lut);
	mapper->ScalarVisibilityOn();

	//致命错误出现在一下三行中的actor
	vtkSmartPointer<vtkActor> actor =
		vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);


	vtkSmartPointer<vtkRenderer> renderer =
		vtkSmartPointer<vtkRenderer>::New();
	renderer->AddActor(actor);
	renderer->SetBackground(1, 1, 1);

	vtkSmartPointer<vtkRenderWindow> renderWindow =
		vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->AddRenderer(renderer);
	renderWindow->SetSize(640, 480);
	renderWindow->Render();
	renderWindow->SetWindowName("Attribute");

	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	renderWindowInteractor->SetRenderWindow(renderWindow);

	renderWindow->Render();
	renderWindowInteractor->Start();

	//system("pause");

	return 0;
}
