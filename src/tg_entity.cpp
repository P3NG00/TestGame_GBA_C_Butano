#include "bn_camera_ptr.h"
#include "bn_fixed.h"
#include "bn_fixed_point.h"
#include "bn_sprite_item.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_tiles_item.h"
#include "bn_sprite_tiles_ptr.h"
// TODO move includes to header files for all cpp files then include only their header file

#include "tg_entity.hpp"
#include "tg_functions.hpp"

entity::entity(bn::sprite_item sprite, bn::camera_ptr camera_obj) :
    _sprite_item(sprite),
    _sprite(sprite.create_sprite(0, 0))
{
    _sprite.set_camera(camera_obj);
}

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

void entity::_update_sprite()
{
    if (_new_sprite_index != -1 && _new_sprite_index != _last_sprite_index)
    {
        _sprite.set_tiles(_sprite_item.tiles_item().create_tiles(_new_sprite_index));
        _last_sprite_index = _new_sprite_index;
        _facing = _direction;
    }
}

void entity::_update_sprite_index()
{
    _new_sprite_index = get_sprite_index(_direction);
}

void entity::_set_x(bn::fixed x)
{
    _sprite.set_x(x);
}

void entity::_set_y(bn::fixed y)
{
    _sprite.set_y(y);
}
