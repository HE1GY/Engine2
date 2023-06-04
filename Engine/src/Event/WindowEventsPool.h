#pragma once

#include "Event.h"

namespace Engine
{
	struct WindowResized
	{
		int width, height;
	};

	struct WindowClosed
	{
	};

	struct KeyEvent
	{
		int32_t m_key_code;
	};

	struct KeyPress : public KeyEvent
	{
		int32_t m_repeated_count;
	};

	struct KeyReleased : public KeyEvent
	{
	};

	class KeyTyped : public KeyEvent
	{
	};

	struct MouseMoved
	{
		int32_t m_x, m_y;
	};

	struct MouseButtonPressed
	{
		int32_t m_key_code;
	};

	struct MouseButtonReleased
	{
		int32_t m_key_code;
	};
	struct MouseScrolled
	{
		int32_t m_x_offset;
		int32_t m_y_offset;
	};


	struct EventsPool
	{
		Event<WindowResized> onWindowResized;
		Event<WindowClosed> onWindowClosed;

		Event<KeyPress> onKeyPress;
		Event<KeyReleased> onKeyReleased;
		Event<KeyTyped> onKeyTyped;

		Event<MouseMoved> onMouseMoved;
		Event<MouseButtonPressed> onMouseButtonPressed;
		Event<MouseButtonReleased> onMouseButtonReleased;
		Event<MouseScrolled> onMouseScrolled;
	};
}