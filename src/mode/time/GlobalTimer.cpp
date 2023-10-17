//
// Created by 夏雨 on 2023/10/13.
//

#include "GlobalTimer.h"

class GlobalTimer
{
public:
    GlobalTimer() = default;

    // 获取当前时间（毫秒）
    static long long getCurrentTimeMillis()
    {
        using namespace std::chrono;
         //std::chrono::system_clock
        return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    }
};