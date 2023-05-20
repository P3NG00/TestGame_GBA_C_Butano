#ifndef TG_PROJECTILE_HPP
#define TG_PROJECTILE_HPP

#include "bn_fixed.h"
#include "bn_sprite_ptr.h"

#include "bn_sprite_items_projectile.h"

class projectile
{
    bn::sprite_ptr _sprite_ptr = bn::sprite_items::projectile.create_sprite(0, 0);
    bn::fixed _dx = 0;
    bn::fixed _dy = 0;
    // TODO implement life value

public:

    projectile();
    void set(bn::fixed x, bn::fixed y, bn::fixed dx, bn::fixed dy);
    void update();
};

#endif
