#include "bn_blending.h"
#include "bn_blending_actions.h"
#include "bn_core.h"
#include "bn_keypad.h"

#include "tg_player.hpp"
#include "tg_projectile.hpp"
#include "tg_scene_level_test.hpp"
#include "tg_text_handler.hpp"

#define PROJECTILE_AMOUNT 8

void scene_level_test::execute()
{
    projectile projectile_obj_array[PROJECTILE_AMOUNT];
    text_handler text_handler_obj = text_handler();
    player player_obj = player();

    // handle fade in
    bn::blending::set_fade_alpha(1);
    player_obj.sprite_ptr.set_blending_enabled(true);
    bn::blending_fade_alpha_to_action fade_in(seconds_to_frames(1), 0);

    while (!fade_in.done())
    {
        fade_in.update();
        bn::core::update();
    }

    player_obj.sprite_ptr.set_blending_enabled(false);

    // loop
    while (true)
    {
        // handle player input
        player_obj.handle_input();

        // check player shooting
        bool create_projectile = bn::keypad::a_pressed();

        // update projectiles
        for (int i = 0; i < PROJECTILE_AMOUNT; i++)
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
