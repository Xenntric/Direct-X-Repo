#pragma once
class KeyboardEvent
{
public:
	enum EventType
	{
		Pressed,
		Released,
		Invalid
	};
	KeyboardEvent();
	KeyboardEvent(const EventType type, const unsigned char key);
	bool isPressed()	const;
	bool isReleased()	const;
	bool isValid()		const;
	unsigned char GetKeyCode() const;

private:
	EventType type;
	unsigned char key;

};

