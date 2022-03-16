// 名称：timer.h
// 版权：仅供学习
// 作者：Sean (eppesh@163.com)
// 环境：VS2019;EasyX_20211109
// 时间：03/16/2022
// 说明：倒计时

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
    void DrawUI();                              // 负责绘制显示主界面
    void Run();                                 // 负责侦听鼠标与键盘事件
    void Start();                               // 负责倒计时逻辑

private:    
    void DrawNumber();
    void OnEvent(const ExMessage message);
    void Reset();
    void SetTimer();                            // 自定义时分秒
    // 将贴图背景设置为透明,并在指定位置(dst_x,dst_y)处显示图片
    void SetTransparent(IMAGE image, const int img_width, const int img_height,
        const int dst_x, const int dst_y);

private:
    int current_hour_;                          // 当前时分秒,随着倒计时而不断减少
    int current_minute_;
    int current_second_;
    int original_hour_;                          // 用户设置的时分秒,在重置时使用
    int original_minute_;
    int original_second_;
    IMAGE img_btn_start_;
    IMAGE img_btn_pause_;
    IMAGE img_btn_reset_;
    IMAGE img_btn_reset_light_;
    IMAGE img_btn_set_;
    bool is_reset_;                             // 是否已重置
    bool is_pause_;                             // 是否已暂停
};

} // namespace pomodoro_technique
#endif