#ifndef TG_PROJECTILE_HPP
#define TG_PROJECTILE_HPP

#include "bn_fixed_point.h"
#include "bn_sprite_ptr.h"

#include "bn_sprite_items_projectile.h"

#include "tg_functions.hpp"

class projectile
{
    bn::sprite_ptr _sprite_ptr = bn::sprite_items::projectile.create_sprite(0, 0);
    bn::fixed_point _direction = bn::fixed_point(0, 0);
    bn::fixed _life;

    void _set_active(bool active);

public:

    projectile();
    void set(bn::fixed_point position, bn::fixed_point direction);
    void update();
    bool active();
};

#endif
