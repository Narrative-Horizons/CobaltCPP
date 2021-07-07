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

			static void update();

			// TODO: Make private and use events
			static void _setKeyPressed(const uint32_t aKeyCode);
			static void _setKeyReleased(const uint32_t aKeyCode);

		private:
			static KeyState _sKeyStates[COBALT_KEY_LAST];
			static KeyState _sKeyLastState[COBALT_KEY_LAST];
	};
}
