#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPointData.h>
#include <vtkDoubleArray.h>
#include <vtkFloatArray.h>

int range = 10;

int main(int, char *[])
{
	//创建点集数据：包含两个坐标点。
	vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
	for (int i = 0; i < range; i++)
	{
		points->InsertNextPoint(i, i+1, 0);
	}

	//创建多边形数据。
	vtkSmartPointer<vtkPolyData> polydata = vtkSmartPointer<vtkPolyData>::New();
	polydata->SetPoints(points);

	//准备加入点数据的标量值，两个标量值分别为1和2。
	vtkSmartPointer<vtkDoubleArray> weights = vtkSmartPointer<vtkDoubleArray>::New();
	weights->SetNumberOfValues(5);
	for (int j = 0; j < range; j++)
	{
		weights->SetValue(j, j+1);//void SetValue(ID,属性值)
	}

	//先获取多边形数据的点数据指针，然后设置该点数据的标量属性值。
	polydata->GetPointData()->SetScalars(weights);

	//输出索引号为n的点的标量值。
	int n = 5;
	double weight = vtkDoubleArray::SafeDownCast(polydata->GetPointData()->GetScalars())->GetValue(n);
	std::cout << "double weight: " << weight << std::endl;

	system("pause");//加上一个“暂停”，防止运行窗口一闪而过

	return EXIT_SUCCESS;
}