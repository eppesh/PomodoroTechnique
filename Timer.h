#ifndef TIMER_H_
#define TIMER_H_

#include <stdio.h>
#include <conio.h>
#include <time.h>

#include "seven_segment_display.h"

namespace pomodoro_technique
{
class Timer
{
public:
    Timer(int hour, int minute, int second);
    void DrawUI();
    void Run();

private:
    void DrawNumber();

private:
    int hour_;
    int minute_;
    int second_;
};

} // namespace pomodoro_technique
#endif