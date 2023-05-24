#ifndef TG_ENEMY_HPP
#define TG_ENEMY_HPP

#include "bn_camera_ptr.h"
#include "bn_fixed.h"
#include "bn_fixed_point.h"
#include "bn_math.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_tiles_ptr.h"

#include "bn_sprite_items_enemy.h"

#include "tg_entity_animated.hpp"
#include "tg_functions.hpp"

class enemy : public entity_animated
{
    bn::fixed_point _new_position;
public:
    enemy();
    bn::fixed_point new_position();
    bool collides_with(bn::fixed_point other_position, bn::fixed other_size);
    // called first to update enemy's new position
    void update(bn::fixed_point player_position);
    // called second to check collision using new position
    void handle_collision(bn::fixed_point other_position, bn::fixed other_size);
    // called last to update enemy's position after collision
    void update_position();
    void set(bn::fixed_point position);
};

#endif
