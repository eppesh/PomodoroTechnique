

[toc]

Pomodoro Technique (番茄工作法) 是一款借鉴[番茄工作法](https://zh.wikipedia.org/wiki/%E7%95%AA%E8%8C%84%E5%B7%A5%E4%BD%9C%E6%B3%95)理念制作的**倒计时**小软件。

为了简单易用，更加专注于自己要做的事，软件默认进行25分钟的倒计时。倒计时结束会有声音提醒，并可选择休息5分钟或进入下一次专注。如果任何时候想休息5分钟，点击“休息”按钮可直接开始5分钟倒计时。

写该软件的初衷是嫌别的“类番茄时钟”的软件太麻烦，而自己只需要一个最简单的倒计时工具，时间到了提醒一下即可，每次只需专注于这25min之内。想休息了直接点击“休息”，休息5min后再提醒。因此用C++写了个自用的简易版倒计时工具。

Authors: Sean (eppesh@163.com)

# Features

- 根据设置/默认的时分秒进行倒计时；
- 倒计时结束有音乐提醒；
- 倒计时过程中可以暂停/继续；
- 重置当前计时；
- 设置时分秒；
- 一键切换成休息（5min）倒计时；

# Documentation

相关文档可通过在线方式查看，或在源码目录下找到。

# Building

目前仅限于Windows平台。

利用`Visual Studio`直接打开源码中的工程文件`.sln`或`.vcxproj`进行编译运行即可；

开发相关：

- `C++`；
- `Visual Studio 2019`; 
- `EasyX 2021`; 

注意：在VS2019中，“项目属性” -- “配置属性” -- “高级” -- “字符集” 采用了“使用了多字节字符集”，若使用默认的“使用 Unicode 字符集”，编译时可能会报错。

# Usage

- 开始第一个“专注的25min”：

  双击运行程序后，直接点击“开始”按钮，程序便会以默认的25min开始倒计时。

- 结束时的音乐提醒：

  每一次倒计时结束，都会自动有音乐提醒，并会弹出 “是否休息5分钟？” 的提示，无论选择“确定”或是“取消”都将停止播放音乐。若选择“确定”，会将倒计时设置为5min，您可以点击“开始”按钮开始休息倒计时；若选择“取消”，则会将倒计时恢复到初始状态，您可以点击“开始”继续下一个“专注的25min”，或什么都不做。

- 暂停/继续倒计时：

  当倒计时开始后，在其结束前点击“暂停”按钮以暂停当前倒计时；再次点击“开始”按钮便开继续倒计时。

- 重置当前计时：

  点击“重置”按钮会将当前倒计时重置为之前设置的倒计时（若没有设置，则为默认的25min）。如果倒计时正在计时，则重置后会重新开始倒计时；如果倒计时处于“暂停”状态，则重置后也仍将处于“暂停”状态。

- 设置时分秒：

  通过点击右上角的“设置”按钮可以设置需要倒计时的时分秒，只有在“暂停”状态时才可进行设置，成功设置后会将当前倒计时调整为新设置的时分秒。注意：设置时必须按 `dd:dd:dd` 的格式（d表示0～9的1个数字，用2个数字来表示时/分/秒，中间用冒号隔开；形如：01:02:00;）输入，否则会提示“输入格式不正确”。

- 一键切换成休息倒计时：

  点击右上角的“休息”按钮，会立刻进入休息（5min）倒计时，无论当前是什么状态。

# Screenshots

![Pic](https://github.com/eppesh/PomodoroTechnique/blob/main/screenshots/Demo.gif)

截图请参考`./screenshots/`下的图片。

# Changelogs

- Updated 03/14/2022
  - 新增项目（根据自己实际需要，想有个自用的倒计时小工具，便有了这个项目）；
  - 完成倒计时核心逻辑（每隔一秒，数字减一）；
  - 完成倒计时数字显示（为了好看，采用七段展示样式的数字）；
  - 采用按键（空格键）方式启动/暂停倒计时；
- Updated 03/16/2022
  - 取消按键方式，改采用点击按钮方式进行操作；
  - 保留按`Esc`键退出程序的功能；
  - 添加“开始”、“暂停”、“重置”、“设置”按钮功能；
- Updated 03/17/2022
  - 添加“休息”功能（即一键进入休息模式）；
  - 更新`README.md`文档；

# Upcoming Changes

Some of the goals for 2022 are:

- 代码优化；
- 可自定义显示数字的大小；

# Postscripts

初衷主要是自用，代码还未进一步优化，也不保证会不断更新。日后使用过程中遇到不爽的地方，还是会尽量完善。