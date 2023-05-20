#ifndef TG_PLAYER_HPP
#define TG_PLAYER_HPP

#include "bn_fixed.h"
#include "bn_sprite_ptr.h"

#include "bn_sprite_items_player.h"

#include "tg_projectile.hpp"

class player
{
    bn::sprite_ptr _sprite_ptr = bn::sprite_items::player.create_sprite(0, 0);
    bn::fixed _dx = 0;
    bn::fixed _dy = 0;
    int _last_sprite_index = 0;
    int _new_sprite_index = 0;

public:

    void handle_input(projectile* projectile_obj);
};

#endif
