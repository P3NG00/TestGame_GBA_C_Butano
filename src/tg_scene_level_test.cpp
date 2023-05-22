#include "bn_affine_bg_ptr.h"
#include "bn_array.h"
#include "bn_blending.h"
#include "bn_blending_actions.h"
#include "bn_camera_ptr.h"
#include "bn_core.h"
#include "bn_keypad.h"

#include "bn_affine_bg_items_bg_1.h"
#include "bn_affine_bg_items_bg_2.h"

#include "tg_functions.hpp"
#include "tg_player.hpp"
#include "tg_projectile.hpp"
#include "tg_scene_level_test.hpp"
#include "tg_text_handler.hpp"

#define PROJECTILE_AMOUNT 8
#define BACKGROUND_AMOUNT 2

void scene_level_test::execute()
{
    unsigned int i;
    bn::fixed_point camera_offset;
    bn::fixed_point last_camera_offset;
    bn::camera_ptr camera_obj = bn::camera_ptr::create(0, 0);
    bn::array<bn::affine_bg_ptr, BACKGROUND_AMOUNT> bg_obj_array = {
        bn::affine_bg_items::bg_1.create_bg(0, 0),
        bn::affine_bg_items::bg_2.create_bg(0, 0),
    };
    bn::array<projectile, PROJECTILE_AMOUNT> projectile_obj_array;
    for (i = 0; i < PROJECTILE_AMOUNT; i++)
        projectile_obj_array[i].sprite_ptr.set_camera(camera_obj);
    text_handler text_handler_obj = text_handler();
    player player_obj = player();
    player_obj.sprite_ptr.set_camera(camera_obj);

    // setup fade in
    bn::blending::set_fade_color(bn::blending::fade_color_type::WHITE);
    bn::blending::set_fade_alpha(1);
    bn::blending_fade_alpha_to_action fade_in(seconds_to_frames(1), 0);
    for (i = 0; i < BACKGROUND_AMOUNT; i++)
    {
        bg_obj_array[i].set_camera(camera_obj);
        bg_obj_array[i].set_blending_enabled(true);
    }

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
    for (i = 1; i < BACKGROUND_AMOUNT; i++)
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
            if (projectile_obj_array[i].sprite_ptr.visible())
            {
                projectile_obj_array[i].update();
            }
            else if (create_projectile)
            {
                bn::fixed_point direction = player_obj.direction_facing() * 3;
                projectile_obj_array[i].set(player_obj.position() + direction, direction);
                create_projectile = false;
            }
        }

        // update camera
        camera_offset = player_obj.direction_moving() * 40;
        camera_offset = last_camera_offset + ((camera_offset - last_camera_offset) / 10);
        // update last true camera offset before rounding it just for this frame
        last_camera_offset = camera_offset;
        // round camera offset if player is not moving on an axis to avoid bumpiness
        if (!is_axis(player_obj.direction_moving()))
        {
            camera_offset.set_x(camera_offset.x().round_integer());
            camera_offset.set_y(camera_offset.y().round_integer());
        }
        // update camera position
        camera_obj.set_position(player_obj.position() + camera_offset);

        // update engine last
        bn::core::update();
    }
}
