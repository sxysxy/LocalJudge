# LocalJudge

简易的本地评测系统
默认传统型文本比较，支持Special Judge

具体用法：
judge.exe 运行即可
 
测试数据放到test\_data文件夹下

config.txt 进行配置：

　source　　　源文件地址
 
　compiler　　编译命令
 
　points　　　测试点数目 
 
　input　　　 输入文件格式 ，提供一个%d占位符代表测试点编号
 
　output　　  输出文件格式，提供一个%d占位符代表测试点编号
 
　answer　　 答案文件格式，提供一个%d占位符代表测试点编号
 
　time　　　　时间限制，计时器用硬件级高精度计时器实现。但是考虑中间启动程序的开销，测量值会略大于真实值。
 
　spj　　　　评测命令，提供两个%s占位符代表输出文件和答案文件。默认用fc评测
