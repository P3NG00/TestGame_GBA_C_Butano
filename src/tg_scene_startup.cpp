#include "tg_scene_startup.hpp"

void scene_startup::execute()
{
    bn::fixed counter = seconds_to_frames(5);
    bn::regular_bg_ptr bg_logo = bn::regular_bg_items::p3.create_bg(-16, -16);
    bn::sprite_ptr sprite_signature = bn::sprite_items::signature.create_sprite(48, 48);

    // setup fade in from white
    bn::blending::set_fade_alpha(1);
    bn::blending::set_fade_color(bn::blending::fade_color_type::WHITE);
    bn::blending_fade_alpha_to_action fade_in_from_white(seconds_to_frames(1), 0);
    bg_logo.set_blending_enabled(true);
    sprite_signature.set_blending_enabled(true);

    // run fade in from white
    while (!bn::keypad::start_pressed() && counter > seconds_to_frames(4))
    {
        counter -= 1;
        fade_in_from_white.update();
        bn::core::update();
    }

    // stall for a bit
    while (!bn::keypad::start_pressed() && counter > seconds_to_frames(2))
    {
        counter -= 1;
        bn::core::update();
    }

    // setup signature fade out
    bn::blending::set_fade_alpha(0);
    bn::blending::set_fade_color(bn::blending::fade_color_type::BLACK);
    bn::blending_fade_alpha_to_action fade_out(seconds_to_frames(1), 1);
    bg_logo.set_blending_enabled(false);

    // run signature fade out
    while (!bn::keypad::start_pressed() && counter > seconds_to_frames(1))
    {
        counter -= 1;
        fade_out.update();
        bn::core::update();
    }

    // setup fade to white
    bn::blending::set_fade_alpha(0);
    fade_out.reset();
    bn::blending::set_fade_color(bn::blending::fade_color_type::WHITE);
    bg_logo.set_blending_enabled(true);
    sprite_signature.set_visible(false);

    // run logo fade out
    while (!bn::keypad::start_pressed() && counter > 0)
    {
        counter -= 1;
        fade_out.update();
        bn::core::update();
    }
}
