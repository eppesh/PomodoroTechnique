#include "seven_segment_display.h"

namespace pomodoro_technique
{
// ����7����ϳ�0~9������
void SevenSegmentDisplay::DrawNumber(const int number, const int x, const int y, const COLORREF background_color)
{
    // �������������������,�������֮ǰ��ʾ������,����һֱ��ʾ8
    setfillcolor(background_color);
    solidrectangle(x, y, x + 160, y + 240);

    switch (number)
    {
    case 0:
        DrawSevenSegmentA(x, y);
        DrawSevenSegmentB(x, y);
        DrawSevenSegmentC(x, y);
        DrawSevenSegmentD(x, y);
        DrawSevenSegmentE(x, y);
        DrawSevenSegmentF(x, y);
        break;
    case 1:
        DrawSevenSegmentB(x, y);
        DrawSevenSegmentC(x, y);
        break;
    case 2:
        DrawSevenSegmentA(x, y);
        DrawSevenSegmentB(x, y);
        DrawSevenSegmentG(x, y);
        DrawSevenSegmentE(x, y);
        DrawSevenSegmentD(x, y);
        break;
    case 3:
        DrawSevenSegmentA(x, y);
        DrawSevenSegmentB(x, y);
        DrawSevenSegmentG(x, y);
        DrawSevenSegmentC(x, y);
        DrawSevenSegmentD(x, y);
        break;
    case 4:
        DrawSevenSegmentF(x, y);
        DrawSevenSegmentG(x, y);
        DrawSevenSegmentB(x, y);
        DrawSevenSegmentC(x, y);
        break;
    case 5:
        DrawSevenSegmentA(x, y);
        DrawSevenSegmentF(x, y);
        DrawSevenSegmentG(x, y);
        DrawSevenSegmentC(x, y);
        DrawSevenSegmentD(x, y);
        break;
    case 6:
        DrawSevenSegmentA(x, y);
        DrawSevenSegmentF(x, y);
        DrawSevenSegmentG(x, y);
        DrawSevenSegmentC(x, y);
        DrawSevenSegmentD(x, y);
        DrawSevenSegmentE(x, y);
        break;
    case 7:
        DrawSevenSegmentA(x, y);
        DrawSevenSegmentB(x, y);
        DrawSevenSegmentC(x, y);
        break;
    case 8:
        DrawSevenSegmentA(x, y);
        DrawSevenSegmentB(x, y);
        DrawSevenSegmentC(x, y);
        DrawSevenSegmentD(x, y);
        DrawSevenSegmentE(x, y);
        DrawSevenSegmentF(x, y);
        DrawSevenSegmentG(x, y);
        break;
    case 9:
        DrawSevenSegmentA(x, y);
        DrawSevenSegmentB(x, y);
        DrawSevenSegmentC(x, y);
        DrawSevenSegmentD(x, y);
        DrawSevenSegmentF(x, y);
        DrawSevenSegmentG(x, y);
        break;
    }
}

// Ŀǰ���ֵĴ�С�ǹ̶���
void SevenSegmentDisplay::DrawSevenSegmentA(const int x, const int y)
{
    // ���ַ�ʽ:һ��int points[],��Ӧsolidpolygon((POINT*)points, 6);��������ķ�ʽ
    //int points[] = { 36 + x, 14 + y, 59 + x, 39 + y, 118 + x, 39 + y, 138 + x, 15 + y, 131 + x, 9 + y, 41 + x, 9 + y };
    POINT points[] = { {36 + x, 14 + y}, {59 + x, 39 + y}, {118 + x, 39 + y},
        {138 + x,15 + y},{131 + x, 9 + y}, {41 + x, 9 + y} };
    setfillcolor(RGB(176, 215, 254));  // ���ø÷ֶε���ɫΪǳ��ɫ
    solidpolygon(points, 6);  // ʹ�õ�ǰ���κ͵�ǰ�����ʽ�����ޱ߿�����6����
}

void SevenSegmentDisplay::DrawSevenSegmentB(const int x, const int y)
{
    int points[] = { 143 + x, 20 + y, 152 + x, 31 + y, 144 + x, 105 + y,
        132 + x, 115 + y, 115 + x, 98 + y, 122 + x, 41 + y, };
    setfillcolor(RGB(187, 250, 255));  // ��ǳ����ɫ
    solidpolygon((POINT *)points, 6);
}

void SevenSegmentDisplay::DrawSevenSegmentC(const int x, const int y)
{
    int points[] = { 132 + x, 119 + y, 144 + x, 128 + y, 136 + x, 213 + y,
        129 + x, 222 + y, 107 + x, 201 + y, 115 + x, 134 + y };
    setfillcolor(RGB(245, 255, 190));
    solidpolygon((POINT *)points, 6);
}

void SevenSegmentDisplay::DrawSevenSegmentD(const int x, const int y)
{
    int points[] = { 40 + x, 203 + y, 104 + x, 203 + y, 126 + x, 226 + y,
        120 + x, 231 + y, 24 + x, 231 + y, 18 + x, 226 + y };
    setfillcolor(RGB(251, 221, 185));  // ����ɫ
    solidpolygon((POINT *)points, 6);
}

void SevenSegmentDisplay::DrawSevenSegmentE(const int x, const int y)
{
    int points[] = { 25 + x, 120 + y, 43 + x, 136 + y, 38 + x, 199 + y,
        15 + x, 223 + y, 6 + x, 209 + y, 15 + x, 127 + y };
    setfillcolor(RGB(245, 255, 192));  // ǳ��ɫ
    solidpolygon((POINT *)points, 6);
}

void SevenSegmentDisplay::DrawSevenSegmentF(const int x, const int y)
{
    int points[] = { 32 + x, 17 + y, 53 + x, 40 + y, 47 + x, 96 + y,
        26 + x, 113 + y, 18 + x, 102 + y, 25 + x, 27 + y };
    setfillcolor(RGB(184, 249, 251));  // ��ǳ����ɫ
    solidpolygon((POINT *)points, 6);
}

void SevenSegmentDisplay::DrawSevenSegmentG(const int x, const int y)
{
    int points[] = { 46 + x, 101 + y, 113 + x, 101 + y, 127 + x, 116 + y,
        111 + x, 131 + y, 45 + x, 131 + y, 29 + x, 117 + y };
    setfillcolor(RGB(187, 254, 219));  // ��ǳ����ɫ
    solidpolygon((POINT *)points, 6);
}


} // namespace challengesix