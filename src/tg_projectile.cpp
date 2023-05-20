#include "bn_fixed.h"

#include "tg_projectile.hpp"

projectile::projectile()
{
    // _sprite_ptr.set_visible(false); TODO
}

void projectile::set(bn::fixed x, bn::fixed y, int dx, int dy)
{
    _sprite_ptr.set_position(x, y);
    _dx = dx;
    _dy = dy;
}

void projectile::update()
{
    _sprite_ptr.set_x(_sprite_ptr.x() + _dx);
    _sprite_ptr.set_y(_sprite_ptr.y() + _dy);
}
