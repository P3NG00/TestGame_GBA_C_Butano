#ifndef TG_PLAYER_HPP
#define TG_PLAYER_HPP

#include "bn_camera_ptr.h"

#include "bn_fixed.h"
#include "bn_fixed_point.h"
#include "bn_keypad.h"
#include "bn_sprite_item.h"
#include "bn_sprite_tiles_ptr.h"

#include "bn_sprite_items_player.h"

#include "tg_constants.hpp"
#include "tg_entity.hpp"
#include "tg_functions.hpp"
#include "tg_player.hpp"

class player : public entity{
public:
    player(bn::camera_ptr camera_obj);
    void update();
};

#endif
