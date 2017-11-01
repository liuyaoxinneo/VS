#2017.11.1

##0. data：用于实验的.txt格式的数据文件
* 复制：20171027/ImageMlte 中的数据文件
* 编号：19data.txt--44data.txt


##1. 3Ddata：尝试定义vtkImageData类型的数据集来生成体数据文件
* 参考20171026/SeriseReading：读取序列文件
* 参考20171026/AttributeSet：读取.txt数据文件

在20171026的AttributeSet源码基础上修改

这里的数据用的是20171027 ImageMelt中的DataTXT

###已实现：
1.


##* 重新编译例子：20171019/1.1--书P79

书中的三行代码在编译时有问题-->**版本原因**
```
img->SetScalarTypeToUnsignedChar();
img->SetNumberOfScalarComponents(1);
img->AllocateScalars();
```
这三行代码换为
```
img->AllocateScalars(VTK_UNSIGNED_CHAR,1);
```
即可解决
