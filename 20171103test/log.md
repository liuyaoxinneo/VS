#2017.11.3

##1.DataVolumeRender2：接着昨天的DataVolumeRender继续
* 源码复制：20171102test/DataVolumeRender
* 数据文件来自：20171102test/QtIDWInsert：ori（18755）/ ins2(490000，背景为0) / ins_int(490000取整输出)

###目标：
1. 读取单个490000点截面并显示
2. 读取多个截面体绘制
3. 或者直接在VS内进行插值

###已完成：
1. 读取25个IDW插值后的数据文件并绘图，此处的文件是**ins_int_data.txt**
2. 自定义颜色映射函数，参考了Qt的自定义颜色映射
3. **运用vtkMetaImageWriter类导出了体数据文件：focus.mhd & focus.zraw**
```
//以下尝试写文件
vtkSmartPointer<vtkMetaImageWriter>writer =
 vtkSmartPointer<vtkMetaImageWriter>::New();
writer->SetFileName("../../Data/data_volume/focus.mhd");
writer->SetInputData(matrix);
writer->Write();
```
