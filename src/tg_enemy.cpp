#include "bn_fixed.h"
#include "bn_fixed_point.h"
#include "bn_sprite_tiles_ptr.h"

#include "bn_sprite_items_enemy.h"

#include "tg_enemy.hpp"
#include "tg_functions.hpp"

enemy::enemy()
{
    sprite.set_visible(false);
}

void enemy::update(bn::fixed_point player_position)
{
    // get direction
    bn::fixed_point direction = normalize(player_position - sprite.position());

    // update position
    sprite.set_position(sprite.position() + (direction / 4)); // TODO adjust speed

    // find sprite index
    bn::fixed_point rounded_direction = bn::fixed_point(direction.x().round_integer(), direction.y().round_integer());
    _new_sprite_index = get_sprite_index(rounded_direction);

    // update sprite check
    if (_new_sprite_index != -1 && _new_sprite_index != _last_sprite_index)
    {
        sprite.set_tiles(bn::sprite_items::enemy.tiles_item().create_tiles(_new_sprite_index));
        _last_sprite_index = _new_sprite_index;
        _facing = _direction;
    }
}

void enemy::set(bn::fixed_point position)
{
    sprite.set_position(position);
    sprite.set_visible(true);
}

bn::fixed_point enemy::position()
{
    return sprite.position();
}
