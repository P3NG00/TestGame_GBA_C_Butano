#include "tg_enemy.hpp"

enemy::enemy() :
    entity(bn::sprite_items::enemy, 8)
{
    _set_active(false);
}

void enemy::update(bn::fixed_point player_position)
{
    // get direction
    _direction = normalize(player_position - position());

    // update position before rounding
    _new_position = position() + (_direction / 4); // TODO adjust speed

    // round direction
    _direction.set_x(_direction.x().round_integer());
    _direction.set_y(_direction.y().round_integer());

    // update sprite index
    _update_sprite_index();

    // update sprite
    _update_sprite();
}

void enemy::update_position()
{
    _set_position(_new_position);
}

void enemy::set(bn::fixed_point position)
{
    _set_position(position);
    _new_position = position;
    _set_active(true);
}

void enemy::handle_collision(enemy other)
{
    if (distance(position(), other.position()) > ENTITY_DISTANCE_CHECK)
        return;
    bn::fixed size_half = _size / 2;
    bn::fixed other_size_half = other._size / 2;
    if (position().x() + size_half > other.position().x() - other_size_half &&
        position().x() - size_half < other.position().x() + other_size_half &&
        position().y() + size_half > other.position().y() - other_size_half &&
        position().y() - size_half < other.position().y() + other_size_half)
    {
        // handle collision on per axis basis
        bn::fixed x_diff = position().x() - other.position().x();
        bn::fixed y_diff = position().y() - other.position().y();
        if (abs(x_diff) > abs(y_diff))
        {
            // x axis collision
            if (x_diff > 0)
                _new_position.set_x(other.position().x() + other_size_half + size_half);
            else
                _new_position.set_x(other.position().x() - other_size_half - size_half);
        }
        else
        {
            // y axis collision
            if (y_diff > 0)
                _new_position.set_y(other.position().y() + other_size_half + size_half);
            else
                _new_position.set_y(other.position().y() - other_size_half - size_half);
        }
    }
}
