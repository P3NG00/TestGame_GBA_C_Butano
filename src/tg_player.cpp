#include "tg_player.hpp"

player::player(bn::camera_ptr camera_obj) :
    entity(bn::sprite_items::player, camera_obj) {}

void player::update()
{
    // player movement
    _direction.set_x(0);
    _direction.set_y(0);
    if (bn::keypad::up_held())
        _direction.set_y(_direction.y() - 1);
    if (bn::keypad::down_held())
        _direction.set_y(_direction.y() + 1);
    if (bn::keypad::left_held())
        _direction.set_x(_direction.x() - 1);
    if (bn::keypad::right_held())
        _direction.set_x(_direction.x() + 1);

    // update sprite index before normalizing direction
    _update_sprite_index();

    // normalize direction if not on axis
    if (!is_axis(_direction))
    {
        // TODO check keypad::b_held() to add speed boost
        _direction.set_x(_direction.x() * NORMALIZED);
        _direction.set_y(_direction.y() * NORMALIZED);
    }

    // update position
    if (!bn::keypad::l_held())
    {
        _set_x(x() + _direction.x());
        _set_y(y() + _direction.y());
    }

    // update sprite
    _update_sprite();
}
