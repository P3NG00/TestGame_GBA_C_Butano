#ifndef TG_PROJECTILE_HPP
#define TG_PROJECTILE_HPP

#include "bn_fixed.h"
#include "bn_fixed_point.h"
#include "bn_sprite_ptr.h"

#include "bn_sprite_items_projectile.h"

#include "tg_entity.hpp"
#include "tg_functions.hpp"

class projectile : public entity
{
public:
    projectile();
    void set(bn::fixed_point position, bn::fixed_point direction);
    void update();
};

#endif
