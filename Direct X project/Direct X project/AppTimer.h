#pragma once
#include <chrono>
class AppTimer
{
public:
	AppTimer() noexcept;
	float Mark() noexcept;
	float Peek() const noexcept;
private:
	std::chrono::steady_clock::time_point last;
};