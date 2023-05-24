#include "tg_entity.hpp"

entity::entity(bn::sprite_item sprite, bn::fixed size) :
    _sprite_item(sprite),
    _sprite(sprite.create_sprite(0, 0)),
    _size(size) {}

bn::fixed_point entity::position()
{
    return _sprite.position();
}

bn::fixed_point entity::direction_moving()
{
    return _direction;
}

bn::fixed_point entity::direction_facing()
{
    return _facing;
}

bn::fixed entity::x()
{
    return _sprite.x();
}

bn::fixed entity::y()
{
    return _sprite.y();
}

bn::fixed entity::size()
{
    return _size;
}

bool entity::active()
{
    return _sprite.visible();
}

void entity::set_camera(bn::camera_ptr camera_obj)
{
    _sprite.set_camera(camera_obj);
}

void entity::_set_x(bn::fixed x)
{
    _sprite.set_x(x);
}

void entity::_set_y(bn::fixed y)
{
    _sprite.set_y(y);
}

void entity::_set_position(bn::fixed_point point)
{
    _sprite.set_position(point);
}

void entity::_set_active(bool active)
{
    _sprite.set_visible(active);
}
