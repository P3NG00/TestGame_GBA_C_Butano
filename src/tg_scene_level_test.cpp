#include "bn_affine_bg_ptr.h"
#include "bn_array.h"
#include "bn_blending.h"
#include "bn_blending_actions.h"
#include "bn_camera_ptr.h"
#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_sprite_ptr.h"

#include "bn_affine_bg_items_bg_1.h"
#include "bn_affine_bg_items_bg_2.h"
#include "bn_sprite_items_target.h"

#include "tg_constants.hpp"
#include "tg_enemy.hpp"
#include "tg_functions.hpp"
#include "tg_player.hpp"
#include "tg_projectile.hpp"
#include "tg_scene_level_test.hpp"
#include "tg_text_handler.hpp"

#define PROJECTILE_AMOUNT 8
#define BACKGROUND_AMOUNT 2
#define ENEMY_AMOUNT 8
#define CAMERA_OFFSET_DISTANCE 20
// used as 1 / CAMERA_OFFSET_DIV_LERP to smoothly move camera towards desired position
#define CAMERA_OFFSET_DIV_LERP 20
#define TARGET_DISTANCE 60

void scene_level_test::execute()
{
    // setup variables
    unsigned int i;
    unsigned short int bg_index = 0;
    bn::fixed_point camera_offset;
    bn::fixed_point last_camera_offset;
    bn::camera_ptr camera_obj = bn::camera_ptr::create(0, 0);
    bn::camera_ptr camera_bg_1 = bn::camera_ptr::create(0, 0);
    bn::camera_ptr camera_bg_2 = bn::camera_ptr::create(0, 0);
    bn::array<projectile, PROJECTILE_AMOUNT> projectile_obj_array;
    bn::array<enemy, ENEMY_AMOUNT> enemy_obj_array; // TODO implement collision
    bn::array<bn::affine_bg_ptr, BACKGROUND_AMOUNT> bg_obj_array = {
        bn::affine_bg_items::bg_1.create_bg(0, 0),
        bn::affine_bg_items::bg_2.create_bg(0, 0)
    };
    text_handler text_handler_obj = text_handler();
    player player_obj = player();
    player_obj.sprite.set_camera(camera_obj);
    bn::sprite_ptr target_sprite = bn::sprite_items::target.create_sprite(0, 0);
    target_sprite.set_camera(camera_obj);
    target_sprite.set_visible(false);
    bool spawn_enemy;
    bool shoot_projectile;

    // increase scale of every other background
    for (i = 0; i < BACKGROUND_AMOUNT; i++)
    {
        bg_obj_array[i].set_blending_enabled(true);
        if (i % 2 == 0)
            bg_obj_array[i].set_camera(camera_bg_2);
        else
        {
            bg_obj_array[i].set_camera(camera_bg_1);
            bg_obj_array[i].set_scale(2);
        }
    }
    // set camera for projectiles
    for (i = 0; i < PROJECTILE_AMOUNT; i++)
        projectile_obj_array[i].sprite.set_camera(camera_obj);
    // set camera for enemies
    for (i = 0; i < ENEMY_AMOUNT; i++)
        enemy_obj_array[i].sprite.set_camera(camera_obj);

    // setup fade in
    bn::blending::set_fade_color(bn::blending::fade_color_type::WHITE);
    bn::blending::set_fade_alpha(1);
    bn::blending_fade_alpha_to_action fade_in(seconds_to_frames(1), 0);

    // handle fade in
    while (!fade_in.done())
    {
        fade_in.update();
        bn::core::update();
    }

    // setup background fading
    bn::blending::set_fade_color(bn::blending::fade_color_type::BLACK);
    bn::blending_fade_alpha_to_action fade_out(seconds_to_frames(3), 1);
    // change fade alpha temporarily to setup fade in action
    bn::blending::set_fade_alpha(1);
    fade_in = bn::blending_fade_alpha_to_action(seconds_to_frames(1.5), 0);
    bn::blending::set_fade_alpha(0);
    // disable blending for all backgrounds other than first
    for (i = 1; i < BACKGROUND_AMOUNT; i++)
        bg_obj_array[i].set_blending_enabled(false);

    // enable target sprite
    target_sprite.set_visible(true);

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

        // spawn enemy
        // TODO handle enemy random spawning
        spawn_enemy = bn::keypad::select_pressed();
        for (i = 0; i < ENEMY_AMOUNT; i++)
        {
            if (enemy_obj_array[i].sprite.visible())
                enemy_obj_array[i].update(player_obj.position());
            else if (spawn_enemy)
            {
                enemy_obj_array[i].set(player_obj.position());
                spawn_enemy = false;
            }
        }

        // check player shooting
        shoot_projectile = bn::keypad::r_pressed();

        // update projectiles
        for (i = 0; i < PROJECTILE_AMOUNT; i++)
        {
            if (projectile_obj_array[i].sprite.visible())
                projectile_obj_array[i].update();
            else if (shoot_projectile)
            {
                bn::fixed_point direction = player_obj.direction_facing() * 3;
                projectile_obj_array[i].set(player_obj.position() + direction, direction);
                shoot_projectile = false;
            }
        }

        // update camera
        camera_offset = player_obj.direction_moving() * CAMERA_OFFSET_DISTANCE;
        // linearly interpolate towards desired position
        camera_offset = last_camera_offset + ((camera_offset - last_camera_offset) / CAMERA_OFFSET_DIV_LERP);
        // update last true camera offset before rounding
        last_camera_offset = camera_offset;
        // round camera offset if player is not moving on an axis to avoid bumpiness
        camera_offset.set_x(camera_offset.x().round_integer());
        camera_offset.set_y(camera_offset.y().round_integer());
        // update camera position
        camera_obj.set_position(player_obj.position() + camera_offset);
        camera_bg_1.set_position(camera_obj.position() / 2);
        camera_bg_2.set_position(camera_bg_1.position() / 2);

        // update target sprite position
        target_sprite.set_x(player_obj.position().x() + (player_obj.direction_facing().x() * TARGET_DISTANCE).round_integer());
        target_sprite.set_y(player_obj.position().y() + (player_obj.direction_facing().y() * TARGET_DISTANCE).round_integer());

        // update engine last
        bn::core::update();
    }
}
