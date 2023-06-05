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
		int32_t key_code;
	};

	struct KeyPress : public KeyEvent
	{
		int32_t repeated_count;
	};

	struct KeyReleased : public KeyEvent
	{
	};

	struct KeyTyped
	{
		uint32_t key_code;
	};

	struct MouseMoved
	{
		int32_t x, y;
	};

	struct MouseButtonPressed
	{
		int32_t key_code;
	};

	struct MouseButtonReleased
	{
		int32_t key_code;
	};
	struct MouseScrolled
	{
		int32_t x_offset;
		int32_t y_offset;
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