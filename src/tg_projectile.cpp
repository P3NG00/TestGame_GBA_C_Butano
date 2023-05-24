#include "tg_projectile.hpp"

projectile::projectile() :
    entity(bn::sprite_items::projectile, 4)
{
    _set_active(false);
}

void projectile::set(bn::fixed_point position, bn::fixed_point direction)
{
    _set_active(true);
    _set_position(position);
    _direction = direction;
    _life = seconds_to_frames(1);
}

void projectile::update()
{
    _life -= 1;
    if (_life > 0)
        _set_position(position() + _direction);
    else
        _set_active(false);
}
