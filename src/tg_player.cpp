#include "bn_keypad.h"
#include "bn_sprite_tiles_ptr.h"

#include "bn_sprite_items_player.h"

#include "tg_player.hpp"
#include "tg_projectile.hpp"

#define NORMALIZED 0.7071

void player::handle_input()
{
    // player movement
    _direction.set_x(0);
    _direction.set_y(0);
    if (bn::keypad::up_held())
        _direction.set_y(_direction.y() - 1);
    if (bn::keypad::down_held())
        _direction.set_y(_direction.y() + 1);
    if (bn::keypad::left_held())
        _direction.set_x(_direction.x() - 1);
    if (bn::keypad::right_held())
        _direction.set_x(_direction.x() + 1);

    // find sprite index
    _new_sprite_index = -1;
    if      (_direction.x() ==  0 && _direction.y() == -1)
    {
        _new_sprite_index = 0;
    }
    else if (_direction.x() ==  1 && _direction.y() == -1)
    {
        _new_sprite_index = 1;
        _direction.set_x(NORMALIZED);
        _direction.set_y(-NORMALIZED);
    }
    else if (_direction.x() ==  1 && _direction.y() ==  0)
    {
        _new_sprite_index = 2;
    }
    else if (_direction.x() ==  1 && _direction.y() ==  1)
    {
        _new_sprite_index = 3;
        _direction.set_x(NORMALIZED);
        _direction.set_y(NORMALIZED);
    }
    else if (_direction.x() ==  0 && _direction.y() ==  1)
    {
        _new_sprite_index = 4;
    }
    else if (_direction.x() == -1 && _direction.y() ==  1)
    {
        _new_sprite_index = 5;
        _direction.set_x(-NORMALIZED);
        _direction.set_y(NORMALIZED);
    }
    else if (_direction.x() == -1 && _direction.y() ==  0)
    {
        _new_sprite_index = 6;
    }
    else if (_direction.x() == -1 && _direction.y() == -1)
    {
        _new_sprite_index = 7;
        _direction.set_x(-NORMALIZED);
        _direction.set_y(-NORMALIZED);
    }

    // update position
    if (!bn::keypad::l_held())
    {
        _sprite_ptr.set_x(_sprite_ptr.x() + _direction.x());
        _sprite_ptr.set_y(_sprite_ptr.y() + _direction.y());
    }

    // update sprite check
    if (_new_sprite_index != -1 && _new_sprite_index != _last_sprite_index)
    {
        _sprite_ptr.set_tiles(bn::sprite_items::player.tiles_item().create_tiles(_new_sprite_index));
        _last_sprite_index = _new_sprite_index;
        _last_direction = _direction;
    }
}

bn::fixed_point player::position()
{
    return _sprite_ptr.position();
}

bn::fixed_point player::direction()
{
    return _last_direction;
}
