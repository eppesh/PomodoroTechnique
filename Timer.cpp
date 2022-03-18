#include "timer.h"

namespace pomodoro_technique
{

Timer::Timer(int hour, int minute, int second) :current_hour_(hour), current_minute_(minute), current_second_(second),
    is_reset_(false), is_pause_(true), is_rest_(false)
{
    if (current_hour_ < 0)
    {
        current_hour_ = 0;
    }
    else if (current_hour_ > 23)
    {
        current_hour_ = 23;
    }
    if (current_minute_ < 0)
    {
        current_minute_ = 0;
    }
    else if (current_minute_ > 59)
    {
        current_minute_ = 59;
    }
    if (current_second_ < 0)
    {
        current_second_ = 0;
    }
    else if (current_second_ > 59)
    {
        current_second_ = 59;
    }
    original_hour_ = current_hour_;
    original_minute_ = current_minute_;
    original_second_ = current_second_;
}

void Timer::SetTransparent(IMAGE image, const int img_width, const int img_height, const int dst_x, const int dst_y)
{
    IMAGE mask(img_width, img_height);
    DWORD *p_memory_close = GetImageBuffer(&image);
    DWORD *p_memory_mask = GetImageBuffer(&mask);
    COLORREF mask_background = p_memory_close[0];
    for (int i = 0; i < img_width * img_height; ++i)
    {
        if (p_memory_close[i] <= 0x555555 && p_memory_close[i] >= 0)  // 0x555555 是深灰色
        {
            p_memory_mask[i] = WHITE;
        }
        else
        {
            p_memory_mask[i] = BLACK;
        }
    }
    BeginBatchDraw();
    putimage(dst_x, dst_y, &mask, SRCAND);
    putimage(dst_x, dst_y, &image, SRCPAINT);
    FlushBatchDraw();
    EndBatchDraw();
}

// 绘制主界面
void Timer::DrawUI()
{
    int window_width = 1200;
    int window_height = 560;
    initgraph(window_width, window_height/*, EW_SHOWCONSOLE*/);  // 初始化窗体
    setbkcolor(RGB(6, 31, 62));
    cleardevice();

    // Show the "Start/Pause","Reset","Set" button    
    loadimage(&img_btn_start_, "PNG", MAKEINTRESOURCE(IDB_START));
    loadimage(&img_btn_pause_, "PNG", MAKEINTRESOURCE(IDB_PAUSE));
    loadimage(&img_btn_reset_, "PNG", MAKEINTRESOURCE(IDB_RESET));
    loadimage(&img_btn_reset_light_, "PNG", MAKEINTRESOURCE(IDB_RESET_LIGHT));
    loadimage(&img_btn_set_, "PNG", MAKEINTRESOURCE(IDB_SET));
    loadimage(&img_btn_rest_, "PNG", MAKEINTRESOURCE(IDB_REST));
    loadimage(&img_btn_rest_light_, "PNG", MAKEINTRESOURCE(IDB_REST_LIGHT));
    SetTransparent(img_btn_start_, 64, 64, 500, 400);
    SetTransparent(img_btn_reset_, 64, 64, 620, 400);
    SetTransparent(img_btn_set_, 32, 32, 1158, 10);
    SetTransparent(img_btn_rest_, 32, 32, 1158, 52);
}

void Timer::Start()
{
    DrawNumber();
    while (true)
    {
        if (is_reset_)
        {
            DrawNumber();
            is_reset_ = false;
        }
        if (is_pause_)
        {
            continue;
        }
        while (current_hour_ != 0 || current_minute_ != 0 || current_second_ != 0)
        {
            time_t current_time = time(nullptr);
            while (current_time == time(nullptr));   // 等待1秒,使显示从25:00变为24:59
            if(is_pause_)
            {
                break;
            }
            if (--current_second_ < 0)
            {
                current_second_ = 59;
                if (--current_minute_ < 0)
                {
                    current_minute_ = 59;
                    if (--current_hour_ < 0)
                    {
                        current_hour_ = 23;
                    }
                }
            }

            DrawNumber();
        }
        
        // 倒计时结束（提醒并回到暂停状态）
        if (current_hour_ == 0 && current_minute_ == 0 && current_second_ == 0)
        {
            // 循环播放提示音
            PlaySound(MAKEINTRESOURCE(IDR_WAVE_ALARM), nullptr, SND_RESOURCE | SND_ASYNC | SND_LOOP);
            if (is_rest_)
            {
                is_rest_ = false;
                int msg_id = MessageBox(0, "是否开始下一次专注？", "Timer", MB_ICONQUESTION | MB_OKCANCEL);
                if (msg_id == IDOK)
                {                    
                    current_hour_ = 0;
                    current_minute_ = 25;
                    current_second_ = 0;
                    is_pause_ = false;
                    is_reset_ = true;
                    setfillcolor(RGB(6, 31, 62));
                    setlinecolor(RGB(6, 31, 62));
                    fillrectangle(500, 400, 564, 464);
                    SetTransparent(img_btn_start_, 64, 64, 500, 400);
                }
                else
                {
                    Sleep(500);
                    is_pause_ = true;
                    is_reset_ = true;
                    Reset();
                    setfillcolor(RGB(6, 31, 62));
                    setlinecolor(RGB(6, 31, 62));
                    fillrectangle(500, 400, 564, 464);
                    SetTransparent(img_btn_start_, 64, 64, 500, 400);
                }
            }
            else
            {
                int msg_id = MessageBox(0, "是否休息5分钟？", "Timer", MB_ICONQUESTION | MB_OKCANCEL);
                if (msg_id == IDOK)
                {
                    is_rest_ = true;
                    current_hour_ = 0;
                    current_minute_ = 5;
                    current_second_ = 0;
                    is_pause_ = false;
                    is_reset_ = true;
                    setfillcolor(RGB(6, 31, 62));
                    setlinecolor(RGB(6, 31, 62));
                    fillrectangle(500, 400, 564, 464);
                    SetTransparent(img_btn_pause_, 64, 64, 500, 400);
                }
                else
                {
                    Sleep(500);
                    is_pause_ = true;
                    is_reset_ = true;
                    Reset();
                    setfillcolor(RGB(6, 31, 62));
                    setlinecolor(RGB(6, 31, 62));
                    fillrectangle(500, 400, 564, 464);
                    SetTransparent(img_btn_start_, 64, 64, 500, 400);
                }
            }            
            PlaySound(nullptr, nullptr, 0);         // 停止播放音乐            
        }
    }
}

void Timer::Run()
{
    ExMessage message;
    while (true)
    {
        message = getmessage(EM_MOUSE | EM_KEY);
        OnEvent(message);
        Sleep(10);
    }
}

// 判断圆形是否有触发
bool IsTrigger(RECT rectangle, POINT point)
{
    if (PtInRect(&rectangle, point))
    {
        // 圆心坐标(前提是已知按钮)
        int radius = (rectangle.right - rectangle.left) / 2;
        int x = rectangle.left + radius;
        int y = rectangle.top + radius;
        int distance = (x - point.x) * (x - point.x) + (y - point.y) * (y - point.y);
        return (distance <= (radius * radius));
    }
    return false;
}

void Timer::SetTimer()
{
    char input[32] = { 0 };
    InputBox(input, 32, "请以\"##:##:##\"形式输入时分秒,每个位置2位,按冒号隔开;\n如: \"00:15:01\"");
    std::string times(input);
    std::regex pattern("([0-9]{2}):([0-9]{2}):([0-9]{2})");
    if (std::regex_match(times, pattern))
    {
        original_hour_ = atoi(times.substr(0, 2).c_str());
        original_minute_ = atoi(times.substr(3, 2).c_str());
        original_second_ = atoi(times.substr(6, 2).c_str());
        if (original_hour_ < 0)
        {
            original_hour_ = 0;
        }
        else if (original_hour_ > 23)
        {
            original_hour_ = 23;
        }
        if (original_minute_ < 0)
        {
            original_minute_ = 0;
        }
        else if (original_minute_ > 59)
        {
            original_minute_ = 59;
        }
        if (original_second_ < 0)
        {
            original_second_ = 0;
        }
        else if (original_second_ > 59)
        {
            original_second_ = 59;
        }
        Reset();
        is_reset_ = true;
    }
    else
    {
        MessageBox(nullptr, "输入格式不正确!", "Timer", MB_OK);
    }
}

void Timer::OnEvent(const ExMessage message)
{
    RECT rect_start = { 500,400,564,464 };      // 开始按钮所在矩形区域
    RECT rect_reset = { 620,400,684,464 };      // 重置按钮所在矩形区域
    RECT rect_set = { 1126,10,1190,42 };        // 设置按钮所在矩形区域
    RECT rect_rest = { 1158,52,1190,84 };       // 休息按钮所在矩形区域
    POINT mouse = { message.x,message.y };      // 鼠标当前坐标
    switch (message.message)
    {
    case WM_LBUTTONDOWN:
    {
        // 判断"开始/暂停"按钮是否触发
        if (IsTrigger(rect_start, mouse))
        {
            // 先覆盖现有按钮,再显示新按钮
            setfillcolor(RGB(6, 31, 62));
            setlinecolor(RGB(6, 31, 62));
            fillrectangle(500, 400, 564, 464);
            is_pause_ = !is_pause_;
            // 若已暂停,说明当前显示为"开始";再次单击表示"开始"功能,需继续倒计时并更换图标为"暂停"
            if (is_pause_)
            {
                SetTransparent(img_btn_start_, 64, 64, 500, 400);
            }
            // 若未暂停,说明当前显示为"暂停";再次单击表示"暂停"功能,需暂停倒计时并更换图标为"开始"
            else
            {
                SetTransparent(img_btn_pause_, 64, 64, 500, 400);
            }

        }
        // 判断"重置"按钮是否触发
        else if (IsTrigger(rect_reset, mouse))
        {
            is_reset_ = true;
            Reset();
            // 先覆盖现有按钮,再显示新按钮
            setfillcolor(RGB(6, 31, 62));
            setlinecolor(RGB(6, 31, 62));
            fillrectangle(620, 400, 684, 464);
            SetTransparent(img_btn_reset_light_, 64, 64, 620, 400);
        }
        // 判断"设置"按钮是否触发;只有暂停时才可设置
        else if (IsTrigger(rect_set, mouse) && is_pause_)
        {
            is_rest_ = false;
            SetTimer();
        }
        // 判断"休息"按钮是否触发
        else if (IsTrigger(rect_rest, mouse))
        {
            is_rest_ = true;
            is_pause_ = false;  // 立刻开始"休息"的倒计时
            current_hour_ = 0;
            current_minute_ = 5;
            current_second_ = 0;
            is_reset_ = true;
            setfillcolor(RGB(6, 31, 62));
            setlinecolor(RGB(6, 31, 62));
            fillrectangle(1158, 52, 1190, 84);
            SetTransparent(img_btn_rest_light_, 32, 32, 1158, 52);
            // 并显示"暂停"按钮,表示现在已在倒计时
            setfillcolor(RGB(6, 31, 62));
            setlinecolor(RGB(6, 31, 62));
            fillrectangle(500, 400, 564, 464);
            SetTransparent(img_btn_pause_, 64, 64, 500, 400);
        }
        break;
    }
    case WM_LBUTTONUP:  // 可通过变换图片实现强调效果
    {
        if (IsTrigger(rect_reset, mouse))
        {
            // 先覆盖现有按钮,再显示新按钮
            setfillcolor(RGB(6, 31, 62));
            setlinecolor(RGB(6, 31, 62));
            fillrectangle(620, 400, 684, 464);
            SetTransparent(img_btn_reset_, 64, 64, 620, 400);

            if (!is_pause_)
            {
                // 重置后,不会暂停,而是把数字重置后继续倒计时
                setfillcolor(RGB(6, 31, 62));
                setlinecolor(RGB(6, 31, 62));
                fillrectangle(500, 400, 564, 464);
                SetTransparent(img_btn_pause_, 64, 64, 500, 400);
            }
        }
        else if (IsTrigger(rect_rest, mouse))
        {
            setfillcolor(RGB(6, 31, 62));
            setlinecolor(RGB(6, 31, 62));
            fillrectangle(1158, 52, 1190, 84);
            SetTransparent(img_btn_rest_, 32, 32, 1158, 52);
        }
    }
    case WM_KEYDOWN:
    {
        if (message.vkcode == VK_SPACE)
        {
        }
        else if (message.vkcode == VK_ESCAPE)
        {
            closegraph();
            exit(0);
        }
        break;
    }
    default:
        break;
    }
}

// 绘制倒计时的数字
void Timer::DrawNumber()
{
    // 显示"时",即第1,2个数字
    SevenSegmentDisplay::DrawNumber(current_hour_ / 10, 40, 120, RGB(6, 31, 62));
    SevenSegmentDisplay::DrawNumber(current_hour_ % 10, 200, 120, RGB(6, 31, 62));
    // 绘制上下两个小圆圈（渐变色）
    setfillcolor(RGB(64, 157, 254));  // 蓝色
    solidcircle(400, 180, 15);  // 画圆
    setfillcolor(RGB(163, 212, 255));  // 浅蓝色
    solidcircle(400, 300, 15);
    // 显示"分",即第3,4个数字
    SevenSegmentDisplay::DrawNumber(current_minute_ / 10, 440, 120, RGB(6, 31, 62));
    SevenSegmentDisplay::DrawNumber(current_minute_ % 10, 600, 120, RGB(6, 31, 62));
    // 绘制上下两个小圆圈（渐变色）
    setfillcolor(RGB(64, 157, 254));  // 蓝色
    solidcircle(800, 180, 15);  // 画圆
    setfillcolor(RGB(163, 212, 255));  // 浅蓝色
    solidcircle(800, 300, 15);
    // 显示"秒",即第5,6个数字
    SevenSegmentDisplay::DrawNumber(current_second_ / 10, 840, 120, RGB(6, 31, 62));
    SevenSegmentDisplay::DrawNumber(current_second_ % 10, 1000, 120, RGB(6, 31, 62));
}

void Timer::Reset()
{
    current_hour_ = original_hour_;
    current_minute_ = original_minute_;
    current_second_ = original_second_;
}
} // namespace pomodoro_technique