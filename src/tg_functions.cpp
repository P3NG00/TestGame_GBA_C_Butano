#include "tg_functions.hpp"

bool is_axis(bn::fixed_point point)
{
    return point.x() == 0 || point.y() == 0;
}

int seconds_to_frames(bn::fixed seconds)
{
    return (seconds * FramesPerSecond).integer();
}

constexpr int sprite_indexes[3][3] = {
    {7,  0, 1},
    {6, -1, 2},
    {5,  4, 3}
};

int get_sprite_index(bn::fixed_point direction)
{
    int x = direction.x().integer();
    int y = direction.y().integer();

    if (x >= -1 && x <= 1 && y >= -1 && y <= 1)
        return sprite_indexes[y + 1][x + 1];
    else
        return -1;
}

bn::fixed distance(bn::fixed_point point1, bn::fixed_point point2)
{
    bn::fixed x = point1.x() - point2.x();
    bn::fixed y = point1.y() - point2.y();
    return bn::sqrt((x * x) + (y * y));
}

bn::fixed magnitude(bn::fixed_point direction)
{
    return distance(bn::fixed_point(0, 0), direction);
}

bn::fixed_point normalize(bn::fixed_point point)
{
    bn::fixed magnitude = distance(bn::fixed_point(0, 0), point);
    return magnitude == 0 ? bn::fixed_point(0, 0) : point / magnitude;
}
