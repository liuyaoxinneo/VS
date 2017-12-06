#2017.11.9

##0. Src：复制20171107test/Src
##1. Plugin：在Qt窗口中添加QVTKwidget的尝试
* 参考20171106：添加qcustomplot类

###问题与解决：
* 添加QVTKWidget后出现错误 **无法打开包括文件: “QVTKWidget.h”**
   * 发现此文件的路径在``C:\VTK\VTK-7.1.1\GUISupport\Qt``，将此文件夹包含到附加包含目录（参考20171107test），但并未解决，出现更多的文件无法打开的情况
