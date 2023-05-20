#include "bn_keypad.h"

#include "tg_scene_level_test.hpp"

void scene_level_test::update()
{
    _player_obj.handle_input();

    // check player shooting
    bool create_projectile = bn::keypad::a_pressed();

    for (int i = 0; i < PROJECTILE_AMOUNT; i++)
    {
        if (!_projectile_obj_array[i].active())
        {
            if (create_projectile)
            {
                _projectile_obj_array[i].set(_player_obj.position(), _player_obj.direction() * 3);
                create_projectile = false;
            }
            continue;
        }

        _projectile_obj_array[i].update();
    }
}
