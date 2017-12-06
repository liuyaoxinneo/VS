#2017.11.22

总结之前的成果，便于今后取用

序号|名称 | 环境 | 功能| 工作方式 | 所用数据
---|---|---|---|---|---
1|1102/QtIDWInsert  |  Qt | 读取18755个点的数据，插值，输出一个截面内700*700个像素点的数据（int型）  |离线|19-43
2|1103/DataVolumeRender2  | VS  |  逐个读取截面 .txt文件，体绘制（时间：9s）; 合并为一个.mhd/.zraw文件 |离线|19-43  
3|1104/DataVolumeRender3  | VS  | 读取.mhd/.zraw文件，体绘制（时间：2s），并对体绘制函数进行设置  |离线|19-43  
4  |1106/Migrate/test1   | VS  | 在VS中建立Qt工程，并接入QCustomPlot类  |离线|  E:/Qt/20170418_section_set
5  |1107/Migrate2   | VS  | 在VS中建立Qt工程，并接入: QCustomPlot类、doppler库  |离线|  E:/Qt/20170509exp_standerdB
