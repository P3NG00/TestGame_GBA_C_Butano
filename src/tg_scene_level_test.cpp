#include "bn_affine_bg_ptr.h"
#include "bn_blending.h"
#include "bn_blending_actions.h"
#include "bn_core.h"
#include "bn_keypad.h"

#include "bn_affine_bg_items_bg_1.h"
#include "bn_affine_bg_items_bg_2.h"

#include "tg_player.hpp"
#include "tg_projectile.hpp"
#include "tg_scene_level_test.hpp"
#include "tg_text_handler.hpp"

#define PROJECTILE_AMOUNT 8

void scene_level_test::execute()
{
    unsigned int i;
    bn::affine_bg_ptr bg_obj_array[] = {
        bn::affine_bg_items::bg_1.create_bg(0, 0),
        bn::affine_bg_items::bg_2.create_bg(0, 0),
    };
    projectile projectile_obj_array[PROJECTILE_AMOUNT];
    text_handler text_handler_obj = text_handler();
    player player_obj = player();

    // setup fade in
    bn::blending::set_fade_color(bn::blending::fade_color_type::WHITE);
    bn::blending::set_fade_alpha(1);
    bn::blending_fade_alpha_to_action fade_in(seconds_to_frames(1), 0);
    for (i = 0; i < sizeof(bg_obj_array) / sizeof(bg_obj_array[0]); i++)
        bg_obj_array[i].set_blending_enabled(true);

    // handle fade in
    while (!fade_in.done())
    {
        fade_in.update();
        bn::core::update();
    }

    // setup background fading
    bn::blending::set_fade_color(bn::blending::fade_color_type::BLACK);
    unsigned short int bg_index = 0;
    bn::blending_fade_alpha_to_action fade_out(seconds_to_frames(3), 1);
    // change fade alpha temporarily to setup fade in action
    bn::blending::set_fade_alpha(1);
    fade_in = bn::blending_fade_alpha_to_action(seconds_to_frames(3), 0);
    bn::blending::set_fade_alpha(0);
    // disable blending for all backgrounds other than first
    for (i = 1; i < sizeof(bg_obj_array) / sizeof(bg_obj_array[0]); i++)
        bg_obj_array[i].set_blending_enabled(false);

    // loop
    while (true)
    {
        // update background fading
        if (!fade_out.done())
        {
            fade_out.update();
            if (fade_out.done())
                fade_in.reset();
        }
        else
        {
            fade_in.update();
            if (fade_in.done())
            {
                bg_obj_array[bg_index].set_blending_enabled(false);
                bg_index = (bg_index + 1) % 2;
                bg_obj_array[bg_index].set_blending_enabled(true);
                fade_out.reset();
            }
        }

        // handle player input
        player_obj.handle_input();

        // check player shooting
        bool create_projectile = bn::keypad::a_pressed();

        // update projectiles
        for (i = 0; i < PROJECTILE_AMOUNT; i++)
        {
            if (projectile_obj_array[i].active())
            {
                projectile_obj_array[i].update();
            }
            else if (create_projectile)
            {
                bn::fixed_point direction = player_obj.direction() * 3;
                projectile_obj_array[i].set(player_obj.position() + direction, direction);
                create_projectile = false;
            }
        }

        // update engine last
        bn::core::update();
    }
}
