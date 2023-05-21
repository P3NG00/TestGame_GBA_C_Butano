#ifndef TG_SCENE_LEVEL_TEST_HPP
#define TG_SCENE_LEVEL_TEST_HPP

#include "bn_blending.h"
#include "bn_blending_actions.h"

#include "tg_functions.hpp"
#include "tg_player.hpp"
#include "tg_projectile.hpp"
#include "tg_text_handler.hpp"

#define PROJECTILE_AMOUNT 8

class scene_level_test
{
    text_handler _text_handler_obj = text_handler();
    projectile _projectile_obj_array[PROJECTILE_AMOUNT];
    player _player_obj = player();
    bn::blending_fade_alpha_to_action _fade_in = bn::blending_fade_alpha_to_action(seconds_to_frames(1), 0);

public:

    scene_level_test();
    void update();
};

#endif
