#ifndef TG_ENEMY_HPP
#define TG_ENEMY_HPP

#include "bn_camera_ptr.h"
#include "bn_fixed.h"
#include "bn_fixed_point.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_tiles_ptr.h"

#include "bn_sprite_items_enemy.h"

#include "tg_entity.hpp"
#include "tg_functions.hpp"

class enemy : public entity
{
    bn::fixed_point _new_position;
public:
    enemy();
    void update(bn::fixed_point player_position);
    void update_position();
    void set(bn::fixed_point position);
    void handle_collision(enemy other);
};

#endif
