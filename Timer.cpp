#include "timer.h"

namespace pomodoro_technique
{
Timer::Timer(int hour, int minute, int second) :hour_(hour), minute_(minute), second_(second)
{
    if (hour_ < 0)
    {
        hour_ = 0;
    }
    else if (hour_ > 23)
    {
        hour_ = 23;
    }
    if (minute_ < 0)
    {
        minute_ = 0;
    }
    else if (minute_ > 59)
    {
        minute_ = 59;
    }
    if (second_ < 0)
    {
        second_ = 0;
    }
    else if (second_ > 59)
    {
        second_ = 59;
    }
}

// 绘制主界面
void Timer::DrawUI()
{
    initgraph(1200, 600, EW_SHOWCONSOLE);  // 初始化窗体，去掉最小化及关闭按钮
    //SetWindowLong(GetHWnd(), GWL_STYLE, GetWindowLong(GetHWnd(), GWL_STYLE) & ~WS_CAPTION);  // 去掉标题栏
    //int caption_height = GetSystemMetrics(SM_CYCAPTION);  // 获取标题栏的高度
    //SetWindowRgn(GetHWnd(), CreateRectRgn(0, caption_height, window_width, window_height - caption_height), true);  // 去掉黑色边框（去掉标题栏后右边下边会有黑色边框）
    setbkcolor(RGB(6, 31, 62));
    cleardevice();

    //RECT title_rect = { 240,80,560,160 };
    //settextcolor(RGB(163, 212, 255));  // 浅蓝色
    //settextstyle(80, 0, "楷体");
    //drawtext("Focus", &title_rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);  // 在指定区域内以指定格式输出字符串
    //settextstyle(50, 0, "楷体");

    settextcolor(RGB(254, 218, 168));  // 浅黄色（米黄色）
    settextstyle(50, 0, "楷体");
    outtextxy(450, 360, "开始");
    outtextxy(650, 360, "重置");

    // TODO(@Sean) 按下“开始”后开始倒计时,按下“暂停”时要暂停

}

void Timer::Run()
{
    while (true)
    {
        DrawNumber();
        // TODO(@Sean) 按下“开始”按钮，或者按下空格键才开始倒计时
        if (_getch() != VK_SPACE /*按下了开始按钮*/)
        {
            continue;
        }
        bool is_pause = false;
        while (hour_ != 0 || minute_ != 0 || second_ != 0)
        {            
            time_t current_time = time(nullptr);
            while (current_time == time(nullptr));   // 等待1秒,使显示从25:00变为24:59
            if (_kbhit())
            {
                break;
            }
            if (--second_ < 0)
            {
                second_ = 59;
                if (--minute_ < 0)
                {
                    minute_ = 59;
                    if (--hour_ < 0)
                    {
                        hour_ = 23;
                    }
                }
            }
            
            DrawNumber();
        }
        _getch();
    }
    
    // 时分秒都为0时,说明倒计时结束
    //std::cout << "End" << std::endl;
}

// 绘制倒计时的数字
void Timer::DrawNumber()
{
    // 显示"时",即第1,2个数字
    SevenSegmentDisplay::DrawNumber(hour_ / 10, 40, 80, RGB(6, 31, 62));
    SevenSegmentDisplay::DrawNumber(hour_ % 10, 200, 80, RGB(6, 31, 62));
    // 绘制上下两个小圆圈（渐变色）
    setfillcolor(RGB(64, 157, 254));  // 蓝色
    solidcircle(400, 140, 15);  // 画圆
    setfillcolor(RGB(163, 212, 255));  // 浅蓝色
    solidcircle(400, 260, 15);
    // 显示"分",即第3,4个数字
    SevenSegmentDisplay::DrawNumber(minute_ / 10, 440, 80, RGB(6, 31, 62));
    SevenSegmentDisplay::DrawNumber(minute_ % 10, 600, 80, RGB(6, 31, 62));
    // 绘制上下两个小圆圈（渐变色）
    setfillcolor(RGB(64, 157, 254));  // 蓝色
    solidcircle(800, 140, 15);  // 画圆
    setfillcolor(RGB(163, 212, 255));  // 浅蓝色
    solidcircle(800, 260, 15);
    // 显示"秒",即第5,6个数字
    SevenSegmentDisplay::DrawNumber(second_ / 10, 840, 80, RGB(6, 31, 62));
    SevenSegmentDisplay::DrawNumber(second_ % 10, 1000, 80, RGB(6, 31, 62));
}
} // namespace pomodoro_technique