#include <iostream>
#include <cmath>
#include "FPSTracker.h"

FPSTracker::FPSTracker() : m_frameCount(0), m_timeFromLastSecond(0.0f) {
    m_lastFrameTime = std::chrono::high_resolution_clock::now();
}

// Saves the current time (called on each frame update). Returns the time from last frame
float FPSTracker::RegisterNewFrame() {
    // Read and update clock
    float deltaTime = GetTimeFromLastFrame();
    m_lastFrameTime = std::chrono::high_resolution_clock::now();

    // Count frames from the last second
    m_frameCount++;
    m_timeFromLastSecond += deltaTime;
    
    // Each second, print the FPS and reset the frame counts
    if (m_timeFromLastSecond >= 1.0) {
        std::cout << "FPS: " << m_frameCount << std::endl;
        m_timeFromLastSecond = fmod(m_timeFromLastSecond, 1.0f);
        m_frameCount = 0;
    }

    return deltaTime;
}

// Returns the time from last frame
float FPSTracker::GetTimeFromLastFrame() {
    std::chrono::duration<float> delta = std::chrono::high_resolution_clock::now() - m_lastFrameTime;
    return delta.count();
}