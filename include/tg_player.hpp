#ifndef TG_PLAYER_HPP
#define TG_PLAYER_HPP

#include "bn_camera_ptr.h"

#include "tg_entity.hpp"
#include "tg_player.hpp"

class player : public entity{
public:
    player(bn::camera_ptr camera_obj);
    void update();
};

#endif
