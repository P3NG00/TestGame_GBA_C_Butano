#include "bn_blending.h"
#include "bn_blending_actions.h"
#include "bn_core.h"
#include "bn_keypad.h"

#include "tg_scene_startup.hpp"

void scene_startup::execute()
{
    _bg_logo.set_blending_enabled(true);
    bn::fixed time_fade = seconds_to_frames(1);
    bn::blending_fade_alpha_to_action fade_in_action(seconds_to_frames(1), 1);

    while (_counter > 0 && !bn::keypad::start_pressed())
    {
        _counter -= 1;

        if (_counter < time_fade)
        {
            fade_in_action.update();
        }

        bn::core::update();
    }

    bn::blending::set_fade_alpha(0);
}
