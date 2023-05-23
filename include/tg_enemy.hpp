#ifndef TG_ENEMY_HPP
#define TG_ENEMY_HPP

#include "bn_fixed.h"
#include "bn_fixed_point.h"
#include "bn_sprite_ptr.h"

#include "bn_sprite_items_enemy.h"

class enemy
{
    bn::fixed_point _direction = bn::fixed_point(0, 0);
    bn::fixed_point _facing = bn::fixed_point(0, -1);
    int _last_sprite_index = 0;
    int _new_sprite_index = 0;
    // TODO implement '_life' and collide with projectiles

public:

    bn::sprite_ptr sprite = bn::sprite_items::enemy.create_sprite(0, 0);

    enemy();
    void update(bn::fixed_point player_position);
    void set(bn::fixed_point position);
    bn::fixed_point position();
};

#endif
