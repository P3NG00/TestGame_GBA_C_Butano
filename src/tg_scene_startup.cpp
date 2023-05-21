#include "bn_blending.h"
#include "bn_blending_actions.h"
#include "bn_core.h"
#include "bn_keypad.h"

#include "tg_scene_startup.hpp"

void scene_startup::execute()
{
    // setup fade in from white
    bn::blending::set_fade_alpha(1);
    bn::blending::set_fade_color(bn::blending::fade_color_type::WHITE);
    bn::blending_fade_alpha_to_action fade_in_from_white(seconds_to_frames(1), 0);
    _bg_logo.set_blending_enabled(true);
    _sprite_signature.set_blending_enabled(true);

    // run fade in from white
    while (!bn::keypad::start_pressed() && _counter > seconds_to_frames(4))
    {
        _counter -= 1;
        fade_in_from_white.update();
        bn::core::update();
    }

    // stall for a bit
    while (!bn::keypad::start_pressed() && _counter > seconds_to_frames(2))
    {
        _counter -= 1;
        bn::core::update();
    }

    // setup signature fade out
    bn::blending::set_fade_alpha(0);
    bn::blending::set_fade_color(bn::blending::fade_color_type::BLACK);
    bn::blending_fade_alpha_to_action fade_out(seconds_to_frames(1), 1);
    _bg_logo.set_blending_enabled(false);

    // run signature fade out
    while (!bn::keypad::start_pressed() && _counter > seconds_to_frames(1))
    {
        _counter -= 1;
        fade_out.update();
        bn::core::update();
    }

    // setup logo fade out
    bn::blending::set_fade_alpha(0);
    fade_out.reset();
    _bg_logo.set_blending_enabled(true);
    _sprite_signature.set_visible(false);

    // run logo fade out
    while (!bn::keypad::start_pressed() && _counter > 0)
    {
        _counter -= 1;
        fade_out.update();
        bn::core::update();
    }

    bn::blending::set_fade_alpha(0);
}
