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
        if (p_memory_close[i] <= 0x555555 && p_memory_close[i] >= 0)  // 0x555555 �����ɫ
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

// ����������
void Timer::DrawUI()
{
    int window_width = 1200;
    int window_height = 560;
    initgraph(window_width, window_height/*, EW_SHOWCONSOLE*/);  // ��ʼ������
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
            while (current_time == time(nullptr));   // �ȴ�1��,ʹ��ʾ��25:00��Ϊ24:59
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
        
        // ����ʱ���������Ѳ��ص���ͣ״̬��
        if (current_hour_ == 0 && current_minute_ == 0 && current_second_ == 0)
        {
            // ѭ��������ʾ��
            PlaySound(MAKEINTRESOURCE(IDR_WAVE_ALARM), nullptr, SND_RESOURCE | SND_ASYNC | SND_LOOP);
            if (is_rest_)
            {
                is_rest_ = false;
                int msg_id = MessageBox(0, "�Ƿ�ʼ��һ��רע��", "Timer", MB_ICONQUESTION | MB_OKCANCEL);
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
                int msg_id = MessageBox(0, "�Ƿ���Ϣ5���ӣ�", "Timer", MB_ICONQUESTION | MB_OKCANCEL);
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
            PlaySound(nullptr, nullptr, 0);         // ֹͣ��������            
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

// �ж�Բ���Ƿ��д���
bool IsTrigger(RECT rectangle, POINT point)
{
    if (PtInRect(&rectangle, point))
    {
        // Բ������(ǰ������֪��ť)
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
    InputBox(input, 32, "����\"##:##:##\"��ʽ����ʱ����,ÿ��λ��2λ,��ð�Ÿ���;\n��: \"00:15:01\"");
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
        MessageBox(nullptr, "�����ʽ����ȷ!", "Timer", MB_OK);
    }
}

void Timer::OnEvent(const ExMessage message)
{
    RECT rect_start = { 500,400,564,464 };      // ��ʼ��ť���ھ�������
    RECT rect_reset = { 620,400,684,464 };      // ���ð�ť���ھ�������
    RECT rect_set = { 1126,10,1190,42 };        // ���ð�ť���ھ�������
    RECT rect_rest = { 1158,52,1190,84 };       // ��Ϣ��ť���ھ�������
    POINT mouse = { message.x,message.y };      // ��굱ǰ����
    switch (message.message)
    {
    case WM_LBUTTONDOWN:
    {
        // �ж�"��ʼ/��ͣ"��ť�Ƿ񴥷�
        if (IsTrigger(rect_start, mouse))
        {
            // �ȸ������а�ť,����ʾ�°�ť
            setfillcolor(RGB(6, 31, 62));
            setlinecolor(RGB(6, 31, 62));
            fillrectangle(500, 400, 564, 464);
            is_pause_ = !is_pause_;
            // ������ͣ,˵����ǰ��ʾΪ"��ʼ";�ٴε�����ʾ"��ʼ"����,���������ʱ������ͼ��Ϊ"��ͣ"
            if (is_pause_)
            {
                SetTransparent(img_btn_start_, 64, 64, 500, 400);
            }
            // ��δ��ͣ,˵����ǰ��ʾΪ"��ͣ";�ٴε�����ʾ"��ͣ"����,����ͣ����ʱ������ͼ��Ϊ"��ʼ"
            else
            {
                SetTransparent(img_btn_pause_, 64, 64, 500, 400);
            }

        }
        // �ж�"����"��ť�Ƿ񴥷�
        else if (IsTrigger(rect_reset, mouse))
        {
            is_reset_ = true;
            Reset();
            // �ȸ������а�ť,����ʾ�°�ť
            setfillcolor(RGB(6, 31, 62));
            setlinecolor(RGB(6, 31, 62));
            fillrectangle(620, 400, 684, 464);
            SetTransparent(img_btn_reset_light_, 64, 64, 620, 400);
        }
        // �ж�"����"��ť�Ƿ񴥷�;ֻ����ͣʱ�ſ�����
        else if (IsTrigger(rect_set, mouse) && is_pause_)
        {
            is_rest_ = false;
            SetTimer();
        }
        // �ж�"��Ϣ"��ť�Ƿ񴥷�
        else if (IsTrigger(rect_rest, mouse))
        {
            is_rest_ = true;
            is_pause_ = false;  // ���̿�ʼ"��Ϣ"�ĵ���ʱ
            current_hour_ = 0;
            current_minute_ = 5;
            current_second_ = 0;
            is_reset_ = true;
            setfillcolor(RGB(6, 31, 62));
            setlinecolor(RGB(6, 31, 62));
            fillrectangle(1158, 52, 1190, 84);
            SetTransparent(img_btn_rest_light_, 32, 32, 1158, 52);
            // ����ʾ"��ͣ"��ť,��ʾ�������ڵ���ʱ
            setfillcolor(RGB(6, 31, 62));
            setlinecolor(RGB(6, 31, 62));
            fillrectangle(500, 400, 564, 464);
            SetTransparent(img_btn_pause_, 64, 64, 500, 400);
        }
        break;
    }
    case WM_LBUTTONUP:  // ��ͨ���任ͼƬʵ��ǿ��Ч��
    {
        if (IsTrigger(rect_reset, mouse))
        {
            // �ȸ������а�ť,����ʾ�°�ť
            setfillcolor(RGB(6, 31, 62));
            setlinecolor(RGB(6, 31, 62));
            fillrectangle(620, 400, 684, 464);
            SetTransparent(img_btn_reset_, 64, 64, 620, 400);

            if (!is_pause_)
            {
                // ���ú�,������ͣ,���ǰ��������ú��������ʱ
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

// ���Ƶ���ʱ������
void Timer::DrawNumber()
{
    // ��ʾ"ʱ",����1,2������
    SevenSegmentDisplay::DrawNumber(current_hour_ / 10, 40, 120, RGB(6, 31, 62));
    SevenSegmentDisplay::DrawNumber(current_hour_ % 10, 200, 120, RGB(6, 31, 62));
    // ������������СԲȦ������ɫ��
    setfillcolor(RGB(64, 157, 254));  // ��ɫ
    solidcircle(400, 180, 15);  // ��Բ
    setfillcolor(RGB(163, 212, 255));  // ǳ��ɫ
    solidcircle(400, 300, 15);
    // ��ʾ"��",����3,4������
    SevenSegmentDisplay::DrawNumber(current_minute_ / 10, 440, 120, RGB(6, 31, 62));
    SevenSegmentDisplay::DrawNumber(current_minute_ % 10, 600, 120, RGB(6, 31, 62));
    // ������������СԲȦ������ɫ��
    setfillcolor(RGB(64, 157, 254));  // ��ɫ
    solidcircle(800, 180, 15);  // ��Բ
    setfillcolor(RGB(163, 212, 255));  // ǳ��ɫ
    solidcircle(800, 300, 15);
    // ��ʾ"��",����5,6������
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