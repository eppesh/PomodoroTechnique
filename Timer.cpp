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

// ����������
void Timer::DrawUI()
{
    initgraph(1200, 600, EW_SHOWCONSOLE);  // ��ʼ�����壬ȥ����С�����رհ�ť
    //SetWindowLong(GetHWnd(), GWL_STYLE, GetWindowLong(GetHWnd(), GWL_STYLE) & ~WS_CAPTION);  // ȥ��������
    //int caption_height = GetSystemMetrics(SM_CYCAPTION);  // ��ȡ�������ĸ߶�
    //SetWindowRgn(GetHWnd(), CreateRectRgn(0, caption_height, window_width, window_height - caption_height), true);  // ȥ����ɫ�߿�ȥ�����������ұ��±߻��к�ɫ�߿�
    setbkcolor(RGB(6, 31, 62));
    cleardevice();

    //RECT title_rect = { 240,80,560,160 };
    //settextcolor(RGB(163, 212, 255));  // ǳ��ɫ
    //settextstyle(80, 0, "����");
    //drawtext("Focus", &title_rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);  // ��ָ����������ָ����ʽ����ַ���
    //settextstyle(50, 0, "����");

    settextcolor(RGB(254, 218, 168));  // ǳ��ɫ���׻�ɫ��
    settextstyle(50, 0, "����");
    outtextxy(450, 360, "��ʼ");
    outtextxy(650, 360, "����");

    // TODO(@Sean) ���¡���ʼ����ʼ����ʱ,���¡���ͣ��ʱҪ��ͣ

}

void Timer::Run()
{
    while (true)
    {
        DrawNumber();
        // TODO(@Sean) ���¡���ʼ����ť�����߰��¿ո���ſ�ʼ����ʱ
        if (_getch() != VK_SPACE /*�����˿�ʼ��ť*/)
        {
            continue;
        }
        bool is_pause = false;
        while (hour_ != 0 || minute_ != 0 || second_ != 0)
        {            
            time_t current_time = time(nullptr);
            while (current_time == time(nullptr));   // �ȴ�1��,ʹ��ʾ��25:00��Ϊ24:59
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
    
    // ʱ���붼Ϊ0ʱ,˵������ʱ����
    //std::cout << "End" << std::endl;
}

// ���Ƶ���ʱ������
void Timer::DrawNumber()
{
    // ��ʾ"ʱ",����1,2������
    SevenSegmentDisplay::DrawNumber(hour_ / 10, 40, 80, RGB(6, 31, 62));
    SevenSegmentDisplay::DrawNumber(hour_ % 10, 200, 80, RGB(6, 31, 62));
    // ������������СԲȦ������ɫ��
    setfillcolor(RGB(64, 157, 254));  // ��ɫ
    solidcircle(400, 140, 15);  // ��Բ
    setfillcolor(RGB(163, 212, 255));  // ǳ��ɫ
    solidcircle(400, 260, 15);
    // ��ʾ"��",����3,4������
    SevenSegmentDisplay::DrawNumber(minute_ / 10, 440, 80, RGB(6, 31, 62));
    SevenSegmentDisplay::DrawNumber(minute_ % 10, 600, 80, RGB(6, 31, 62));
    // ������������СԲȦ������ɫ��
    setfillcolor(RGB(64, 157, 254));  // ��ɫ
    solidcircle(800, 140, 15);  // ��Բ
    setfillcolor(RGB(163, 212, 255));  // ǳ��ɫ
    solidcircle(800, 260, 15);
    // ��ʾ"��",����5,6������
    SevenSegmentDisplay::DrawNumber(second_ / 10, 840, 80, RGB(6, 31, 62));
    SevenSegmentDisplay::DrawNumber(second_ % 10, 1000, 80, RGB(6, 31, 62));
}
} // namespace pomodoro_technique