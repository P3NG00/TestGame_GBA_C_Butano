#ifndef TG_FUNCTIONS_HPP
#define TG_FUNCTIONS_HPP

#include "bn_fixed.h"
#include "bn_fixed_point.h"
#include "bn_math.h"

#include "tg_constants.hpp"

bool is_axis(bn::fixed_point point);
int seconds_to_frames(bn::fixed seconds);
int get_sprite_index(bn::fixed_point direction);
bn::fixed distance(bn::fixed_point point1, bn::fixed_point point2);
bn::fixed magnitude(bn::fixed_point direction);
bn::fixed_point normalize(bn::fixed_point point);

#endif
