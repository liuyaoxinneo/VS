#2017.11.2

##0. C0501：用三维显示二维图像
* 用三维显示方法**AttributeSet**中的成像模式替代vtkImageActor的显示
* 已成功
---
原成像模块
```
vtkSmartPointer<vtkImageActor> redActor =
		vtkSmartPointer<vtkImageActor>::New();
	redActor->SetInput(img);

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
```
---
二维图像的三维显示方法

**来自20171026/AttributeSet**
```

//自定义颜色映射
	vtkSmartPointer<vtkLookupTable> lut =
		vtkSmartPointer<vtkLookupTable>::New();
	lut->SetNumberOfTableValues(10);
	lut->Build();
	lut->SetTableValue(0, 0, 0, 0, 1);
	lut->SetTableValue(1, 0.8900, 0.8100, 0.3400, 1);
  //SetTableValue(在表中的ID，R,G,B，不透明度)
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
	mapper->SetInputData(matrix);//grid--vtkUnstructuredGrid，matrix--vtkImageData
	mapper->SetScalarRange(0,255);
	mapper->SetLookupTable(lut);
	mapper->ScalarVisibilityOn();

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
![3D_0](images/2017/11/3d-0.png)
	return 0;
```
---

##1. 3Ddata：尝试定义vtkImageData类型的数据集来生成体数据文件
源码直接复制昨天的代码
* 定义vtkImageData部分：参考20171101/C0501
* 体绘制渲染：参考20171026/VolumeRendering

###已实现：
*

##跳过！直接进行体绘制！

##2. DataVolumeRender：直接读取数据文件体绘制
* 主体源码来自3Ddata
* 读取序列文件模块来自：20171016/
* 体绘制模块来自：20171026/VolumeRendering
* 数据文件来自：20171027/ImageMelt/DataTXT

###

体绘制部分做以下修改
```
cast->SetInputData(matrix);
···
···
volumeMapper->SetInputData(matrix);
···
···
```
**即，把所有的SetInputConnection()改为SetInputData**

###实现结果：
1. 实现了粗略的体绘制！缺陷边缘效果不佳（并未加入任何插值算法）

**改进措施**：界面信息需要插值处理
* 在Qt中做好插值后输出数据文件
* 加大a的值（目前为200）
2.

##3. QtIDWInsert：利用Qt对原始数据文件先进行处理，环境：Qt
* 插值、读文件源码来自：E:/Qt-sync/2D_offline_analysis_insert（修改的基础）
* 写文件源码来自：E:/Qt-sync/20170909_ 3D_data_export/test_debug
```
//下面输出已插值后的文件
QFile outfile(QString("inserted_data%1.txt")
              .arg(fileid)
              ,0);
if(!outfile.open(QIODevice::WriteOnly|QIODevice::Text))
    return;
QTextStream out(&outfile);

for(int x=0;x<ny;x++)
{
    for(int y=0;y<ny;y++)
    {
        out<<colorMap->data()->cell(x,y)<<" "<<"\n";
    }
}
outfile.close();
qDebug()<<QString("processed data%1.txt has been written!")
          .arg(fileid);
qDebug()<<"----------";
```

 即，输入VTK的是一个截面的所有点的正方形数据
* DataVolumeRender中的代码要做适当修改
* 参数：a=800,nx * ny=700 * 700；初始化：扇形区域内0，外300
* 输出文件顺序：从(0,0)开始，先固定x，让y从0->ny变化

###实现结果：
成功导出了处理后的490000个数据点！

但是单个文件数据量太大！还是读入的时候有问题，**没办法显示！**
