
#include "GameTimer.h"

GameTimer::GameTimer() noexcept
{
	last = std::chrono::steady_clock::now();
}

float GameTimer::Mark() noexcept
{
	const auto old = last;
	last = std::chrono::steady_clock::now();
	const std::chrono::duration<float> frameTime = last - old;
	return frameTime.count();
}

float GameTimer::Peek() const noexcept
{
	return std::chrono::duration<float>(std::chrono::steady_clock::now() - last).count();
}
