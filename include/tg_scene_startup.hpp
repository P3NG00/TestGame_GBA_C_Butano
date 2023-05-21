#ifndef TG_SCENE_STARTUP_HPP
#define TG_SCENE_STARTUP_HPP

#include "bn_regular_bg_ptr.h"
#include "bn_sprite_ptr.h"

#include "bn_regular_bg_items_p3.h"
#include "bn_sprite_items_signature.h"

#include "tg_functions.hpp"

class scene_startup
{
    bn::fixed _counter = seconds_to_frames(5);
    bn::regular_bg_ptr _bg_logo = bn::regular_bg_items::p3.create_bg(-16, -16);
    bn::sprite_ptr _sprite_signature = bn::sprite_items::signature.create_sprite(48, 48);

public:

    void execute();
};

#endif
