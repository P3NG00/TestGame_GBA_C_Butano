#ifndef TG_ENTITY_HPP
#define TG_ENTITY_HPP

#include "bn_camera_ptr.h"
#include "bn_fixed.h"
#include "bn_fixed_point.h"
#include "bn_sprite_item.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_tiles_item.h"
#include "bn_sprite_tiles_ptr.h"

#include "tg_functions.hpp"

class entity
{
    // initialized y to -1 to start facing up
    bn::fixed_point _facing = bn::fixed_point(0, -1);
    bn::sprite_item _sprite_item;
    bn::sprite_ptr _sprite;
    int _last_sprite_index = 0;
    int _new_sprite_index = 0;
    // TODO implement '_life'

protected:
    bn::fixed_point _direction = bn::fixed_point(0, 0);

    entity(bn::sprite_item sprite);
    entity(bn::sprite_item sprite, bn::camera_ptr camera_obj);
    void _set_x(bn::fixed x);
    void _set_y(bn::fixed y);
    void _set_position(bn::fixed_point point);
    void _update_sprite();
    void _update_sprite_index();
    void _set_active(bool active);

public:
    bn::fixed_point position();
    bn::fixed_point direction_moving();
    bn::fixed_point direction_facing();
    bn::fixed x();
    bn::fixed y();
    bool active();
    void set_camera(bn::camera_ptr camera_obj);
};

#endif
