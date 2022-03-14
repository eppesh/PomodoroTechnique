// ���ƣ��߶�չʾ��
// ��Ȩ������ѧϰ����
// ���ߣ�Sean (eppesh@163.com)
// ������VS2019; EasyX 2021
// ʱ�䣺2021/07/12
// ˵����"�߶�"��˳ʱ�����ڵ������α��ΪA��G; ��A-����̺�,B-�ұ��ϲ����,C-�ұ��²����,
//       D-����̺�̺�,E-����²����,F-����ϲ����,G-�м�̺�;

// ��л����[2864292458@qq.com]; ������@��ͬѧ�Ƽ��ĵ�����������7ģ��Ϊ����,�������ʵ��޸�������

#ifndef SEVEN_SEGMENT_DISPALY_H_
#define SEVEN_SEGMENT_DISPALY_H_

#include <graphics.h>

namespace pomodoro_technique
{
class SevenSegmentDisplay
{
public:
    // ��ָ��λ��(x,y)�����ơ��߶�չʾ����ʽ������number; background_color�������óɸ�������ı���ɫһ��
    static void DrawNumber(const int number, const int x, const int y, const COLORREF background_color);

private:

    // ��ָ��λ��(x,y)�������߶��е�A��
    static void DrawSevenSegmentA(const int x, const int y);
    // ��ָ��λ��(x,y)�������߶��е�B��
    static void DrawSevenSegmentB(const int x, const int y);
    // ��ָ��λ��(x,y)�������߶��е�C��
    static void DrawSevenSegmentC(const int x, const int y);
    // ��ָ��λ��(x,y)�������߶��е�D��
    static void DrawSevenSegmentD(const int x, const int y);
    // ��ָ��λ��(x,y)�������߶��е�E��
    static void DrawSevenSegmentE(const int x, const int y);
    // ��ָ��λ��(x,y)�������߶��е�F��
    static void DrawSevenSegmentF(const int x, const int y);
    // ��ָ��λ��(x,y)�������߶��е�G��
    static void DrawSevenSegmentG(const int x, const int y);
};
} // namespace pomodoro_technique
#endif