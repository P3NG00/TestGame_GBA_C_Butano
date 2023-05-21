#include "bn_keypad.h"

#include "tg_scene_level_test.hpp"

scene_level_test::scene_level_test()
{
    _player_obj.sprite_ptr.set_blending_enabled(true);
}

void scene_level_test::update()
{
    // handle fade in
    if (!_fade_in.done())
    {
        _fade_in.update();
        return;
    }

    _player_obj.handle_input();

    // check player shooting
    bool create_projectile = bn::keypad::a_pressed();

    for (int i = 0; i < PROJECTILE_AMOUNT; i++)
    {
        if (!_projectile_obj_array[i].active())
        {
            if (create_projectile)
            {
                bn::fixed_point direction = _player_obj.direction() * 3;
                _projectile_obj_array[i].set(_player_obj.position() + direction, direction);
                create_projectile = false;
            }

            continue;
        }

        _projectile_obj_array[i].update();
    }
}
