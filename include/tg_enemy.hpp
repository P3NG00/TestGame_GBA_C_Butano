#ifndef TG_ENEMY_HPP
#define TG_ENEMY_HPP

#include "bn_camera_ptr.h"
#include "bn_fixed.h"
#include "bn_fixed_point.h"
#include "bn_sprite_ptr.h"

#include "bn_sprite_items_enemy.h"

#include "tg_entity.hpp"

class enemy : public entity
{
public:
    enemy();
    void update(bn::fixed_point player_position);
    void set(bn::fixed_point position);
};

#endif
