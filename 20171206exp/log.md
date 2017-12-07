#2017.12.6
##0. Src：复制20171123整合的Src文件

##1. DataExport：迁移Qt中的3D_data_export_1_0至VS内的Qt工程中
* 源目录E:/Qt/3D_data_export_1_0/test_debug
* 只需接入doppler_net库即可
* 步骤参考20171107test
* 功能：只能

##问题与解决：
* 如何改变生成文件的路径？

由**FilePrefix**可知，将输出文件名前加路径即可，路径的起点为.cpp文件所在的位置
```
QFile file("../../Data/out5.txt");
```

* 此程序输出的为18755个点的数据，能否整合插值？输出700*700点的数据文件？

##2. FilePrefix：改变VS内Qt程序的输出数据文件的路径（临时）
* 只需包含默认库

##3. Display：读取数据文件的显示，用以判断程序的插值是否起作用（临时）

##4. DataProcessing：Qt环境中对18755点的插值（临时）
* 直接复制20171102/QtIDWInsert
* ori_data_1：直接以编码器的步进作为长度单位，123个文件
* ori_data_2：以mm为单位采集，24个文件

##5. DataCombination：合并截面数据
* 直接复制20171103/DataVolumeRender2中的.cpp/CMakeLits.txt重新编译
* 所用数据：ori_data_2插值后的数据
