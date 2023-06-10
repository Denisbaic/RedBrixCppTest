#include "EngineECS.h"

#include "raylib.h"
#include <chrono>
#include "TimerManager.h"

void EngineECS::PreInit(std::any const& config)
{
    auto const& casted_config = std::any_cast<EngineECS_Config>(config);

    InitWindow(casted_config.screenWidth, casted_config.screenHeight, casted_config.title);
    InitAudioDevice();

    TimerManager::instance().startUp();

    SetTargetFPS(60);
    game_ = casted_config.game;
}

void EngineECS::Init()
{
    game_->BeginPlay();
}

void EngineECS::GameLoop()
{
    while (!WindowShouldClose())
    {
        RunFrame();
    }
}

void EngineECS::RunFrame()
{
    const auto dt = TimerManager::instance().GetAndSetFrameDelta();
    
    lag_ += dt;

    while (lag_ >= TimerManager::instance().MS_PER_UPDATE)
    {
        game_->Tick(std::chrono::duration<double>(TimerManager::instance().MS_PER_UPDATE).count());
        lag_ -= TimerManager::instance().MS_PER_UPDATE;
    }

    game_->Render();
}

void EngineECS::EndPlay()
{
    TimerManager::instance().shutDown();
    
    CloseAudioDevice();     // Close audio context

    CloseWindow();          // Close window and OpenGL context
}
