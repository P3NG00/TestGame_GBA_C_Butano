#include "bn_blending.h"
#include "bn_core.h"

#include "tg_scene_startup.hpp"

void scene_startup::execute()
{
    bn::fixed time_fade = seconds_to_frames(1);
    _bg_logo.set_blending_enabled(true);

    while (_counter > 0)
    {
        _counter -= 1;

        if (_counter < time_fade)
        {
            bn::blending::set_fade_alpha(1 - (_counter / time_fade));
        }

        bn::core::update();
    }

    bn::blending::set_fade_alpha(0);
}
