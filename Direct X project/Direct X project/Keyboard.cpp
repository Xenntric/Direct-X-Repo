#include "Keyboard.h"

bool Keyboard::keyPressed(unsigned char keycode) const noexcept
{
	return keyStates[keycode];
}

Keyboard::Event Keyboard::parseKey() noexcept
{
	if (keyBuffer.size() > 0u)
	{
		Keyboard::Event event = keyBuffer.front();
		keyBuffer.pop();

		return event;
	}
	else
	{
		return Keyboard::Event();
	}
}

bool Keyboard::keyEmpty() const noexcept
{
	return keyBuffer.empty();
}

void Keyboard::keyClear() noexcept
{
	keyBuffer = std::queue<Event>();
}

bool Keyboard::charEmpty() noexcept
{
	return charBuffer.empty();
}

void Keyboard::charClear() noexcept
{
	charBuffer = std::queue<char>();
}

void Keyboard::clear() noexcept
{
	keyClear();
	charClear();
}

char Keyboard::readChar() noexcept
{
	if (charBuffer.size() > 0u)
	{
		unsigned char charCode = charBuffer.front();
		charBuffer.pop();
		return charCode;
	}
	else
	{
		return 0;
	}
}

void Keyboard::enableAutoRepeat() noexcept
{
	autoRepeatEnabled = true;
}

void Keyboard::disableAutoRepeat() noexcept
{
	autoRepeatEnabled = false;
}

bool Keyboard::isAutoRepeatEnabled() const noexcept
{
	return autoRepeatEnabled;
}

void Keyboard::onKeyPressed(unsigned char keycode) noexcept
{
	keyStates[keycode] = true;
	keyBuffer.push(Keyboard::Event(Keyboard::Event::PressType::OnPress, keycode));
	trimBuffer(keyBuffer);
}

void Keyboard::onKeyReleased(unsigned char keycode) noexcept
{
	keyStates[keycode] = false;
	keyBuffer.push(Keyboard::Event(Keyboard::Event::PressType::OnRelease, keycode));
	trimBuffer(keyBuffer);
} 

void Keyboard::onChar(char character) noexcept
{
	charBuffer.push(character);
	trimBuffer(charBuffer);
}

void Keyboard::clearState() noexcept
{
	keyStates.reset();
}
