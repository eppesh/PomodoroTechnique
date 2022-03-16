// ���ƣ�timer.h
// ��Ȩ������ѧϰ
// ���ߣ�Sean (eppesh@163.com)
// ������VS2019;EasyX_20211109
// ʱ�䣺03/16/2022
// ˵��������ʱ

#ifndef TIMER_H_
#define TIMER_H_

#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <regex>
#include <time.h>

#include "resource.h"
#include "seven_segment_display.h"

#pragma comment(lib,"winmm.lib")

namespace pomodoro_technique
{
class Timer
{
public:
    Timer(int hour, int minute, int second);
    void DrawUI();                              // ���������ʾ������
    void Run();                                 // �����������������¼�
    void Start();                               // ���𵹼�ʱ�߼�

private:    
    void DrawNumber();
    void OnEvent(const ExMessage message);
    void Reset();
    void SetTimer();                            // �Զ���ʱ����
    // ����ͼ��������Ϊ͸��,����ָ��λ��(dst_x,dst_y)����ʾͼƬ
    void SetTransparent(IMAGE image, const int img_width, const int img_height,
        const int dst_x, const int dst_y);

private:
    int current_hour_;                          // ��ǰʱ����,���ŵ���ʱ�����ϼ���
    int current_minute_;
    int current_second_;
    int original_hour_;                          // �û����õ�ʱ����,������ʱʹ��
    int original_minute_;
    int original_second_;
    IMAGE img_btn_start_;
    IMAGE img_btn_pause_;
    IMAGE img_btn_reset_;
    IMAGE img_btn_reset_light_;
    IMAGE img_btn_set_;
    bool is_reset_;                             // �Ƿ�������
    bool is_pause_;                             // �Ƿ�����ͣ
};

} // namespace pomodoro_technique
#endif