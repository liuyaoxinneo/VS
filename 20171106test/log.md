#2017.11.6

##0. Src：
* doppler库文件和include文件夹
* qcustomplot.cpp/.h

##1. Migrate：将现有的Qt工程运行环境迁移到VS内的尝试
* 主要难点在于：doppler的库导入、qcustomplot的导入
* 与前一阶段工程配置的不同在于：不使用Cmake进行构建
* 步骤参考Note：向VS中迁移Qt
* Qt源码一：E:/Qt/20170418_section_set，包括了qcustomplot的导入，但为离线

思路：从头重新编写一个Qt工程能避免直接复制的时候发生的一些错误！
###问题与解决：
* 向空白的Qt工程内添加 qcustomplot.h/.cpp时，出现许多**无法解析的外部符号**
  * 项目--属性--连接器--输入--附加依赖项中添加 **$(QTDIR)\lib\Qt5PrintSupportd.lib** 即可
  * 也可以通过在VS内新建Qt项目时选择：``print support``模块（会自动附加依赖项Qt5PrintSupportd.lib）
* 在Qt Designer中对窗口部件进行修改，保存.ui文件后main.cpp中不能立刻对ui中的部件设置
  * 经过一次运行，即可进行设置，打``ui.``之后会出现可供调用的部件

*至此，已能转移Qt/20170418_section_set*

*实现了qcustomplot类的导入*
