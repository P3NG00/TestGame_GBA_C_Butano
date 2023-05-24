#include "bn_fixed.h"
#include "bn_fixed_point.h"
#include "bn_sprite_tiles_ptr.h"

#include "bn_sprite_items_enemy.h"

#include "tg_enemy.hpp"
#include "tg_functions.hpp"

enemy::enemy() :
    entity(bn::sprite_items::enemy)
{
    _set_active(false);
}

void enemy::update(bn::fixed_point player_position)
{
    // get direction
    _direction = normalize(player_position - position());

    // update position before rounding
    _set_position(position() + (_direction / 4)); // TODO adjust speed

    // round direction
    _direction.set_x(_direction.x().round_integer());
    _direction.set_y(_direction.y().round_integer());

    // update sprite index
    _update_sprite_index();

    // update sprite
    _update_sprite();
}

void enemy::set(bn::fixed_point position)
{
    _set_position(position);
    _set_active(true);
}
