#include "bn_fixed.h"

#include "tg_projectile.hpp"

projectile::projectile()
{
    _set_active(false);
}

void projectile::set(bn::fixed_point position, bn::fixed_point direction)
{
    _set_active(true);
    _sprite_ptr.set_position(position);
    _direction = direction;
    _life = seconds_to_frames(1);
}

void projectile::update()
{
    _life -= 1;
    if (_life > 0)
        _sprite_ptr.set_position(_sprite_ptr.position() + _direction);
    else
        _set_active(false);
}

bool projectile::active()
{
    return _sprite_ptr.visible();
}

void projectile::_set_active(bool active)
{
    _sprite_ptr.set_visible(active);
}
