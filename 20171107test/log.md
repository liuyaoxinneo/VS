#2017.11.7

##0. Src：复制昨天的Src文件
##1. Migrate1：迁移更加复杂的工程——在昨天的基础上接入doppler的库
* Qt源码：E:/Qt/20170509exp_standerdB，实时传输/绘图

##问题与解决：
---
* 添加doppler的库和包含文件后，出现错误 **找不到doppler.dll文件**

添加doppler库的正确步骤如下：
1. include文件夹的加入：右击项目——属性——配置属性——C/C++——常规——附加包含目录：添加一条目录``E:\VS-sync\20171107test\Migrate2\doppler\include``，即为include文件夹
2. .dll和.lib库的加入：右击项目——属性——配置属性——链接器——常规——附加库目录：添加一项``E:\VS-sync\20171107test\Migrate2\doppler\dll``，即为dll文件夹的目录
3. 右击项目——属性——配置属性——链接器——输入——附加依赖项，查看是否有 **Doppler_netd.lib** 项，没有要加上
4. 项目.h文件如下设置，即，加入对 **doppler_net.h** 文件的包含 + 设置Doppler_net类，名字可以为
```
···
#include "doppler_net.h"

class Migrate2 : public QMainWindow
{
···

private:
  ···
	Doppler_net net;
  ···
};

```
5. 最后， **要把Doppler_netd.dll和Doppler_netd.lib放入生成的.exe程序的同一目录下**
在``..\x64\Debug``目录下（经实验，只需加入doppler_netd.dll即可）
---

* 在成功加入doppler库之后，再加入qcustomplot类的调用，出现问题 **打不开qcustomplot.h文件**
  * 在 右击项目——属性——配置属性——C/C++——常规——附加包含目录中，添加含有qcustomplot.h的文件夹，即可在ui_***.h中打开，后面的问题也不会存在了

*至此，已能迁移项目Qt/20170509exp_standerdB*

*实现了整体的迁移！*

---
* .ui文件的快速迁移：在VS中用XML编辑器打开.ui文件，复制Qt中Debug模式下的.ui文件（即是用XML编辑器打开的），复制，并修改以下几处：
* 即，修改与项目名称有关的地方即可
```
<class>Migrate2Class</class>
<widget class="QMainWindow" name="Migrate2Class">
```
```
</property>
<property name="windowTitle">
  <string>Migrate2</string>
</property>
```
