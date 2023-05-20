#include "bn_core.h"

#include "tg_scene_startup.hpp"

void scene_startup::execute()
{
    while (_counter > 0)
    {
        _counter -= 1;
        bn::core::update();
    }
}
