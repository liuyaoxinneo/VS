#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkInteractionStyle);
#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkStructuredPoints.h>
#include <vtkStructuredPointsReader.h>
#include <vtkVolumeRayCastCompositeFunction.h>//����RayCast������ͷ�ļ�ҲҪ���ϣ������޷�ʹ��
#include <vtkVolumeRayCastIsosurfaceFunction.h>
#include <vtkVolumeRayCastMIPFunction.h>
#include <vtkGPUVolumeRayCastMapper.h>
#include <vtkVolumeRayCastMapper.h>
#include <vtkColorTransferFunction.h>
#include <vtkPiecewiseFunction.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkVolumeProperty.h>
#include <vtkAxesActor.h>
#include <vtkImageShiftScale.h>
#include <vtkImageCast.h>
#include <vtkFixedPointVolumeRayCastMapper.h>
#include <vtkMetaImageReader.h>

//���ԣ�../data/mummy.128.vtk
int main(int argc, char *argv[])
{
	vtkSmartPointer<vtkStructuredPointsReader> reader =
		vtkSmartPointer<vtkStructuredPointsReader>::New();
	reader->SetFileName("../mummy.128.vtk");
	reader->Update();
	//vtkSmartPointer<vtkMetaImageReader> reader =
	//	vtkSmartPointer<vtkMetaImageReader>::New();
	//reader->SetFileName("../data_volume/focus.mhd");
	//reader->Update();

	vtkSmartPointer<vtkImageCast> cast = vtkSmartPointer<vtkImageCast>::New();
	cast->SetInputConnection(reader->GetOutputPort());
	cast->SetOutputScalarTypeToUnsignedShort();
	cast->Update();
	
	//1��Alpha�ϳ�ͶӰ����
	vtkSmartPointer<vtkVolumeRayCastCompositeFunction> rayCastFun =
		vtkSmartPointer<vtkVolumeRayCastCompositeFunction>::New();
	//2������ܶ�ͶӰ����
	//vtkSmartPointer<vtkVolumeRayCastMIPFunction> rayCastFun =
	//	vtkSmartPointer<vtkVolumeRayCastMIPFunction>::New();
	//3:��ֵ����ƺ���
	//vtkSmartPointer<vtkVolumeRayCastIsosurfaceFunction> rayCastFun =
	//	vtkSmartPointer<vtkVolumeRayCastIsosurfaceFunction>::New();
	//rayCastFun->SetIsoValue(100);

	//1:��GPU����
	/*vtkSmartPointer<vtkVolumeRayCastMapper> volumeMapper =
		vtkSmartPointer<vtkVolumeRayCastMapper>::New();
	volumeMapper->SetInputConnection(reader->GetOutputPort());
	volumeMapper->SetVolumeRayCastFunction(rayCastFun);*/
	//2��GPU���ٵĹ���ͶӰ--��������SetVolumeRayCastFunction
	vtkSmartPointer<vtkGPUVolumeRayCastMapper> volumeMapper =
		vtkSmartPointer<vtkGPUVolumeRayCastMapper>::New();
	volumeMapper->SetInputConnection(reader->GetOutputPort());


	//���ù��߲�������--�����������
	volumeMapper->SetSampleDistance(0.5);//vtkVolumeRayCastMapperĬ�ϲ�������Ϊ1
	//����ͼ���������--ƽ������ֱ���,ÿ�����ض�Ӧ����������
	//volumeMapper->SetAutoAdjustSampleDistances(0);//Ĭ��Ϊ��������������ʱ����Ⱦʱ�������ٶȣ���Ҫ����ͼ���������������ȹر�
	//volumeMapper->SetImageSampleDistance(0.5);//16������--1������

	vtkSmartPointer<vtkVolumeProperty> volumeProperty =
		vtkSmartPointer<vtkVolumeProperty>::New();
	volumeProperty->SetInterpolationTypeToLinear();
	volumeProperty->ShadeOn();  //�򿪻��߹ر���Ӱ���ԣ�Ĭ��Ϊ�ر���ӰЧ��
	volumeProperty->SetAmbient(0.4);//���û�����ϵ��
	volumeProperty->SetDiffuse(0.6);//ɢ���ϵ��
	volumeProperty->SetSpecular(0.2);//�����ϵ��

	//opacity--��͸����
	vtkSmartPointer<vtkPiecewiseFunction> compositeOpacity =
		vtkSmartPointer<vtkPiecewiseFunction>::New();
	//1��ֱ��ͨ����Ӷϵ������ú���
	compositeOpacity->AddPoint(70, 0.00);
	compositeOpacity->AddPoint(90, 0.40);//AddPoint(x,y),x--�Ա������Ҷ�ֵ��y--ӳ��ֵ����͸����
	compositeOpacity->AddPoint(180, 0.60);//compositeOpacityΪһ���ֶκ���
	//2��ֱ�����һ���߶Σ���Ӷϵ㴦�������ϵ�
	//compositeOpacity->AddSegment(120, 0.0, 180, 0.6);//(x1,y1,x2,y2)
	//compositeOpacity->AddSegment(180, 0.6, 255, 1);
	volumeProperty->SetScalarOpacity(compositeOpacity); //���ò�͸���ȴ��亯��

	//�������ز�������,�ԱȲ�ͬ������
	//compositeOpacity->AddPoint(120,  0.00);
	//compositeOpacity->AddPoint(180,  0.60);
	//volumeProperty->SetScalarOpacity(compositeOpacity);

	vtkSmartPointer<vtkPiecewiseFunction> volumeGradientOpacity =
		vtkSmartPointer<vtkPiecewiseFunction>::New();
	volumeGradientOpacity->AddPoint(10, 0.0);
	volumeGradientOpacity->AddPoint(90, 0.5);
	volumeGradientOpacity->AddPoint(100, 1.0);
	//volumeProperty->SetGradientOpacity(volumeGradientOpacity);//�����ݶȲ�͸����Ч���Ա�

	vtkSmartPointer<vtkColorTransferFunction> color =
		vtkSmartPointer<vtkColorTransferFunction>::New();
	color->AddRGBPoint(0.000, 0.00, 0.00, 0.00);
	color->AddRGBPoint(64.00, 1.00, 0.52, 0.30);
	color->AddRGBPoint(190.0, 1.00, 1.00, 1.00);
	color->AddRGBPoint(220.0, 0.20, 0.20, 0.20);
	volumeProperty->SetColor(color);//������ɫ���亯��

	vtkSmartPointer<vtkVolume> volume =
		vtkSmartPointer<vtkVolume>::New();
	volume->SetMapper(volumeMapper);
	volume->SetProperty(volumeProperty);

	vtkSmartPointer<vtkRenderer> ren = vtkSmartPointer<vtkRenderer>::New();
	ren->SetBackground(1.0, 1.0, 1.0);
	ren->AddVolume(volume);

	vtkSmartPointer<vtkRenderWindow> renWin = vtkSmartPointer<vtkRenderWindow>::New();
	renWin->AddRenderer(ren);
	renWin->SetSize(300, 300);
	renWin->Render();
	renWin->SetWindowName("VolumeRenderingApp");

	vtkSmartPointer<vtkRenderWindowInteractor> iren =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	iren->SetRenderWindow(renWin);
	ren->ResetCamera();

	renWin->Render();
	iren->Start();

	return EXIT_SUCCESS;
}