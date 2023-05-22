#include "bn_fixed.h"
#include "bn_fixed_point.h"
#include "bn_keypad.h"
#include "bn_sprite_tiles_ptr.h"

#include "bn_sprite_items_player.h"

#include "tg_functions.hpp"
#include "tg_player.hpp"
#include "tg_projectile.hpp"

#define NORMALIZED bn::fixed(0.7071)

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

    // find new sprite index from input
    _new_sprite_index = get_sprite_index(_direction);

    // normalize direction if not on axis
    if (!is_axis(_direction))
    {
        // TODO check keypad::b_held() to add speed boost
        _direction.set_x(_direction.x() * NORMALIZED);
        _direction.set_y(_direction.y() * NORMALIZED);
    }

    // update position
    if (!bn::keypad::l_held())
    {
        sprite_ptr.set_x(sprite_ptr.x() + _direction.x());
        sprite_ptr.set_y(sprite_ptr.y() + _direction.y());
    }

    // update sprite check
    if (_new_sprite_index != -1 && _new_sprite_index != _last_sprite_index)
    {
        sprite_ptr.set_tiles(bn::sprite_items::player.tiles_item().create_tiles(_new_sprite_index));
        _last_sprite_index = _new_sprite_index;
        _facing = _direction;
    }
}

bn::fixed_point player::position()
{
    return sprite_ptr.position();
}

bn::fixed_point player::direction_moving()
{
    return _direction;
}

bn::fixed_point player::direction_facing()
{
    return _facing;
}
