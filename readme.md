星小夜的登录器
======

[![latest packaged version(s)](https://img.shields.io/badge/latest%20packaged%20version(s)-6.0.0-blue)](https://img.shields.io/badge/latest%20packaged%20version(s)-6.0.0-blue)
[![Build Status](https://img.shields.io/badge/build-passing-brightgreen)](https://img.shields.io/badge/build-passing-green)
[![CodeFactor](https://www.codefactor.io/repository/github/ijhack/qtpass/badge)](https://www.codefactor.io/repository/github/ijhack/qtpass)
[![Language grade: C/C++](https://img.shields.io/lgtm/grade/cpp/g/IJHack/QtPass.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/IJHack/QtPass/context:cpp)
[![FOSSA Status](https://app.fossa.io/api/projects/git%2Bgithub.com%2FIJHack%2FQtPass.svg?type=shield)](https://app.fossa.io/projects/git%2Bgithub.com%2FIJHack%2FQtPass?ref=badge_shield)
[![QMake Github Action](https://img.shields.io/badge/QMake-pass-red)](https://img.shields.io/badge/build-passing-brightgreen)

大家好，我是星夜，登录器已经完全全部代码的编写，现在在github上开源，本项目采用**GPL**协议，下载源码进行学习时，注意遵守相关协议，做一个合格的搬运工。


下载与使用
--------

星小夜的登录器采用qt作为框架，理论上跨平台

用户可以从[下载地址](#)下载完整的登录器

函数介绍文档
--------
为了减轻程序员读代码的负担，我将整份源码的所有函数都写上了注释，并生成了说明文档

说明文档：[文档地址](https://starlitnightly.github.io/out/html/index.html)

函数注释例子：

	/**
	 * @brief 一键换装备-搜索装备
	 * @param pid 窗口id
	 * @param name 要换的装备名
	 * @return 无
	 */
	void Searchbag(HWND pid,QString name){
	    dm.MoveTo(736,382);
	    dm.LeftClick();
	    QString s=name;
	    foreach(QChar c, s)
	        PostMessage(pid, WM_CHAR, c.unicode(), 0);
	    Delay(500);
	    dm.MoveTo(797,380);
	    dm.LeftClick();
	}


源码使用方法
--------

* source文件夹内全部文件下载下来，在**qt creater**中打开**untitled.pro**
* 在项目中，构建设置中设置编译套件为**Qt-5.9.0-MinGW-32**，也就是qt最原始的编译套件，不是MSVC什么的
* 编译无问题后，在程序的release或者debug目录中**（取决于你选择的模式）**，文件结构应与图中一样，否则程序会自动结束**（检查缺少的文件/文件夹，在logonseer文件夹中都有）**

		├─bearer
		├─font
		├─gif
		├─iconengines
		├─imageformats
		├─json
		├─pic
		├─platforms
		├─seer背包
		├─translations
		└─工具
		    ├─dm
		    ├─Fiddler
		    │  ├─FiddlerHook
		    │  │  ├─Content
		    │  │  ├─defaults
		    │  │  │  └─preferences
		    │  │  ├─locale
		    │  │  │  └─en-US
		    │  │  └─skin
		    │  ├─ImportExport
		    │  ├─Inspectors
		    │  ├─ResponseTemplates
		    │  ├─Scripts
		    │  ├─Tools
		    │  ├─检查
		    │  └─汉化截图
		    ├─星小夜的脚本
		    └─赛尔数据计算器
		        ├─帮助文件
		        │  ├─Bin
		        │  └─Easter Eggs
		        ├─数据文件
		        │  ├─刻印
		        │  ├─套装
		        │  │  └─目镜
		        │  ├─属性
		        │  ├─种族值
		        │  ├─称号
		        │  ├─设置
		        │  └─魂印特训
		        ├─记录文件
		        │  ├─属性表格
		        │  └─精灵培养
		        └─资源文件


项目更新
--------

2020.07.03

1. 基础功能迁移——刷新、静音、变速
2. 简单脚本迁移——一键勇者之塔脚本

2020.07.04

1. 变速窗口完善
2. 普通脚本全部迁移

2020.07.05

1. 增加巅峰脚本、圣瑞脚本
2. 增加nono提示-绿火、巅峰阵容截图（有待优化）

2020.07.06

1. 增加六界神王殿脚本
2. nono提示优化（全方位）
3. 增加一键换背包

2020.07.07

1. 增加精灵技能快查与对战精灵识别
2. nono优化
3. 增加垃圾回收机制

## License
### GNU GPL v3.0

[![GNU GPL v3.0](http://www.gnu.org/graphics/gplv3-127x51.png)](http://www.gnu.org/licenses/gpl.html)

View official GNU site <http://www.gnu.org/licenses/gpl.html>.

[![OSI](http://opensource.org/trademarks/opensource/OSI-Approved-License-100x137.png)](https://opensource.org/licenses/GPL-3.0)

[View the Open Source Initiative site.](https://opensource.org/licenses/GPL-3.0)