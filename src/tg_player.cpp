#include "bn_keypad.h"
#include "bn_sprite_tiles_ptr.h"

#include "bn_sprite_items_player.h"

#include "tg_player.hpp"
#include "tg_projectile.hpp"

#define NORMALIZED 0.7071

void player::handle_input(projectile* projectile_obj)
{
    // player movement
    _dx = 0;
    _dy = 0;
    if (bn::keypad::up_held())
        _dy -= 1;
    if (bn::keypad::down_held())
        _dy += 1;
    if (bn::keypad::left_held())
        _dx -= 1;
    if (bn::keypad::right_held())
        _dx += 1;

    // find sprite index
    _new_sprite_index = -1;
    if      (_dx ==  0 && _dy == -1)
        _new_sprite_index = 0;
    else if (_dx ==  1 && _dy == -1)
    {
        _new_sprite_index = 1;
        _dx = NORMALIZED;
        _dy = -NORMALIZED;
    }
    else if (_dx ==  1 && _dy ==  0)
        _new_sprite_index = 2;
    else if (_dx ==  1 && _dy ==  1)
    {
        _new_sprite_index = 3;
        _dx = NORMALIZED;
        _dy = NORMALIZED;
    }
    else if (_dx ==  0 && _dy ==  1)
        _new_sprite_index = 4;
    else if (_dx == -1 && _dy ==  1)
    {
        _new_sprite_index = 5;
        _dx = -NORMALIZED;
        _dy = NORMALIZED;
    }
    else if (_dx == -1 && _dy ==  0)
        _new_sprite_index = 6;
    else if (_dx == -1 && _dy == -1)
    {
        _new_sprite_index = 7;
        _dx = -NORMALIZED;
        _dy = -NORMALIZED;
    }

    // update position
    if (!bn::keypad::l_held())
    {
        _sprite_ptr.set_x(_sprite_ptr.x() + _dx);
        _sprite_ptr.set_y(_sprite_ptr.y() + _dy);
    }

    // update sprite check
    if (_new_sprite_index != -1 && _new_sprite_index != _last_sprite_index)
    {
        _sprite_ptr.set_tiles(bn::sprite_items::player.tiles_item().create_tiles(_new_sprite_index));
        _last_sprite_index = _new_sprite_index;
    }

    // check player shooting
    if (bn::keypad::a_pressed())
    {
        projectile_obj->set(_sprite_ptr.x(), _sprite_ptr.y(), _dx * 3, _dy * 3);
    }
}