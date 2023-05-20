#include "tg_scene_level_test.hpp"

scene_level_test::scene_level_test()
{
    // TODO initialize elements
}

void scene_level_test::update()
{
    _player_obj.handle_input(&_projectile_obj);
    _projectile_obj.update();
}
