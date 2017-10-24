#2017.10.24

##(继续在2017.10.19中GeneratePoint修改)

##复制 20171016test\3 -->setscalars
可见：赋予坐标点属性按照以下顺序
* 创建坐标点
* 创建polydata
* 加入点数据的标量值
* 先获取多边形数据的点数据指针，然后设置该点数据的标量属性值。
	```
  polydata->GetPointData()->SetScalars(weights);
  ```

##已实现：
