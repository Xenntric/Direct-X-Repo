#include "KeyboardEvent.h"

KeyboardEvent::KeyboardEvent()
	:
	type(EventType::Invalid),
	key(0u)
{}

KeyboardEvent::KeyboardEvent(const EventType type, const unsigned char key)
	:
	type(type),
	key(key)
{}

bool KeyboardEvent::isPressed() const
{
	return this->type == EventType::Pressed;
}

bool KeyboardEvent::isReleased() const
{
	return this->type == EventType::Released;
}

bool KeyboardEvent::isValid() const
{
	return this->type != EventType::Invalid;
}

unsigned char KeyboardEvent::GetKeyCode() const
{
	return this->key;
}