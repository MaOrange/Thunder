This is readme.txt.

正在准备C++实训ing

为学习Cocos2d-x (c++) 和 Git 写的小练习。

这是一个cocos2d-x纵版飞机射击游戏（雷电），是按照《Cocos2d-x 3.x 开发详解》 第三章 的教程实例做的，中间因为BUG找不到只好重写了HUDLayer类。

只有Classes和Resources是用户定义的，其他都是cocos引擎的内容，所以要放在一个目录才能跑，但是不知道加了 .gitignore 之后会不会生效。

 ![image]( https://github.com/MaOrange/Thunder/blob/master/demo.png)

 ![image]( https://github.com/MaOrange/Thunder/blob/master/demo2.png)


已知问题：
 在cocos2d-x中显示中文：

 以GBK编码cpp文件，再加上
 #pragma execution_character_set("utf-8")
：vs可以通过编译并显示中文，但在安卓端无法显示中文（非乱码）

以UTF-8编码cpp，
：会出现诡异BUG，经常无法通过编译。
但是可以生成debug.apk并正常显示中文。也可以在github中正确显示更改。

solution：
1.使用xml？？？？
2.