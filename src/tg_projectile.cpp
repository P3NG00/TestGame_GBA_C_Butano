#include "bn_fixed.h"

#include "tg_projectile.hpp"

projectile::projectile()
{
    _sprite_ptr.set_visible(false);
}

void projectile::set(bn::fixed_point position, bn::fixed_point direction)
{
    _sprite_ptr.set_visible(true);
    _sprite_ptr.set_position(position);
    _direction = direction;
}

void projectile::update()
{
    if (!active())
        return;
    _sprite_ptr.set_position(_sprite_ptr.position() + _direction);
}

bool projectile::active()
{
    return _sprite_ptr.visible();
}
