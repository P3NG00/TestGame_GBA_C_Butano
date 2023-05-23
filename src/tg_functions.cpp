#include "bn_fixed.h"
#include "bn_fixed_point.h"
#include "bn_math.h"

#include "tg_constants.hpp"

bool is_axis(bn::fixed_point point)
{
    return point.x() == 0 || point.y() == 0;
}

int seconds_to_frames(bn::fixed seconds)
{
    return (seconds * FRAMES_PER_SECOND).integer();
}

int get_sprite_index(bn::fixed_point direction)
{
    if      (direction.x() ==  0 && direction.y() ==  0)
        return -1;
    else if (direction.x() ==  0 && direction.y() == -1)
        return 0;
    else if (direction.x() ==  1 && direction.y() == -1)
        return 1;
    else if (direction.x() ==  1 && direction.y() ==  0)
        return 2;
    else if (direction.x() ==  1 && direction.y() ==  1)
        return 3;
    else if (direction.x() ==  0 && direction.y() ==  1)
        return 4;
    else if (direction.x() == -1 && direction.y() ==  1)
        return 5;
    else if (direction.x() == -1 && direction.y() ==  0)
        return 6;
    else if (direction.x() == -1 && direction.y() == -1)
        return 7;
    else
        return -1;
}

bn::fixed distance(bn::fixed_point point1, bn::fixed_point point2)
{
    bn::fixed x = point1.x() - point2.x();
    bn::fixed y = point1.y() - point2.y();
    return bn::sqrt((x * x) + (y * y));
}

bn::fixed_point normalize(bn::fixed_point point)
{
    bn::fixed magnitude = distance(bn::fixed_point(0, 0), point);
    return magnitude == 0 ? bn::fixed_point(0, 0) : point / magnitude;
}
