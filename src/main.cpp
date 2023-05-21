#include "bn_core.h"

#include "tg_scene_level_test.hpp"
#include "tg_scene_startup.hpp"

int main()
{
    // init butano
    bn::core::init();

    // show startup scene
    scene_startup().execute();

    // show game scene
    scene_level_test().execute();
}
