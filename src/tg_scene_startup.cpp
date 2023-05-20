#include "bn_core.h"

#include "tg_scene_startup.hpp"

void scene_startup::execute()
{
    while (--_counter > 0)
    {
        bn::core::update();
    }
}
