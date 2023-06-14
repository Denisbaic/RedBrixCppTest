#include "TimerManager.h"

std::chrono::milliseconds TimerManager::GetElapsedTime() const
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - time_start_);
}

std::chrono::milliseconds TimerManager::GetAndSetFrameDelta()
{
	using clock = std::chrono::high_resolution_clock;

	const auto current_time_point = clock::now();
	const auto dt = std::chrono::duration_cast<std::chrono::milliseconds>(current_time_point - time_last_frame_);
	time_last_frame_ = current_time_point;
	return dt;
}

void TimerManager::Restart()
{
	time_start_ = std::chrono::high_resolution_clock::now();
	time_last_frame_= time_start_;
}

void TimerManager::startUp()
{
	time_start_ = std::chrono::high_resolution_clock::now();
	time_last_frame_ = time_start_;
}

void TimerManager::shutDown()
{
}
