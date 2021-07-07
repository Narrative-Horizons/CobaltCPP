#include <cobalt/input.hpp>

namespace cobalt
{
    KeyState Input::_sKeyStates[COBALT_KEY_LAST];
    KeyState Input::_sKeyLastState[COBALT_KEY_LAST];

    bool Input::isKeyDown(const uint32_t aKeyCode)
    {
        return _sKeyStates[aKeyCode] == KeyState::Down || _sKeyStates[aKeyCode] == KeyState::Pressed;
    }

    bool Input::isKeyPressed(const uint32_t aKeyCode)
    {
        return _sKeyStates[aKeyCode] == KeyState::Pressed;
    }

    bool Input::isKeyUp(const uint32_t aKeyCode)
    {
        return _sKeyStates[aKeyCode] == KeyState::Up;
    }

    void Input::update()
    {
        for (uint32_t i = 0; i < COBALT_KEY_LAST; i++)
        {
            if (_sKeyStates[i] == KeyState::Pressed && _sKeyLastState[i] == KeyState::Pressed)
            {
                _sKeyStates[i] = KeyState::Down;
            }

            if (_sKeyStates[i] == KeyState::Up && _sKeyLastState[i] == KeyState::Up)
            {
                _sKeyStates[i] = KeyState::None;
            }

            _sKeyLastState[i] = _sKeyStates[i];
        }
    }

    void Input::_setKeyPressed(const uint32_t aKeyCode)
    {
        if (aKeyCode < COBALT_KEY_LAST)
        {
            if (_sKeyStates[aKeyCode] == KeyState::Pressed || _sKeyStates[aKeyCode] == KeyState::Down)
                return;

            _sKeyStates[aKeyCode] = KeyState::Pressed;
        }
    }

    void Input::_setKeyReleased(const uint32_t aKeyCode)
    {
        if (aKeyCode < COBALT_KEY_LAST)
        {
            _sKeyStates[aKeyCode] = KeyState::Up;
        }
    }
}