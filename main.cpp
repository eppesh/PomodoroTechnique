// ���ƣ�����ʱ
// ��Ȩ������ѧϰ������
// ���ߣ�Sean (eppesh@163.com)
// ������VS2019;EasyX 2021
// ʱ�䣺2022/03/14
// ˵��������ʱ

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
