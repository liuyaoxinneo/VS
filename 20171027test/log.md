#2017.10.17

##1. SeriesVolumeCast：读取序列图像文件生成的数据体进行cast ray方法重建的可行性
* 在20171026/SeriesReading 的源码(读取序列图像文件)
* 20171017/1 的源码(体绘制管线)

###已实现：
可以作为体数据投入，但是效果很差

---
##2. FatalErrorFix：修复昨日晚上的致命错误
[网上找到的修复方案](http://blog.csdn.net/wokaowokaowokao12345/article/details/51096887)

在cpp文件开头加上以下三行即可
```
#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkInteractionStyle);
```

---
##3.ImageMelt：改变聚焦深度，单个截面混合实现最佳的单截面显示效果
