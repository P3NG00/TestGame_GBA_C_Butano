#include "bn_fixed_point.h"

#include "tg_enemy.hpp"

enemy::enemy()
{
    sprite.set_visible(false);
}

void enemy::update(bn::fixed_point player_position)
{
    // TODO move towards player's position
}

void enemy::set(bn::fixed_point position)
{
    sprite.set_position(position);
    sprite.set_visible(true);
}
