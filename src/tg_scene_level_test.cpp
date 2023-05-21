#include "bn_blending.h"
#include "bn_core.h"
#include "bn_keypad.h"

#include "tg_scene_level_test.hpp"

void scene_level_test::execute()
{
    // handle fade in
    bn::blending::set_fade_alpha(1);
    _player_obj.sprite_ptr.set_blending_enabled(true);
    bn::blending_fade_alpha_to_action fade_in(seconds_to_frames(1), 0);

    while (!fade_in.done())
    {
        fade_in.update();
        bn::core::update();
    }

    _player_obj.sprite_ptr.set_blending_enabled(false);

    // loop
    while (true)
    {
        // handle player input
        _player_obj.handle_input();

        // check player shooting
        bool create_projectile = bn::keypad::a_pressed();

        // update projectiles
        for (int i = 0; i < PROJECTILE_AMOUNT; i++)
        {
            // check active
            if (!_projectile_obj_array[i].active())
            {
                // create projectile
                if (create_projectile)
                {
                    bn::fixed_point direction = _player_obj.direction() * 3;
                    _projectile_obj_array[i].set(_player_obj.position() + direction, direction);
                    create_projectile = false;
                }

                continue;
            }

            // update projectile
            _projectile_obj_array[i].update();
        }

        // update engine last
        bn::core::update();
    }
}
