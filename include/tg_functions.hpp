#ifndef TG_FUNCTIONS_HPP
#define TG_FUNCTIONS_HPP

#include "bn_fixed.h"
#include "bn_fixed_point.h"

bool is_axis(bn::fixed_point point);
int seconds_to_frames(bn::fixed seconds);
int get_sprite_index(bn::fixed_point direction);

#endif
