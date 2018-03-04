# EvaluationSystem
在我国的各级人民法院，为了记录庭审现场各类人员（包括：司法人员、嫌疑人、律师等）的谈话内容，有一批工作人员专门负责此项工作，这批工作人员被称之为“速录员”。速录员要求具有很快的文字录入速度和较高的录入准确率，以保证庭审记录的完整性和准确性。因此，如何有效地评测速录员录入文字的速度以及准确率是各级人民法院在招聘和考核速录员时需要面对的难题。针对这一现状，本实验要求各位同学在Visual Studio 2010下使用C++语言独立开发出一个速录员评测系统。

------
#涉及技术：


**音频播放：** 实验中的音频格式为MP3，其实也适用于WAV格式的音频文件，使用的接口为MCI（The Media Control Interface），参考的技术贴为<http://blog.csdn.net/dancewyr/article/details/7183572>；


**文字录入和身份验证：** 速录员输入文字的地方使用了EditBox控件，考虑到文字的自动换行，解决办法是设置EditBox的多行属性和垂直滚动条属性为true。身份验证只是单纯的校验身份证号的长度，并不涉及其合法性，这里可以利用正则表达式对此进行校验，有时间的时候我会再补上此内容。


**测试倒计时：** 这里的倒计时主要是控制文字录入区的激活状态，如果倒计时为0时，文字录入区的状态为不可选中，即表示测试结束。


**配置文件读取：** 通过读取.ini文件获取测试的时长，音频文件格式，最大录入速度（计算成绩时需要用到），录入速度与准确率的权重等信息，参考技术贴：<https://zhidao.baidu.com/question/33265898.html>


**成绩计算：** 这里用的算法为编辑距离（EditDistance）算法，具体的内容介绍可以参考我的CSDN博客：<http://blog.csdn.net/CliuGeek/article/details/78750137>,计算成绩的时候需要用到之前说到的录入速度和准确率所设定的权重，根据以下公式进行计算：Score = Percentage_accuracy*accuracy+Percentage_speed*speed，其中score为最终成绩，Percentage_accuracy为准确率的权重，accuracy为录入的准确率，Percentage_speed为录入速度的权重，speed为录入速度。两个权重的设定分别为0.7和0.3。speed计算方式为：speed = 录入文字个数/所用时间（分钟）。最快录入速度为.ini文件中读取到的最快录入速度，如果超过该速度，按该最大速度计算。最终成绩最高为100分，超过100分按100分计算。


**成绩单生成：** 利用PDFLib工具，将评测用户的个人信息（准考证号、身份证号等信息）、录入文字内容，成绩等信息写入PDF文件并生成，防止评测用户自行修改其内容。生成文件放在了D盘根目录下，文件名为test.pdf。如果想再次测试该程序，请务必删除第一次生成的pdf文件，否则会因为已存在同名文件而无法创新新的pdf文件。


-----

#操作流程：


**开始界面：**

![开始界面](/img/1.png)

**填写个人信息并选题：**

![个人信息填写](/img/2.png)

**开始答题：**

![开始答题](/img/3.png)

**提交：**

![提交](/img/4.png)

**打印成绩单：**

![打印成绩单](/img/5.png)

**成绩单：**

![成绩单](/img/6.png)