#ifndef TG_SCENE_STARTUP_HPP
#define TG_SCENE_STARTUP_HPP

#include "bn_regular_bg_ptr.h"

#include "bn_regular_bg_items_p3.h"

class scene_startup
{
    unsigned short int _counter = 60;
    bn::regular_bg_ptr _bg_logo = bn::regular_bg_items::p3.create_bg(0, 0);

public:

    void execute();
};

#endif
