#pragma once

#include <chrono>

class FPSTracker {
public:
    FPSTracker();
    float RegisterNewFrame();
    float GetTimeFromLastFrame();
private:
    int m_frameCount;
    float m_timeFromLastSecond;
    std::chrono::high_resolution_clock::time_point m_lastFrameTime;
};