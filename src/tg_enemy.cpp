#include "tg_enemy.hpp"

enemy::enemy() :
    entity_animated(bn::sprite_items::enemy, 8)
{
    _set_active(false);
}

bn::fixed_point enemy::new_position()
{
    return _new_position;
}

bool enemy::collides_with(bn::fixed_point other_position, bn::fixed other_size)
{
    bn::fixed size_half = _size / 2;
    bn::fixed other_size_half = other_size / 2;
    return position().x() + size_half > other_position.x() - other_size_half &&
           position().x() - size_half < other_position.x() + other_size_half &&
           position().y() + size_half > other_position.y() - other_size_half &&
           position().y() - size_half < other_position.y() + other_size_half;
}

void enemy::update(bn::fixed_point player_position)
{
    // get direction
    _direction = normalize(player_position - position());

    // update position before rounding
    _new_position = position() + (_direction / 2);

    // round direction
    _direction.set_x(_direction.x().round_integer());
    _direction.set_y(_direction.y().round_integer());

    // update sprite index
    _update_sprite_index();

    // update sprite
    _update_sprite();
}

// called after update() to check new position
void enemy::handle_collision(bn::fixed_point other_position, bn::fixed other_size)
{
    if (!collides_with(other_position, other_size))
        return;
    // handle collision on per axis basis
    bn::fixed x_diff = position().x() - other_position.x();
    bn::fixed y_diff = position().y() - other_position.y();
    bn::fixed combined_halves = (_size / 2) + (other_size / 2);
    if (abs(x_diff) > abs(y_diff))
    {
        // x axis collision
        if (x_diff > 0)
            _new_position.set_x(other_position.x() + combined_halves);
        else
            _new_position.set_x(other_position.x() - combined_halves);
    }
    else
    {
        // y axis collision
        if (y_diff > 0)
            _new_position.set_y(other_position.y() + combined_halves);
        else
            _new_position.set_y(other_position.y() - combined_halves);
    }
}

// called after handle_collision() to update to new position
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
