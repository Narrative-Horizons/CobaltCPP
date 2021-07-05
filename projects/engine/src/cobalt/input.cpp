#include <cobalt/input.hpp>

namespace cobalt
{
    KeyState Input::sKeyStates[COBALT_KEY_LAST];
    KeyState Input::sKeyLastState[COBALT_KEY_LAST];

    bool Input::isKeyDown(const uint32_t aKeyCode)
    {
        return sKeyStates[aKeyCode] == KeyState::Down || sKeyStates[aKeyCode] == KeyState::Pressed;
    }

    bool Input::isKeyPressed(const uint32_t aKeyCode)
    {
        return sKeyStates[aKeyCode] == KeyState::Pressed;
    }

    bool Input::isKeyUp(const uint32_t aKeyCode)
    {
        return sKeyStates[aKeyCode] == KeyState::Up;
    }

    void Input::update()
    {
        for (uint32_t i = 0; i < COBALT_KEY_LAST; i++)
        {
            if (sKeyStates[i] == KeyState::Pressed && sKeyLastState[i] == KeyState::Pressed)
            {
                sKeyStates[i] = KeyState::Down;
            }

            if (sKeyStates[i] == KeyState::Up && sKeyLastState[i] == KeyState::Up)
            {
                sKeyStates[i] = KeyState::None;
            }

            sKeyLastState[i] = sKeyStates[i];
        }
    }

    void Input::_setKeyPressed(const uint32_t aKeyCode)
    {
        if (aKeyCode < COBALT_KEY_LAST)
        {
            if (sKeyStates[aKeyCode] == KeyState::Pressed || sKeyStates[aKeyCode] == KeyState::Down)
                return;

            sKeyStates[aKeyCode] = KeyState::Pressed;
        }
    }

    void Input::_setKeyReleased(const uint32_t aKeyCode)
    {
        if (aKeyCode < COBALT_KEY_LAST)
        {
            sKeyStates[aKeyCode] = KeyState::Up;
        }
    }
}