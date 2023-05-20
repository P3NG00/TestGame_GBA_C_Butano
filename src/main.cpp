#include "bn_core.h"

#include "tg_scene_level_test.hpp"

int main()
{
    // init butano
    bn::core::init();

    // initialize game assets
    scene_level_test scene_level_test_obj = scene_level_test();
    scene_level_test_obj.initialize();

    // game loop
    while(true)
    {
        // handle input
        scene_level_test_obj.update();

        // update butano last
        bn::core::update();
    }
}
