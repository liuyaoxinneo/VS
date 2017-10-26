#2017.10.26

##1. Attribute：给已知坐标点设置属性值
在20171024的setscalers源码基础上修改

###已实现：
1. **逐行读取 data1.txt 数据文件**
```
	int n = 0;
	FILE*fp;
	int buffer;
	fp = fopen("../data1.txt", "r");//以只读方式打开
	while (!feof(fp))
	{
		fscanf(fp, "%d", &input[n]);
		n++;
	}
	fclose(fp);
  ```
2. 赋属性值给已知坐标的点
3. 几何+拓扑结构(Vertxe)+属性信息(强度值) --> UnstructuredGrid
4. **自定义颜色--强度值的映射**
```
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
···
mapper->SetScalarRange(0,255);
mapper->SetLookupTable(lut);
···
```

---
##2. VolumeDataGenerate：生成体数据文件
参考类：vtkStructuredGridWruter / vtkUnstructuredGridWruter


##3. ##VolumeRendering：读取体数据文件实现RayCast方法的体绘制
