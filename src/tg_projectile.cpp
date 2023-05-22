#include "bn_fixed.h"

#include "tg_projectile.hpp"

projectile::projectile()
{
    sprite.set_visible(false);
}

void projectile::set(bn::fixed_point position, bn::fixed_point direction)
{
    sprite.set_visible(true);
    sprite.set_position(position);
    _direction = direction;
    _life = seconds_to_frames(1);
}

void projectile::update()
{
    _life -= 1;
    if (_life > 0)
        sprite.set_position(sprite.position() + _direction);
    else
        sprite.set_visible(false);
}
