#include "tg_entity_animated.hpp"

entity_animated::entity_animated(bn::sprite_item sprite, bn::fixed size) :
    entity(sprite, size) {}

void entity_animated::_update_sprite()
{
    if (_new_sprite_index != -1 && _new_sprite_index != _last_sprite_index)
    {
        _sprite.set_tiles(_sprite_item.tiles_item().create_tiles(_new_sprite_index));
        _last_sprite_index = _new_sprite_index;
        _facing = _direction;
    }
}

void entity_animated::_update_sprite_index()
{
    _new_sprite_index = get_sprite_index(_direction);
}
