#ifndef TG_ENTITY_ANIMATED_HPP
#define TG_ENTITY_ANIMATED_HPP

#include "tg_entity.hpp"

class entity_animated : public entity
{
    int _last_sprite_index = 0;
    int _new_sprite_index = 0;
protected:
    entity_animated(bn::sprite_item sprite, bn::fixed size);
    void _update_sprite();
    void _update_sprite_index();
};

#endif
