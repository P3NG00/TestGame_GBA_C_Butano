#include "tg_scene_level_test.hpp"

void scene_level_test::initialize()
{
    _text_handler_obj.create_text(0, 0, "Hello, world!");
}

void scene_level_test::update()
{
    _player_obj.handle_input(&_projectile_obj);
    _projectile_obj.update();
}
