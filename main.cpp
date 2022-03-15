// 名称：倒计时
// 版权：仅供学习交流；
// 作者：Sean (eppesh@163.com)
// 环境：VS2019;EasyX 2021
// 时间：2022/03/14
// 说明：倒计时

#include <ctime>
#include <iostream>
#include <windows.h>

#include "graphics.h"

#include "timer.h"

using namespace pomodoro_technique;


int main()
{
    Timer timer(0, 1, 10);
    timer.DrawUI();
    timer.Run();

    system("pause");
    return 0;
}
