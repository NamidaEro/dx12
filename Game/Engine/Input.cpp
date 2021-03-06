#include "pch.h"
#include "Input.h"

void Input::Init(HWND hwnd)
{
    _hwnd = hwnd;
    _states.resize(KEY_TYPE_COUNT, KEY_STATE::NONE);
}

void Input::Update()
{
    HWND hwnd = ::GetActiveWindow();
    if(_hwnd != hwnd )
    {
        for(KEY_STATE& key : _states)
        {
            key = KEY_STATE::NONE;
        }

        return;
    }

    BYTE asciiKeys[KEY_TYPE_COUNT] = {};
    if (::GetKeyboardState(asciiKeys) == false) { return; }

    for(uint32 key = 0; key < KEY_TYPE_COUNT; ++key)
    {
        if(::GetAsyncKeyState(key) & 0x8000)
        {
            KEY_STATE& state = _states[key];

            if(state == KEY_STATE::PRESS || state == KEY_STATE::DOWN)
            {
                state = KEY_STATE::PRESS;
            }
            else
            {
                state = KEY_STATE::DOWN;
            }
        }
        else
        {
            KEY_STATE& state = _states[key];

            if (state == KEY_STATE::PRESS || state == KEY_STATE::DOWN)
            {
                state = KEY_STATE::UP;
            }
            else
            {
                state = KEY_STATE::NONE;
            }
        }
    }

}
