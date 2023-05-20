#ifndef TG_SCENE_LEVEL_TEST_HPP
#define TG_SCENE_LEVEL_TEST_HPP

#include "tg_player.hpp"
#include "tg_projectile.hpp"
#include "tg_text_handler.hpp"

class scene_level_test
{
    text_handler _text_handler_obj = text_handler();
    player _player_obj = player();
    projectile _projectile_obj = projectile();

public:

    void initialize();
    void update();
};

#endif
