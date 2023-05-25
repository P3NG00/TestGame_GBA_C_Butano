#ifndef TG_SCENE_LEVEL_TEST_HPP
#define TG_SCENE_LEVEL_TEST_HPP

#include "bn_array.h"
#include "bn_blending.h"
#include "bn_blending_actions.h"
#include "bn_camera_ptr.h"
#include "bn_core.h"
#include "bn_display.h"
#include "bn_fixed.h"
#include "bn_fixed_point.h"
#include "bn_keypad.h"
#include "bn_random.h"
#include "bn_regular_bg_ptr.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_text_generator.h"
#include "bn_string.h"
#include "bn_string_view.h"

#include "bn_regular_bg_items_bg_1.h"
#include "bn_regular_bg_items_bg_2.h"
#include "bn_regular_bg_items_select_window.h"
#include "bn_sprite_items_target.h"
#include "common_variable_8x16_sprite_font.h"

#include "tg_constants.hpp"
#include "tg_enemy.hpp"
#include "tg_functions.hpp"
#include "tg_player.hpp"
#include "tg_projectile.hpp"

class scene_level_test
{
public:
    void execute();
};

#endif
