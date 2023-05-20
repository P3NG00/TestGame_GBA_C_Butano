#include "bn_core.h"

#include "tg_scene_level_test.hpp"
#include "tg_scene_startup.hpp"

int main()
{
    // init butano
    bn::core::init();

    // show startup scene
    scene_startup().execute();

    // initialize test level scene
    scene_level_test scene_level_test_obj = scene_level_test();

    // game loop
    while(true)
    {
        // handle input
        scene_level_test_obj.update();

        // update butano last
        bn::core::update();
    }
}
