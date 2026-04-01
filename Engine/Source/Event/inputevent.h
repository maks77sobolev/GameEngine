#pragma once


namespace LifeExe
{
enum class EventType
{
	WindowsClose,
	WindowsResize,
	MouseMove,
	MouseButton,
	MouseScroll,
	KeyPress,
};
using EventData=int;
struct InputEvent
{
    EventType type;
    EventData data;
};
}// end of namespace lifeexe 