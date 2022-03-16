// 名称：倒计时
// 版权：仅供学习交流；
// 作者：Sean (eppesh@163.com)
// 环境：VS2019;EasyX 2021
// 时间：03/14/2022
// 说明：倒计时功能简易实现

#include <ctime>
#include <iostream>
#include <thread>

#include "graphics.h"
#include "timer.h"

using namespace pomodoro_technique;


int main()
{
    Timer timer(0, 0, 3);
    timer.DrawUI();

    // 响应鼠标事件的子线程
    std::thread mouse_thread(&Timer::Run, &timer);
    mouse_thread.detach();

    timer.Start();

    system("pause");
    return 0;
}
