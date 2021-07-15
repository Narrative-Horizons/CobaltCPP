#pragma once

#include <cstdint>

#include <cobalt/keycodes.hpp>

namespace cobalt
{
	enum class KeyState : uint32_t
	{
		None,
		Pressed,
		Down,
		Up
	};

	class Input
	{
		public:
			static bool isKeyDown(const uint32_t aKeyCode);
			static bool isKeyPressed(const uint32_t aKeyCode);
			static bool isKeyUp(const uint32_t aKeyCode);

			static bool isMouseDown(const uint32_t aKeyCode);
			static bool isMousePressed(const uint32_t aKeyCode);
			static bool isMouseUp(const uint32_t aKeyCode);

			static void getMousePosition(int32_t* x, int32_t* y);

			static void update();

			// TODO: Make private and use events
			static void _setKeyPressed(const uint32_t aKeyCode);
			static void _setKeyReleased(const uint32_t aKeyCode);

			static void _setMousePressed(const uint32_t aKeyCode);
			static void _setMouseReleased(const uint32_t aKeyCode);

			static void _setMousePosition(float x, float y);

		private:
			static KeyState _sKeyStates[COBALT_KEY_LAST];
			static KeyState _sKeyLastState[COBALT_KEY_LAST];

			static KeyState _sMouseStates[COBALT_MOUSE_BUTTON_LAST];
			static KeyState _sMouseLastState[COBALT_MOUSE_BUTTON_LAST];

			static int32_t _mouseX, _mouseY;
	};
}
