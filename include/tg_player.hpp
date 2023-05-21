#ifndef TG_PLAYER_HPP
#define TG_PLAYER_HPP

#include "bn_fixed_point.h"
#include "bn_sprite_ptr.h"

#include "bn_sprite_items_player.h"

#include "tg_projectile.hpp"

class player
{
    bn::fixed_point _direction = bn::fixed_point(0, 0);
    // initialized y to -1 to handle the player facing up at the start
    bn::fixed_point _last_direction = bn::fixed_point(0, -1);
    int _last_sprite_index = 0;
    int _new_sprite_index = 0;

public:

    bn::sprite_ptr sprite_ptr = bn::sprite_items::player.create_sprite(0, 0);

    void handle_input();
    bn::fixed_point position();
    bn::fixed_point direction();
};

#endif
