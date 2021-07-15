#include <cobalt/input.hpp>

namespace cobalt
{
    KeyState Input::_sKeyStates[COBALT_KEY_LAST];
    KeyState Input::_sKeyLastState[COBALT_KEY_LAST];

    KeyState Input::_sMouseStates[COBALT_MOUSE_BUTTON_LAST];
    KeyState Input::_sMouseLastState[COBALT_MOUSE_BUTTON_LAST];

    int32_t Input::_mouseX = 0.0f;
    int32_t Input::_mouseY = 0.0f;
	
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

    bool Input::isMouseDown(const uint32_t aKeyCode)
    {
        return _sMouseStates[aKeyCode] == KeyState::Down || _sMouseStates[aKeyCode] == KeyState::Pressed;
    }

    bool Input::isMousePressed(const uint32_t aKeyCode)
    {
        return _sMouseStates[aKeyCode] == KeyState::Pressed;
    }

    bool Input::isMouseUp(const uint32_t aKeyCode)
    {
        return _sMouseStates[aKeyCode] == KeyState::Up;
    }

    void Input::getMousePosition(int32_t* x, int32_t* y)
    {
        *x = _mouseX;
        *y = _mouseY;
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

        for (uint32_t i = 0; i < COBALT_MOUSE_BUTTON_LAST; i++)
        {
            if (_sMouseStates[i] == KeyState::Pressed && _sMouseLastState[i] == KeyState::Pressed)
            {
                _sMouseStates[i] = KeyState::Down;
            }

            if (_sMouseStates[i] == KeyState::Up && _sMouseLastState[i] == KeyState::Up)
            {
                _sMouseStates[i] = KeyState::None;
            }

            _sMouseLastState[i] = _sMouseStates[i];
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

    void Input::_setMousePressed(const uint32_t aKeyCode)
    {
    	if(aKeyCode < COBALT_MOUSE_BUTTON_LAST)
    	{
            _sMouseStates[aKeyCode] = KeyState::Pressed;
    	}
    }

    void Input::_setMouseReleased(const uint32_t aKeyCode)
    {
        if (aKeyCode < COBALT_MOUSE_BUTTON_LAST)
        {
            _sMouseStates[aKeyCode] = KeyState::Up;
        }
    }

    void Input::_setMousePosition(const float x, const float y)
    {
        _mouseX = x;
        _mouseY = y;
    }
}
