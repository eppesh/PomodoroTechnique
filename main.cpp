// ���ƣ�����ʱ
// ��Ȩ������ѧϰ������
// ���ߣ�Sean (eppesh@163.com)
// ������VS2019;EasyX 2021
// ʱ�䣺03/14/2022
// ˵��������ʱ���ܼ���ʵ��

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

    // ��Ӧ����¼������߳�
    std::thread mouse_thread(&Timer::Run, &timer);
    mouse_thread.detach();

    timer.Start();

    system("pause");
    return 0;
}
