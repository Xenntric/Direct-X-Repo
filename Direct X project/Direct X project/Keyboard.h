#pragma once
#include <Windows.h>
#include <queue>
#include <bitset>
class Keyboard
{
	friend class Window;
public:
	class Event
	{
	public:
		enum class PressType
		{
			OnPress,
			OnRelease,
			Error
		};
	private:
		PressType pressType;
		unsigned char keycode;
	public:
		Event()
			:
			pressType(PressType::Error),
			keycode(0u)
		{
		}
		Event(PressType pressType, unsigned char keycode) noexcept
			:
			pressType(pressType),
			keycode(keycode)
		{
		}
		bool IsPress() const noexcept
		{
			return pressType == PressType::OnPress;
		}
		bool IsRelease() const noexcept
		{
			return pressType == PressType::OnRelease;
		}
		unsigned char GetCode() const noexcept
		{
			return keycode;
		}
	};
public:
	Keyboard() = default;
	Keyboard(const Keyboard&) = delete;
	Keyboard& operator=(const Keyboard&) = delete;
	// key event stuff
	bool keyPressed(unsigned char keycode) const noexcept;
	Event parseKey() noexcept;
	bool keyEmpty() const noexcept;
	void keyClear() noexcept;
	// char event stuff
	char readChar() noexcept;
	bool charEmpty() noexcept;
	void charClear() noexcept;
	void clear() noexcept;
	// autorepeat control
	void enableAutoRepeat() noexcept;
	void disableAutoRepeat() noexcept;
	bool isAutoRepeatEnabled() const noexcept;
private:
	void onKeyPressed(unsigned char keycode) noexcept;
	void onKeyReleased(unsigned char keycode) noexcept;
	void onChar(char character) noexcept;
	void clearState() noexcept;
	template<typename T>
	static void trimBuffer(std::queue<T>& buffer) noexcept;
private:
	static constexpr unsigned int nKeys = 256u;
	static constexpr unsigned int bufferSize = 16u;
	bool autoRepeatEnabled = false;
	std::bitset<nKeys> keyStates;
	std::queue<Event> keyBuffer;
	std::queue<char> charBuffer;
};

template<typename T>
inline void Keyboard::trimBuffer(std::queue<T>& buffer) noexcept
{
}
