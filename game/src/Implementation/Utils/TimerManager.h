#pragma once
#include <chrono>

#include "Contract/IModuleManager.h"
#include "Contract/Singleton.h"

class TimerManager final :
    public IModuleManager, public Singleton<TimerManager>
{
    std::chrono::time_point<std::chrono::steady_clock> time_start_;
    std::chrono::time_point<std::chrono::steady_clock> time_last_frame_;
public:

	std::chrono::milliseconds MS_PER_UPDATE = std::chrono::milliseconds{ 33 };

    TimerManager(Singleton<TimerManager>::token) {}

    std::chrono::milliseconds GetElapsedTime() const;

    std::chrono::milliseconds GetAndSetFrameDelta();

    void Restart();

    void startUp() override;
    void shutDown() override;
};

