#ifndef TG_SCENE_STARTUP_HPP
#define TG_SCENE_STARTUP_HPP

#include "bn_regular_bg_ptr.h"

#include "bn_regular_bg_items_p3.h"

#include "tg_functions.hpp"

class scene_startup
{
    bn::fixed _counter = seconds_to_frames(1);
    bn::regular_bg_ptr _bg_logo = bn::regular_bg_items::p3.create_bg(0, 0);

public:

    void execute();
};

#endif
