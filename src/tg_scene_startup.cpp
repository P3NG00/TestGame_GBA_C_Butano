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
    while (_counter > seconds_to_frames(4) && !bn::keypad::start_pressed())
    {
        _counter -= 1;
        fade_in_from_white.update();
        bn::core::update();
    }

    // stall for a bit
    while (_counter > seconds_to_frames(2) && !bn::keypad::start_pressed())
    {
        _counter -= 1;
        bn::core::update();
    }

    // setup signature fade out
    bn::blending::set_fade_alpha(0);
    bn::blending::set_fade_color(bn::blending::fade_color_type::BLACK);
    bn::blending_fade_alpha_to_action fade_out_signature(seconds_to_frames(1), 1);
    _bg_logo.set_blending_enabled(false);

    // run signature fade out
    while (_counter > seconds_to_frames(1) && !bn::keypad::start_pressed())
    {
        _counter -= 1;
        fade_out_signature.update();
        bn::core::update();
    }

    // setup logo fade out
    bn::blending::set_fade_alpha(0);
    bn::blending_fade_alpha_to_action fade_out_logo(seconds_to_frames(1), 1);
    _bg_logo.set_blending_enabled(true);
    _sprite_signature.set_visible(false);

    // run logo fade out
    while (_counter > 0 && !bn::keypad::start_pressed())
    {
        _counter -= 1;
        fade_out_logo.update();
        bn::core::update();
    }

    // don't update bn::blending::set_fade_alpha(0) here, from where it left off will be used in the next scene
}
