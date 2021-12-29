#include "KeyboardClass.h"
KeyboardClass::KeyboardClass()
{
	for (size_t i = 0; i < 256; i++)
	{
		this->keyStates[i] = false; //initalise all key states to false;
	}
}

bool KeyboardClass::KeyIsPressed(const unsigned char keycode)
{
	return this->keyStates[keycode];
}
bool KeyboardClass::KeyBufferIsEmpty()
{
	return this->keyBuffer.empty();
}

bool KeyboardClass::CharBufferIsEmpty()
{
	return this->charBuffer.empty();
}

KeyboardEvent KeyboardClass::ReadKey()
{
	if (this->keyBuffer.empty()) //if no keys to read
	{
		return KeyboardEvent(); //return the empty keyboardevent
	}
	else
	{
		KeyboardEvent ke = this->keyBuffer.front(); //get keyboard event at front of queue
		this->keyBuffer.pop(); //remove that keyboard event
		return ke; //return the keyboard event
	}
}

unsigned char KeyboardClass::ReadChar()
{
	if (this->charBuffer.empty()) //if no keys to read
	{
		return 0u(); //return the null char
	}
	else
	{
		unsigned char c = this->charBuffer.front(); //get char at front of queue
		this->charBuffer.pop(); //remove that char
		return c; //return the char
	}
}
void KeyboardClass::OnKeyPressed(const unsigned char key)
{
	this->keyStates[key] = true;
	this->keyBuffer.push(KeyboardEvent(KeyboardEvent::EventType::Pressed, key));
}
void KeyboardClass::OnKeyReleased(const unsigned char key)
{
	this->keyStates[key] = false;
	this->keyBuffer.push(KeyboardEvent(KeyboardEvent::EventType::Released, key));
}
void KeyboardClass::OnChar(const unsigned char key)
{
	this->charBuffer.push(key);
}

//autorepeat keys
void KeyboardClass::EnableAutoRepeatKeys()
{
	this->autoRepeatKeys = true;
}
void KeyboardClass::DisableAutoRepeatKeys()
{
	this->autoRepeatKeys = false;
}
bool KeyboardClass::IsKeyAutoRepeat()
{
	return this->autoRepeatKeys;
}
//autorepeat char
void KeyboardClass::EnableAutoRepeatChars()
{
	this->autoRepeatChars = true;
}
void KeyboardClass::DisableAutorepeatChars()
{
	this->autoRepeatChars = false;
}
bool KeyboardClass::IsCharAutoRepeat()
{
	return this->autoRepeatChars;
}