#include "bn_fixed.h"
#include "bn_fixed_point.h"

#define FRAMES_PER_SECOND 60

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
